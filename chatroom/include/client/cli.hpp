#include "../common.hpp"
#include "ftpc.hpp"
const int port=6666;
static bool recv_chatting=true;
static bool send_chatting=true;
int Send(int fd, const char *buf, int len, int flags);
int Recv(int fd,char *buf,int len,int flag);
void own_chat_end(int);
void group_chat_end(int);
static bool grecv_chat=true;
static bool gsend_chat=true;

struct clientmessage{
    int data_fd;
    std::string ip;
    std::string own_account;
    int begin_chat_mark=0;
    int if_getchat_account=0;
    int if_online=0;
    int if_enter_group=0;
    int if_begin_group_chat=0;
    ftpclient fptc;
};

class chatclient{
    public:
    
    void start();
    ~chatclient();
    private:

    void connect_init();
    void caidan();
    void deal_login_mu(char *a);
    void deal_else_gn();

    void delete_friends(int client_fd);
    void show_friends(int client_fd);
    void chat_with_friends(int client_fd,std::string request);
    void add_friends(int client_fd,std::string buf);
    void ingore_someone(int client_fd);
    void deal_new_message(int client_fd,std::string message);
    void new_message_show(int client_fd);
    void groups(int client_fd);
    void look_history(int client_fd);
    
    void flush_recv_buffer(int sockfd);
    std::string check_set(std::string temp);

    int check_if_newmes(int client_fd);
    //心
    void heart_check();
    void heart_work_thread();

    void create_group(int client_fd,int choose);
    void disband_group(int client_fd,int choose); 
    void look_enter_group(int client_fd,int choose);
    void apply_enter_group(int client_fd,int choose);
    void groups_chat(int client_fd,int choose);
    void look_groups_history(int client_fd,int choose);
    void quit_one_group(int client_fd,int choose);
    void look_group_members(int client_fd,int choose);
    
    void owner_charger_right(int client_fd,int choose);
    void move_someone_outgroup(int client_fd,std::string xz,std::string group_number);
    void add_group_charger(int client_fd,std::string xz,std::string group_number);

    void deal_apply_mes(int client_fd,std::string message);

    long long group_number_get(long long a);

    bool if_login=false;
    
    //心
    std::atomic<bool> heart_if_running{false};
    std::thread heart_beat;
    std::atomic<time_t> last_heart_time{0};

    int client_fd;
    std::unordered_map<int,clientmessage> clientmes;
    
    std::set<std::string> recv_message;  
};

void chatclient::start(){
    connect_init();

    while(true){
        if(!if_login){
            caidan();
        }else{
            deal_else_gn();
        }
    }
}

void chatclient::connect_init(){
    std::cout<<"开始连接服务端"<<std::endl;
    client_fd=socket(AF_INET,SOCK_STREAM,0);
    if(client_fd<0){
        perror("socket");
        close(client_fd);
    }    
    struct sockaddr_in clmes;
    clmes.sin_family=AF_INET;
    clmes.sin_port=htons(port);
    inet_pton(AF_INET,"10.30.0.117",&clmes.sin_addr);//小组网络
    //inet_pton(AF_INET,"192.168.110.68",&clmes.sin_addr);//寝室网络
    //inet_pton(AF_INET,"192.168.20.143",&clmes.sin_addr);//手机热点
    int len=sizeof(clmes);
    int connect_fd=connect(client_fd,(struct sockaddr*)&clmes,len);
    if(connect_fd<0){
        perror("connect");
        close(client_fd);
        return;
    }
    int flag=fcntl(client_fd,F_GETFL,0);
    fcntl(client_fd,F_SETFL,flag|O_NONBLOCK);
    clientmes[client_fd].ip="10.30.0.152";
    clientmes[client_fd].data_fd=-1;
    std::cout<<"已成功连接到服务端!"<<std::endl;

    //心
    heart_if_running=true;
    heart_beat=std::thread(&chatclient::heart_work_thread,this);
    heart_beat.detach();
}

void chatclient::heart_work_thread(){
    const char heart_cmd=0x05; //表示一个字节的大小
    const int heart_time=5;
    while(heart_if_running){
        if(Send(client_fd,&heart_cmd,1,0)<=0){
            perror("发送心跳失败");
            break;
        }
        last_heart_time=time(nullptr);
        sleep(heart_time);
    }
    std::cout<<"发送心跳终止，连接断开"<<std::endl;
    close(client_fd);
    client_fd=-1;
    if_login=false;
    exit(1);
}

void chatclient::heart_check(){
    int alive=1;
    if(setsockopt(client_fd,SOL_SOCKET,SO_KEEPALIVE,&alive,sizeof(alive))<0){
        perror("setsockopt alive");
    }
    int idle=30;
    if(setsockopt(client_fd,SOL_TCP,TCP_KEEPIDLE,&idle,sizeof(idle))<0){
        perror("setsockopt idle");
    }
    int intv=5;
    if(setsockopt(client_fd,SOL_TCP,TCP_KEEPINTVL,&intv,sizeof(intv))<0){
        perror("setsockopt intv");
    }
    int cnt=3;
    if(setsockopt(client_fd,SOL_TCP,TCP_KEEPCNT,&cnt,sizeof(cnt))<0){
        perror("setsockopt cnt");
    }
}

void chatclient::caidan(){
    std::cout<<"        ---------------------       "<<std::endl;
    std::cout<<"        |      聊天室        |      "<<std::endl;
    std::cout<<"        |      1.登陆        |      "<<std::endl;
    std::cout<<"        |      2.注册        |      "<<std::endl;
    std::cout<<"        |      3.注销        |      "<<std::endl;
    std::cout<<"        |      4.退出        |      "<<std::endl;
    std::cout<<"        ---------------------       "<<std::endl;
    char choose[10];
    memset(choose,'\0',sizeof(10));
    int tempc=0;
    int fail_times=0;
    while(true){
        std::cin>>tempc;
        if(std::cin.fail()){
            std::cout<<"输入中包含无效字符请重新输入:";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //这一步可以丢弃掉输入中的无效字符
            fail_times++;
            if(fail_times==3){
                std::cout<<"输入错误次数过多，请稍后重试"<<std::endl;
                return;
            }
            continue;
        }
        if(tempc>=1&&tempc<=4){
            break;
        }else{
            fail_times++;
            if(fail_times==3){
                std::cout<<"输入错误次数过多，请稍后重试"<<std::endl;
                return;
            }
            std::cout<<"输入格式错误请重新输入:";
        }
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::string temp=std::to_string(tempc);
    strcpy(choose,temp.data());
    strncat(choose," choose",sizeof(" choose"));
    if(choose[0]=='4'){
        std::cout<<"已退出客户端"<<std::endl;
        exit(0);
    }
    if(choose[0]!='1'&&choose[0]!='2'&&choose[0]!='3'){
        std::cout<<"无效命令，请重新输入"<<std::endl;
    }
    Send(client_fd,choose,strlen(choose),0);
    deal_login_mu(choose);
}

void chatclient::deal_login_mu(char *a){
    auto &x=clientmes[client_fd];
    char account[1024],password[1024],name[100];
    memset(account,'\0',sizeof(account));
    memset(password,'\0',sizeof(password));
    memset(name,'\0',sizeof(name));
    std::cout<<"请输入账号(10位):";
    std::cin.getline(account,sizeof(account));
    std::string actemp=account;
    int failtimes=0;
    while(actemp.size()!=10&&!std::all_of(actemp.begin(),actemp.end(),::isdigit)){
        if(failtimes==3){
            std::cout<<"错误次数过多请稍后重试"<<std::endl;
            return;
        }
        std::cout<<"账号格式不规范请重新输入:";
        failtimes++;
        std::getline(std::cin,actemp);
    }
    Send(client_fd,actemp.c_str(),actemp.size(),0);
    x.own_account=account;
    
    std::cout<<"请输入密码:";
    std::cin.getline(password,sizeof(password));
    Send(client_fd,password,strlen(password),0);
    
    if(strncmp(a,"2",1)==0){
        std::cout<<"请输入昵称:";
        std::cin.getline(name,sizeof(name));
        std::regex alpha_only("^[A-Za-z]+$");
        while(!std::regex_match(name,alpha_only)){
            std::cout<<"名字不是纯英文字母,请重新输入:"<<std::endl;
            std::cin.getline(name,sizeof(name));
        }
        Send(client_fd,name,strlen(name),0);
    }
    char reponse[1024];
    memset(reponse,'\0',sizeof(reponse));
    usleep(2000);
    int n=Recv(client_fd,reponse,sizeof(reponse),0);
    reponse[n]='\0';
    std::cout<<"server reponse:"<<reponse<<std::endl;
    if(n<=0){
        perror("recv");
        close(client_fd);
        return;
    }else{
        if(strstr(reponse,"登录成功")){
            if_login=true;
        }else if(strstr(reponse,"注册成功")){
            if_login=true;
        }else{
            return;
        }
    }
}

void chatclient::deal_else_gn(){
    std::cout<<"        ---------------------------       "<<std::endl;
    std::cout<<"        请选择你的需求：               "<<std::endl;
    std::cout<<"        |      1.查看好友列表       |      "<<std::endl;
    std::cout<<"        |      2.私聊某人           |      "<<std::endl;
    std::cout<<"        |      3.删除好友           |      "<<std::endl;
    std::cout<<"        |      4.添加好友           |      "<<std::endl;
    std::cout<<"        |      5.屏蔽功能           |      "<<std::endl;
    std::cout<<"        |      6.群聊功能           |      "<<std::endl;
    std::cout<<"        |      7.查看历史聊天记录   |     "<<std::endl;
    std::cout<<"        |      8.退出               |     "<<std::endl;
    auto&client=clientmes[client_fd];
    std::mutex getmes;
    std::thread getm([&]{
        while(true){
            int new_messize=0;
            new_messize=check_if_newmes(client_fd);
        }
    }); 
    getm.detach();
    std::mutex recv_mutex;
    static bool mesmark=false;
    std::thread message_out([&]{
        while(true){
            std::unique_lock<std::mutex> lock(recv_mutex);
            if(!recv_message.empty()&&recv_message.size()!=0&&mesmark==false&&client.if_enter_group==0){
                std::cout<<"        |      9.处理/查看"<<recv_message.size()<<"条新消息 |  "<<std::endl<<std::flush;
                lock.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                mesmark=true; 
                break;
            }else if(!recv_message.empty()&&recv_message.size()!=0&&mesmark==false&&client.if_enter_group==1){
                std::cout<<"收到新消息请稍后退出群聊后查看"<<std::endl;
                mesmark=true; 
                break;
            }
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
        }
    });
    message_out.detach();
    char choose[10];
    memset(choose,'\0',sizeof(choose));
    int tempch=0;
    //处理非法输入
    int fail_times=0;
    std::cin>>tempch;
    while(tempch<1||tempch>9||std::cin.fail()){
        if(fail_times!=0){
            std::cin>>tempch;
        }
        if(std::cin.fail()){
            std::cout<<"输入中包含无效字符请重新输入:";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //这一步可以丢弃掉输入中的无效字符
            fail_times++;
            if(fail_times==3){
                std::cout<<"输入错误次数过多，请稍后重试"<<std::endl;
                return;
            }
            continue;
        }
        if(tempch>=1&&tempch<=9){
            break;
        }else{
            fail_times++;
            if(fail_times==3){
                std::cout<<"输入错误次数过多，请稍后重试"<<std::endl;
                return;
            }
            std::cout<<"输入格式错误请重新输入:";
        }
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::string temp=std::to_string(tempch);
    strcpy(choose,temp.data());
    int n=Send(client_fd,choose,1,0);
    if(n<=0){
        perror("send");
        close(client_fd);
    }
    if(choose[0]=='8'){
        char server_repon[1024];
        memset(server_repon,'\0',1024);
        usleep(2000);
        int n=Recv(client_fd,server_repon,sizeof(server_repon),0);
        std::cout<<"n="<<n<<std::endl;
        std::cout<<"server reponse:"<<server_repon<<std::endl;
        if_login=false;
        return;
    }
    
    char buf[1024]; 
    memset(buf,'\0',sizeof(buf));
    int len=Recv(client_fd,buf,sizeof(buf),0);
    //下面这一行测试使用，之后应记得删除
    //std::cout<<"test buf="<<buf<<std::endl;
    if(buf[strlen(buf)]==' '||buf[strlen(buf)]=='\n'){
        buf[strlen(buf)]='\0';
    }
    switch (choose[0]){
        case '1':
            show_friends(client_fd);
            break;
        case '2':
            chat_with_friends(client_fd,(std::string)buf);
            break;
        case '3':
            delete_friends(client_fd);
            break;
        case '4':
            add_friends(client_fd,"no");
            break;
        case '5':
            ingore_someone(client_fd);
            break;
        case '6':
            client.if_enter_group=1;
            groups(client_fd);
            break;
        case '7':
            look_history(client_fd);
            break;
        case '9':
            new_message_show(client_fd);
            break;
        default:std::cout<<"无效选择"<<std::endl;
        break;
    }
}

int chatclient::check_if_newmes(int client_fd){
    auto&client=clientmes[client_fd];
    char buf[1024];
    memset(buf,'\0',sizeof(buf));
    static int stopmark=0;
    if(stopmark==0){
        Recv(client_fd,buf,sizeof(buf),MSG_PEEK);
        if(strlen(buf)>0&&buf[0]!=0x06){
            return 0;
        }
    }
    //MSG_PEEK只查看不接收
    if(strlen(buf)>0){
        std::string temp=buf;
        std::string markmes='('+client.own_account+')';
        std::mutex recv_lock;
        std::unique_lock<std::mutex> x(recv_lock);
        for(int i=0;i<temp.size();i++){
            if(temp[i]==0x05||temp[i]==0x06){
                temp.erase(i,1);
            }
        }
        if(temp.find("群聊")!=std::string::npos&&temp.find(markmes)!=std::string::npos&&temp.find("已被")
        ==std::string::npos&&temp.find("已成功加入")==std::string::npos){
            return 0;
        }
        if(((temp.find("群聊")!=std::string::npos||temp.find("你们现在是好友了")!=std::string::npos||
        temp.find("好友请求")!=std::string::npos)&&temp.find(markmes)!=std::string::npos)||
        (temp.find("群聊")!=std::string::npos&&temp.find(markmes)==std::string::npos)){
            flush_recv_buffer(client_fd);
            stopmark=1;
            char real_buf[1024];
            memset(real_buf,'\0',sizeof(real_buf));
            Recv(client_fd,real_buf,sizeof(real_buf),0);
            if(temp.find("好友请求被拒绝")!=std::string::npos||temp.find("你们现在是好友了")!=std::string::npos||temp.find("已被")!=std::string::npos
            ||temp.find("已成功加入")!=std::string::npos){
                std::string outmes=temp.substr(temp.find('['),temp.find(']')+1);
                std::cout<<outmes<<std::endl;
                flush_recv_buffer(client_fd);
                return 0;
            }
            int pos=temp.find('(');
            temp=temp.substr(0,pos);
            if(!recv_message.count(temp)){
                recv_message.insert(temp);
            }else{
                flush_recv_buffer(client_fd);
            }
        }
        x.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(300)); 
        stopmark=0;
    }
    return recv_message.size();
}

void chatclient::new_message_show(int client_fd){
    if(recv_message.empty()){
        std::cout<<"当前暂无新消息"<<std::endl;
        return;
    }
    std::cout<<"请选择你的需求或查看相关信息:"<<std::endl;
    int cnt=1;
    std::unordered_map<int,std::string> temp;
    std::mutex mes_showlcok;
    std::unique_lock<std::mutex> slock(mes_showlcok);
    for(auto i:recv_message){
        if(i.find('[')==std::string::npos) continue;
        std::string checkmes=i;
        checkmes=checkmes.substr(checkmes.find('['),checkmes.find(']')+1);
        if(cnt-1>1){
            if(temp[cnt-1].find(checkmes)!=std::string::npos){
                continue;
            }
        }
        std::cout<<std::to_string(cnt)<<"."<<checkmes<<std::endl;
        temp[cnt]=i;
        cnt++;
    }
    slock.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); 
    
    int choose=0;
    std::cout<<"输入你想处理的消息序号:";
    int fail_times=0;
    std::cin>>choose;
    while(choose<1||choose>=cnt||std::cin.fail()){
        if(fail_times!=0){
            std::cin>>choose;
        }
        if(std::cin.fail()){
            std::cout<<"输入中包含无效字符请重新输入:";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //这一步可以丢弃掉输入中的无效字符
            fail_times++;
            if(fail_times==3){
                std::cout<<"输入错误次数过多，请稍后重试"<<std::endl;
                return;
            }
            continue;
        }
        if(choose>=1&&choose<cnt){
            break;
        }else{
            fail_times++;
            if(fail_times==3){
                std::cout<<"输入错误次数过多，请稍后重试"<<std::endl;
                return;
            }
            std::cout<<"输入格式错误请重新输入:";
        }
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    deal_new_message(client_fd,temp[choose]);
}

void chatclient::flush_recv_buffer(int sockfd){
    char buffer[1024];
    while (true) {
        ssize_t bytes = recv(sockfd, buffer, sizeof(buffer),0);
        if (bytes <= 0) {
            break; 
        }
    }
}

void chatclient::deal_new_message(int client_fd,std::string message){
    if(message.find("好友请求:")!=std::string::npos){
        add_friends(client_fd,message);
        flush_recv_buffer(client_fd);
        recv_message.erase(message);
    }else if(message.find("私聊消息")!=std::string::npos){
        chat_with_friends(client_fd,message);
    }else if(message.find("加入群聊")!=std::string::npos){
        deal_apply_mes(client_fd,message);
        recv_message.erase(message);
    }else{
        recv_message.erase(message);
    }
    std::string next_choose;
    if(!recv_message.empty()){
        std::cout<<"是否继续处理消息？(1继续0退出)";
        std::getline(std::cin,next_choose);
        int failtime=1;
        while(next_choose.size()!=1||(next_choose!="1"&&next_choose!="0")){
            if(failtime==3){
                std::cout<<"输入错误次数过多请稍后重试"<<std::endl;
                return;
            }
            std::cout<<"输入格式有误，请重新输入:";
            std::getline(std::cin,next_choose);
            failtime++;
        }
        if(next_choose=="1"){
            new_message_show(client_fd);
        }else{
            return;
        }
    }else{ 
        std::cout<<"消息已全部处理完，暂时无新消息"<<std::endl;
    }
}

void chatclient::deal_apply_mes(int client_fd,std::string message){
    int pos=message.find("用户");
    std::string account=message.substr(0,pos);
    pos=message.find("聊");
    std::string group_number=message.substr(pos+3,9);
    //验证身份
    std::string mes=group_number+"identify";
    Send(client_fd,mes.c_str(),mes.size(),0);
    char buf[100];
    memset(buf,'\0',sizeof(buf));
    usleep(2000);
    Recv(client_fd,buf,sizeof(buf),0);
    std::string temp=buf;
    std::cout<<"identify="<<temp<<std::endl;
    if(temp.find("find")!=std::string::npos){
        std::cout<<"是否同意该用户进群(1是0否,输入0或1):";
        std::string choose;
        std::getline(std::cin,choose);
        int fail_time=0;
        while(choose.size()!=1||(choose!="0"&&choose!="1")){
            if(fail_time==3){
                std::cout<<"输入错误次数过多，请稍后重试"<<std::endl;
                return;
            }
            std::cout<<"输入格式有误，请重新输入:";
            fail_time++;
            std::getline(std::cin,choose);
        }
        if(choose=="0"){
            std::cout<<"已拒绝该用户的入群申请"<<std::endl;
        }else{
            int pos=account.find('[');
            account.erase(pos,1);
            choose+="(agree enter)*"+account+"**"+group_number+"$$";
            Send(client_fd,choose.c_str(),choose.size(),0);
            std::cout<<"该用户已成功入群"<<std::endl;
        }
    }else{
        std::cout<<"你不是该群的群主或管理员无权进行处理"<<std::endl;
    }
}

void chatclient::groups(int client_fd){
    std::cout<<"        -----------------------------       "<<std::endl;
    std::cout<<"        请选择你的需求：               "<<std::endl;
    std::cout<<"        |      1.创建群聊             |      "<<std::endl;
    std::cout<<"        |      2.解散群聊             |      "<<std::endl;
    std::cout<<"        |      3.查看已加入的群聊     |      "<<std::endl;
    std::cout<<"        |      4.申请加群             |      "<<std::endl;
    std::cout<<"        |      5.加入群聊聊天         |      "<<std::endl;
    std::cout<<"        |      6.退出某群             |      "<<std::endl;
    std::cout<<"        |      7.查看群聊历史聊天记录 |      "<<std::endl;
    std::cout<<"        |      8.查看群组成员         |      "<<std::endl;
    std::cout<<"        |      9.群主/管理员特权      |     "<<std::endl;
    std::cout<<"        |      10.返回                |      "<<std::endl;
    std::cout<<"        -----------------------------       "<<std::endl;
    int choose=0;
    int fail_times=0;
    while(true){
        std::cin>>choose;
        if(std::cin.fail()){
            std::cout<<"输入中包含无效字符请重新输入:";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //这一步可以丢弃掉输入中的无效字符
            fail_times++;
            if(fail_times==3){
                std::cout<<"输入错误次数过多，请稍后重试"<<std::endl;
                return;
            }
            continue;
        }
        if(choose>=1&&choose<=10){
            break;
        }else{
            fail_times++;
            if(fail_times==3){
                std::cout<<"输入错误次数过多，请稍后重试"<<std::endl;
                return;
            }
            std::cout<<"输入格式错误请重新输入:";
        }
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    if(choose==10){
        Send(client_fd,"10t",3,0);
        auto&client=clientmes[client_fd];
        client.if_enter_group=0;
        return;
    }
    switch (choose){
    case 1:
        create_group(client_fd,choose);
        break;
    case 2:
        disband_group(client_fd,choose);
        break;
    case 3:
        look_enter_group(client_fd,choose);
        break;
    case 4:
        apply_enter_group(client_fd,choose);
        break;
    case 5:
        groups_chat(client_fd,choose);
        break;
    case 6:
        quit_one_group(client_fd,choose);
        break;
    case 7:
        look_groups_history(client_fd,choose);
        break;
    case 8:
        look_group_members(client_fd,choose);
        break;
    case 9:
        owner_charger_right(client_fd,choose);
    default:
        break;
    }
}

void chatclient::create_group(int client_fd,int choose){
    std::string chose=std::to_string(choose);
    chose+=' ';
    std::cout<<"请输入你想创建的群聊的群号(9位):";
    long long group_number=group_number_get(group_number);
    if(group_number==0) return;
    int fail_times=0;
    std::string group_name;
    std::cout<<"请输入你群聊的名字:";
    std::getline(std::cin,group_name);
    while(group_name.size()>32){
        std::cout<<"群名过长,请重新输入:";
        fail_times++;
        if(fail_times==3){
            std::cout<<"输入错误次数过多，请稍后重试"<<std::endl;
            return;
        }
        std::getline(std::cin,group_name);
    }
    std::string num=std::to_string(group_number);
    std::string all_message=num+group_name+"(group)";
    all_message.insert(0,chose);
    int n=Send(client_fd,all_message.c_str(),all_message.size(),0);
    if(n<0){
        perror("create send");
    }
    char buf[100];
    memset(buf,'\0',sizeof(buf));
    usleep(2000);
    Recv(client_fd,buf,sizeof(buf),0);
    std::cout<<"server response:"<<buf<<std::endl;
    groups(client_fd);
}

void chatclient::disband_group(int client_fd,int choose){
    std::string chose=std::to_string(choose);
    chose+=' ';
    std::cout<<"请输入你想解散的群聊的群号(9位):";
    long long group_number=group_number_get(group_number);
    if(group_number==0) return;
    std::string all_message=std::to_string(group_number)+"(group)";
    all_message.insert(0,chose);
    int n=Send(client_fd,all_message.c_str(),all_message.size(),0);
    if(n<0){
        perror("disband send");
    }
    char buf[100];
    memset(buf,'\0',sizeof(buf));
    usleep(2000);
    Recv(client_fd,buf,sizeof(buf),0);
    std::cout<<"server response:"<<buf<<std::endl;
    groups(client_fd);
}

void chatclient::look_enter_group(int client_fd,int choose){
    std::string chose=std::to_string(choose);
    chose+=' ';
    char buf[1024];
    memset(buf,'\0',sizeof(buf));
    std::string all_message=chose+"(group)";
    int n=Send(client_fd,all_message.c_str(),all_message.size(),0);
    if(n<0){
        perror("look enter send");
    }
    usleep(2000);
    Recv(client_fd,buf,sizeof(buf),0);
    std::string temp=buf;
    if(temp.find("你还未加入任何群聊")==std::string::npos){
        std::cout<<"   群ID      群名      群主ID"<<std::endl;
    }
    std::cout<<buf<<std::endl;
    groups(client_fd);
}

void chatclient::apply_enter_group(int client_fd,int choose){
    std::string chose=std::to_string(choose);
    chose+=' ';
    std::cout<<"请输入你想加入的群聊的群号(9位):";
    long long group_number=group_number_get(group_number);
    if(group_number==0) return;
    std::string all_message=std::to_string(group_number)+"(group)";
    all_message.insert(0,chose);
    Send(client_fd,all_message.c_str(),all_message.size(),0);

    char buf[100];
    memset(buf,'\0',sizeof(buf));
    usleep(2000);
    Recv(client_fd,buf,sizeof(buf),0);
    std::cout<<"server response:"<<buf<<std::endl;
    groups(client_fd);
}

void chatclient::groups_chat(int client_fd,int choose){
    auto&client=clientmes[client_fd];
    std::string chose=std::to_string(choose);
    chose+=' ';
    std::cout<<"请输入你想加入聊天的群聊账号:";
    long long group_number=group_number_get(group_number);
    if(group_number==0) return;
    std::string all_message=std::to_string(group_number)+"(group)";
    all_message.insert(0,chose);
    Send(client_fd,all_message.c_str(),all_message.size(),0);
    char buf[100];
    memset(buf,'\0',sizeof(buf));
    usleep(2000);
    Recv(client_fd,buf,sizeof(buf),0);
    std::cout<<"server response:"<<buf<<std::endl;
    std::string temp=buf;
    static int group_chatfd;
    if(temp.find("可以在该群中发送消息了")!=std::string::npos){
        std::string gb_addr="239.";
        long long getaddr=group_number;
        gb_addr+=(std::to_string(getaddr%255)+'.');
        getaddr/=255;
        gb_addr+=(std::to_string(getaddr%255)+'.');
        getaddr/=255;
        gb_addr+=(std::to_string(getaddr%255));

        group_chatfd=socket(AF_INET,SOCK_DGRAM,0);
        int flag=fcntl(group_chatfd,F_GETFL,0);
        fcntl(group_chatfd,F_SETFL,flag|O_NONBLOCK);
        struct sockaddr_in addr;
        memset(&addr,0,sizeof(addr));
        addr.sin_family=AF_INET;
        addr.sin_port=htons(8888);
        addr.sin_addr.s_addr=htonl(INADDR_ANY);
        
        int opt=1;
        int reuse_fd=setsockopt(group_chatfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(int));
        if(reuse_fd<0){
            perror("reuse setsockopt");
            close(group_chatfd);
        }
        int bind_fd=bind(group_chatfd,(struct sockaddr*)&addr,sizeof(addr));
        if(bind_fd<0){
            perror("udp bind");
            close(group_chatfd);
        }
        //加入多播
        struct ip_mreq mreq;
        mreq.imr_interface.s_addr=htonl(INADDR_ANY);
        mreq.imr_multiaddr.s_addr=inet_addr(gb_addr.c_str());
        int set_fd=setsockopt(group_chatfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));
        if(set_fd<0){
            perror("setsockopt");
            close(group_chatfd);
        }
        char gbuf[4096];
        std::cout<<"group_chat_fd="<<group_chatfd<<std::endl;

        std::signal(SIGINT,group_chat_end);

        std::thread recv_thread([&]{
            while(grecv_chat){
                memset(gbuf,'\0',sizeof(gbuf));
                usleep(500);
                int n=Recv(group_chatfd,gbuf,sizeof(gbuf),0);
                if(n<0){
                    continue;
                }       
                gbuf[n]='\0';
                std::string a=gbuf;
                if(a[0]!='\n'&&a[0]!=0x06&&!a.empty()){
                    int pos1=a.find("$?");
                    int pos2=a.find("^!");
                    std::string tempac=a.substr(pos1+2,pos2-pos1-2);
                    if(tempac==client.own_account) continue;
                    else{
                        if(pos1!=-1&&pos2!=-1){
                            a.erase(pos1,pos2-pos1+2);
                        }
                    }
                    std::cout<<a;
                }
            }
        });
        std::thread send_thread([&]{
            while(gsend_chat){
                char mes[100];
                std::string message;
                memset(mes,'\0',sizeof(mes));
                while(std::cin.getline(mes,sizeof(mes))){
                    if(*mes!=0){
                        message+=mes;
                    }else{
                        break;
                    }
                    message+='\n';
                }
                message+="*g*(group)";
                message=message+"$?"+client.own_account+"^!";
                Send(client_fd,message.c_str(),message.size(),0);
                if(message.find("STOR ")!=std::string::npos||message.find("RETR ")!=std::string::npos){
                    int pos=message.find("\n*g*(group)");
                    message.erase(pos,message.size()-pos);
                    client.fptc.start(message);
                }
                message.clear();
                if(gsend_chat==false) break;
            }
        });
        if(recv_thread.joinable()){
            recv_thread.join();
        }
        if(send_thread.joinable()){
            send_thread.join();
            std::string gend_mark="/gexit/*g*(group)";
            Send(client_fd,gend_mark.c_str(),gend_mark.size(),0);
        }
        if(recv_thread.joinable()&&send_thread.joinable()){
            
        }else{
            //离开多播组
            set_fd=setsockopt(group_chatfd,IPPROTO_IP,IP_DROP_MEMBERSHIP,&mreq,sizeof(mreq));
            if(set_fd<0){
                perror("quit setsockopt");
                close(group_chatfd);
            }
            std::cout<<"已成功退出群聊"<<std::endl;
            grecv_chat=true;
            gsend_chat=true;
        }
    }else{
        return;
    }
}

void chatclient::look_groups_history(int client_fd,int choose){
    std::string chose=std::to_string(choose);
    chose+=' ';
    std::cout<<"请输入你想查看历史记录的群聊的群号:";
    long long group_number=group_number_get(group_number);
    if(group_number==0) return;
    std::string all_message=std::to_string(group_number)+("(group)");
    all_message.insert(0,chose);
    Send(client_fd,all_message.c_str(),all_message.size(),0);
    char buf[1000000];
    memset(buf,'\0',sizeof(buf));
    usleep(2000);
    Recv(client_fd,buf,sizeof(buf),0);
    std::cout<<buf<<std::endl;
    groups(client_fd);
}

void chatclient::quit_one_group(int client_fd,int choose){
    std::string chose=std::to_string(choose);
    chose+=' ';
    std::cout<<"请输入你想退出的群聊的群号(9位):";
    long long group_number=group_number_get(group_number);
    if(group_number==0) return;
    std::string all_message=std::to_string(group_number)+"(group)";
    all_message.insert(0,chose);
    Send(client_fd,all_message.c_str(),all_message.size(),0);
    usleep(2000);
    char buf[100];
    memset(buf,'\0',sizeof(buf));
    Recv(client_fd,buf,sizeof(buf),0);
    std::cout<<buf<<std::endl;
    groups(client_fd);
}

void chatclient::look_group_members(int client_fd,int choose){
    std::string chose=std::to_string(choose);
    chose+=' ';
    std::cout<<"请输入你想查看群成员的群聊的群号(9位):";
    long long group_number=group_number_get(group_number);
    if(group_number==0) return;
    std::string all_message=std::to_string(group_number)+"(group)";
    all_message.insert(0,chose);
    Send(client_fd,all_message.c_str(),all_message.size(),0);
    char buf[1024];
    memset(buf,'\0',sizeof(buf));
    usleep(2000);
    int n=Recv(client_fd,buf,sizeof(buf),0);
    if(n<0){
        perror("look member recv");
    }
    std::string check=buf;
    std::cout<<buf<<std::endl;
    groups(client_fd);
}

void chatclient::owner_charger_right(int client_fd,int choose){
    std::string chose=std::to_string(choose);
    chose+=' ';
    std::string all_message=chose+"(group)";
    int n=Send(client_fd,all_message.c_str(),all_message.size(),0);
    if(n<0){
        perror("right send");
    }
    char buf[100];
    memset(buf,'\0',sizeof(buf));
    usleep(1000);
    Recv(client_fd,buf,sizeof(buf),0);
    std::string check_identity=buf;
    std::cout<<"identify="<<check_identity<<std::endl;
    if(check_identity.find("成员")!=std::string::npos||check_identity.empty()){
        std::cout<<"你还不是任何群的群主或者管理员,无权继续操作"<<std::endl;
        return;
    }
    std::cout<<"        请选择你的需求：               "<<std::endl;
    std::cout<<"        |      1.将某人移除群聊       |      "<<std::endl;
    if(check_identity.find("群主")!=std::string::npos){
    std::cout<<"        |      2.添加管理员           |      "<<std::endl;
    std::cout<<"        |      3.移除管理员           |      "<<std::endl;  
    }
    std::cout<<"        |      4.返回                 |      "<<std::endl;
    chose.clear();
    std::getline(std::cin,chose);
    int failtime=0;
    while(chose.size()!=1||(chose!="1"&&chose!="2"&&chose!="3"&&chose!="4")){
        if(failtime==3){
            std::cout<<"输入错误次数过多请稍后重试！"<<std::endl;
            return;
        }
        std::cout<<"输入格式有误，请重新输入:";
        failtime++;
        std::getline(std::cin,chose);
    }
    if(chose=="4"){
        return;
    }
    std::cout<<"请输入你想操作的群聊的群号(9位):";
    long long group_number=group_number_get(group_number);
    std::string temp=std::to_string(group_number);
    if(group_number==0) return;
    switch (chose[0]){
        case '1':
            move_someone_outgroup(client_fd,chose,temp);
            break;
        case '2':
        case '3':
            add_group_charger(client_fd,chose,temp);
            break;
        default:
            break;
    }
    groups(client_fd);
}

void chatclient::move_someone_outgroup(int client_fd,std::string xz,std::string group_number){
    auto&client=clientmes[client_fd];
    std::string account;
    std::cout<<"请输入你想要移除的群成员账号(10位):";
    //最后应该进行10位账号的验证 
    std::getline(std::cin,account);
    int failtimes=0;
    while(account.size()!=10&&!std::all_of(account.begin(),account.end(),::isdigit)){
        if(failtimes==3){
            std::cout<<"错误次数过多请稍后重试"<<std::endl;
            break;
        }
        std::cout<<"账号格式不规范请重新输入:";
        failtimes++;
        std::getline(std::cin,account);
    }
    xz+=' ';
    account.insert(0,xz);
    group_number.insert(0,"*");
    group_number+="(group)(group owner)";
    account+=group_number;
    Send(client_fd,account.c_str(),account.size(),0);
    char buf[100];
    memset(buf,'\0',sizeof(buf));
    usleep(2000);
    Recv(client_fd,buf,sizeof(buf),0);
    std::cout<<"server response:"<<buf<<std::endl;
}

void chatclient::add_group_charger(int client_fd,std::string xz,std::string group_number){
    auto&client=clientmes[client_fd];
    std::string account;
    std::cout<<"请输入你想要添加/移除管理员的群成员账号:";
    //最后应该进行10位账号的验证 
    std::getline(std::cin,account);
    int failtimes=0;
    while(account.size()!=10&&!std::all_of(account.begin(),account.end(),::isdigit)){
        if(failtimes==3){
            std::cout<<"错误次数过多请稍后重试"<<std::endl;
            break;
        }
        std::cout<<"账号格式不规范请重新输入:";
        failtimes++;
        std::getline(std::cin,account);
    }
    xz+=' ';
    account.insert(0,xz);
    group_number.insert(0,"*");
    group_number+="(group)(group owner)";
    account+=group_number;
    Send(client_fd,account.c_str(),account.size(),0);
    char buf[100];
    memset(buf,'\0',sizeof(buf));
    usleep(1500);
    Recv(client_fd,buf,sizeof(buf),0);
    std::cout<<"server response:"<<buf<<std::endl;
}

long long chatclient::group_number_get(long long a){
    int fail_times=0;
    while(true){
        std::cin>>a;
        if(std::cin.fail()){
            std::cout<<"输入中包含无效字符请重新输入:";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //这一步可以丢弃掉输入中的无效字符
            fail_times++;
            if(fail_times==3){
                std::cout<<"输入错误次数过多，请稍后重试"<<std::endl;
                return 0;
            }
            continue;
        }
        if(a>99999999&&a<=999999999){
            break;
        }else{
            fail_times++;
            if(fail_times==3){
                std::cout<<"输入错误次数过多，请稍后重试"<<std::endl;
                return 0;
            }
            std::cout<<"群聊格式错误请重新输入:";
        }
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    return a;
}

void chatclient::ingore_someone(int client_fd){
    std::cout<<"        请选择你的需求：               "<<std::endl;
    std::cout<<"        |      1.屏蔽某人                  |      "<<std::endl;
    std::cout<<"        |      2.解除对某人的屏蔽           |      "<<std::endl;
    static int times=0;
    std::string choose;
    std::getline(std::cin,choose);
    if(choose=="1"){
        std::string account;
        std::cout<<"请输入你想屏蔽的账号:";
        std::getline(std::cin,account);
        account+="B";
        int n=Send(client_fd,account.c_str(),account.size(),0);
        if(n<0){
            perror("ingore send");
            close(client_fd);
            return;
        }
        char reponse[1024];
        usleep(2000);
        memset(reponse,'\0',sizeof(reponse));
        Recv(client_fd,reponse,sizeof(reponse),0);
        std::cout<<"server reponse:"<<reponse<<std::endl;
    }else if(choose=="2"){
        std::cout<<"请输入你想要解除屏蔽的账号:";
        std::string account;
        std::getline(std::cin,account);
        account+="K";
        Send(client_fd,account.c_str(),account.size(),0);
        usleep(2000);
        char response[100];
        memset(response,'\0',sizeof(response));
        Recv(client_fd,response,sizeof(response),0);
        std::cout<<"server response:"<<response<<std::endl;
    }else{
        times++;
        if(times==3){
            std::cout<<"输入错误次数过多，请稍后重试"<<std::endl;
            times=0;
            return;
        }else{
            std::cout<<"无效输入！请重新按照格式输入";
            ingore_someone(client_fd);
        }
    }
}

void chatclient::delete_friends(int client_fd){
    char friend_name[1024];
    std::cout<<"请输入你要删除的好友的账号:";
    std::cin.getline(friend_name,sizeof(friend_name));
    int n=Send(client_fd,friend_name,strlen(friend_name),0);
    if(n<0){
        perror("send");
        close(client_fd);
        return;
    }
    char reponse[1024];
    memset(reponse,'\0',sizeof(reponse));
    usleep(1000);
    n=Recv(client_fd,reponse,sizeof(reponse),0);
    if(n<0){
        perror("delete recv");
        close(client_fd);
        return;
    }
    std::cout<<"server reponse:"<<reponse<<std::endl;
}

void chatclient::look_history(int client_fd){
    std::cout<<"请输入你要查看聊天记录的好友账号:";
    std::string account;
    std::getline(std::cin,account);
    Send(client_fd,account.c_str(),account.size(),0);

    char buf[10000];
    memset(buf,'\0',sizeof(buf));
    usleep(1000);
    int n=Recv(client_fd,buf,sizeof(buf),0);
    if(n<0){
        perror("look recv");
        close(client_fd);
    }
    std::cout<<buf<<std::endl;
}

void chatclient::chat_with_friends(int client_fd,std::string request){
    auto &client=clientmes[client_fd];
    if(request.find("私聊消息")!=std::string::npos){
        std::string temp;
        std::cout<<"请选择加入私聊(1)或者等会再说(0) (输入1或0):";
        std::getline(std::cin,temp);
        while(temp.size()!=1){
            std::cout<<"非法输入!请重新按照格式进行输入:";
            std::getline(std::cin,temp);
        }
        if(temp=="1"){
            client.begin_chat_mark=1;
            int pos=request.find('(');
            int tail=request.find(')');
            std::string getaccout=request.substr(pos+1,tail-pos-1);
            std::string ensure_state="enter chat state("+getaccout+")";
            std::cout<<"state mess:"<<ensure_state<<std::endl;
            Send(client_fd,ensure_state.c_str(),ensure_state.size(),0);
            client.if_getchat_account=1;
            recv_message.erase(request);
        }else{
            return;
        }
    }
    if(client.if_getchat_account==0){
        char account[1024];
        memset(account,'\0',sizeof(account));
        std::cout<<"请输入你要私聊的好友账号:";
        client.begin_chat_mark=1;
        std::cin.getline(account,1024);
        strncat(account,"(need to save)",sizeof("(need to save)"));
        std::string check;
        std::string temp;
        check="私聊消息";
        temp=check_set(check);
        if(temp.find("来自")!=std::string::npos&&temp.find("私聊消息")!=std::string::npos){
            std::cout<<"好友已发来私聊请求，下面进行选择"<<std::endl;
            chat_with_friends(client_fd,temp);
        }
        Send(client_fd,account,strlen(account),0);
        char ensure[100];
        memset(ensure,'\0',sizeof(ensure));
        usleep(2000);
        Recv(client_fd,ensure,sizeof(ensure),0);
        std::string ifzx=ensure;
        std::cout<<"ensure message:"<<ifzx<<std::endl;
        if(ifzx.find("可以向该好友发送消息了")!=std::string::npos){
            recv_chatting=true;
            send_chatting=true;
        }
        if(ifzx.find("屏蔽")!=std::string::npos||ifzx.find("该账号不存在")!=std::string::npos||ifzx.find("不允许")!=std::string::npos){
            return;
        }
        if(ifzx.find("在线")){
            client.if_online=1;
        }else{
            client.if_online=0;
        }
        client.if_getchat_account=1;
    }else{
        std::cout<<"request_size="<<request.size()<<std::endl;
        std::cout<<request<<std::endl;
    }
    std::signal(SIGINT,own_chat_end);
    
    std::thread recv_thread([&]{
        while (recv_chatting) {
            char msg[4096];
            memset(msg,'\0',sizeof(msg));
            usleep(500);
            int n=Recv(client_fd, msg, sizeof(msg),0);
            if(n<0){
                continue;
            }
            std::string temp=msg;
            if(temp.find("来自asdf用户的私聊消息")!=std::string::npos){
                continue;
            }
            if(strlen(msg)>0&&msg[0]!=' '&&msg[0]!='\n'&&msg[0]!=0x06){
                std::cout<<msg;
            }
            
            temp=temp.substr(temp.find(':')+1,5);
        }
    });
    
    std::thread send_thread([&]{
        while (send_chatting) {
            std::string allbuf;
            char buf[200];
            memset(buf,'\0',sizeof(buf));
            while(std::cin.getline(buf,sizeof(buf))){
                if(*buf!=0){
                    allbuf+=buf;
                }else{
                    break;
                }
                if(buf[0]!=' '){
                    allbuf+='\n';
                }
            }          
            if(allbuf.empty()) continue;  
            allbuf+=("*c*");
            std::string temp=allbuf;
            Send(client_fd,allbuf.c_str(),allbuf.size(),0);
            if(temp.find("STOR ")!=std::string::npos||temp.find("RETR ")!=std::string::npos){
                int pos=temp.find('*');
                temp.erase(pos,temp.size()-pos);
                client.fptc.start(temp);
            }
        }
    });

    if(recv_chatting==false&&send_chatting==false){
        std::cout<<"私聊结束"<<std::endl;
    }
    if(recv_thread.joinable()){
        recv_thread.join();
        recv_chatting=true;
    }
    if(send_thread.joinable()){
        send_thread.join();
        send_chatting=true;
        client.if_getchat_account=0;
        client.begin_chat_mark=0;
        std::string ownend_mark="ownexit*c*";
        Send(client_fd,ownend_mark.c_str(),ownend_mark.size(),0);
        return;
    }
}

void chatclient::show_friends(int client_fd){
    char friends[4096];
    memset(friends,'\0',sizeof(friends));
    usleep(2000);
    int n=Recv(client_fd,friends,sizeof(friends),0);
    if(n<=0){
        perror("show recv");
        close(client_fd);
        client_fd=-1;
        if_login=false;
        return;
    }
    std::cout<<"好友列表："<<std::endl;
    std::string temp=friends;
    int pos=temp.find("1.");
    if(pos==-1){
        pos=temp.find("你暂时");
    }
    temp.erase(0,pos);
    std::cout<<temp<<std::endl;
}

void chatclient::add_friends(int client_fd,std::string buf){
    if(buf.find("好友请求")!=std::string::npos){
        std::cout<<"请输入同意或拒绝:"<<std::endl;
        std::string re;
        std::getline(std::cin,re);
        while(re!="同意"&&re!="拒绝"){
            std::cout<<"输入有误！请重新按照格式输入:";
            std::getline(std::cin,re);
        }
        flush_recv_buffer(client_fd);
        int n=Send(client_fd,re.c_str(),re.size(),0);
        
        char reponse[100];
        memset(reponse,'\0',sizeof(reponse));
        usleep(1000);
        Recv(client_fd,reponse,sizeof(reponse),0);
        std::cout<<"server response:"<<reponse<<std::endl;
        return;
    }
    
    char account[100];
    memset(account,'\0',sizeof(account));
    std::cout<<"请输入你要添加好友的账号:";
    std::cin.getline(account,sizeof(account));
    strncat(account,"\n",1);
    int n=Send(client_fd,account,strlen(account),0);
    if(n<=0){
        perror("add send");
        close(client_fd);
        return;
    }
    char reponse[1024];
    memset(reponse,'\0',sizeof(reponse));

    int retry = 0;
    while (retry < 10) { // 最多尝试10次
        usleep(1000);
        int n=Recv(client_fd, reponse, sizeof(reponse), 0);
        if (n > 0) {
            std::cout << "server reponse:" << reponse << std::endl;
            return;
        } 
        usleep(100000); // 等待100ms
        retry++;
    }
}

std::string chatclient::check_set(std::string temp){
    std::string message;
    for(const std::string&str:recv_message){
        if(str.find(temp)!=std::string::npos){
            message=str;
            return message;
        }
    }
    message="no";
    return message;
}

chatclient::~chatclient(){
    std::cout<<"开始关闭该客户端"<<std::endl;

    //心
    heart_if_running=false;
    if(heart_beat.joinable()){
        heart_beat.join();
    }

    for(auto[fd,clientmesage]:clientmes){
        close(fd);
    }
    if(client_fd!=-1){
        close(client_fd);
    }
    std::cout<<"该客户端已成功关闭！"<<std::endl;
}

int Recv(int fd,char *buf,int len,int flag){
    int reallen=0;
    fd_set set;
    struct timeval timeout;
    while(reallen<len){
        int temp = recv(fd, buf + reallen, len - reallen, flag);
        if (temp > 0) {
            reallen += temp;
        } else if (temp == 0) { // 连接关闭
            break;
        } else {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                break; // 非阻塞模式下无更多数据，退出循环
            } else {
                perror("recv");
                close(fd);
                return -1;
            }
        }
    }
    return reallen;
}

int Send(int fd, const char *buf, int len, int flags)
{
    int reallen = 0;
    while (reallen < len){
        int temp = send(fd, buf + reallen, len - reallen, flags);
        if (temp < 0){
            perror("send");
            close(fd);
            return reallen;
        }
        else if (temp == 0){
            // 数据已全部发送完毕
            return reallen;
        }
        reallen += temp;
    }
    return reallen;
}

void own_chat_end(int){
    recv_chatting=false;
    send_chatting=false;
    std::cout<<"已退出私聊"<<std::endl;
}

void group_chat_end(int){
    grecv_chat=false;
    gsend_chat=false;
    std::cout<<"已退出群聊"<<std::endl;
}