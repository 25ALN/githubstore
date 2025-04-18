#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#define _XOPEN_SOURCE
#include <signal.h>

#define maxzl 1024
#define maxcanshu 100
char prvdir[1024] = "";
char *outfile = NULL;
char *infile = NULL;
int mark = 0, bz = 0;
struct k
{
    char *a[maxcanshu];
};
void getmessage(char *buf);
void canshujiexi(char *buf, struct k *out);
void canshujiexi2(char *buf, struct k *out);
void guandaofj(char *buf, struct k *out, int *outnum);
void zhixinml_gd(struct k *out, int outnum);
void changedir(char *dirpath);

int main(int argc, char *argv[])
{
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, SIG_IGN);
    while (1)
    {
        printf("wjy-super-shell:");
        fflush(stdout);
        char buf[maxzl];
        struct k out[maxcanshu];
        int outnum = 0;
        getmessage(buf);
        if (strcmp(buf, "exit") == 0)
        {
            break;
        }
        if (strncmp(buf, "cd ", 3) == 0)
        {
            char *s = buf + 3;
            changedir(s);
            continue;
        }
        guandaofj(buf, out, &outnum);
        zhixinml_gd(out, outnum);
        mark = 0;
        infile = NULL, outfile = NULL;
    }
}
void getmessage(char *buf)
{
    if (fgets(buf, maxzl, stdin) == NULL)
    {
        printf("\n");
        exit(0);
    }
    buf[strlen(buf) - 1] = '\0';
}
void guandaofj(char *buf, struct k *out, int *outnum)
{
    char *zjbl;
    char *gd = strtok_r(buf, "|", &zjbl);
    while (gd != NULL && *outnum < maxcanshu - 1)
    {
        canshujiexi(gd, &out[*outnum]);
        (*outnum)++;
        gd = strtok_r(NULL, "|", &zjbl);
    }
}
void canshujiexi2(char *buf, struct k *outt)
{
    char *s = buf;
    int i = 0;
    bz = 0;
    int left = 0, right = 0, len = strlen(s);
    while (left < len)
    {
        while (left < len && s[left] == ' ')
            left++;
        if (left >= len)
            break;
        if (s[left] == '\'')
        {
            left++;
            right = left;
            while (right < len && s[right] != '\'')
                right++;
            if (right >= len)
            {
                return;
            }
            s[right++] = '\0';
        }
        else
        {
            right = left;
            while (right < len && s[right] != ' ')
                right++;
            if (right < len)
                s[right++] = '\0';
        }
        outt->a[i++] = s+left;
        left = right;
    }
    outt->a[i] = NULL; 
}
void canshujiexi(char *buf,struct k *outt){
    for(int l=0;l<strlen(buf);l++){
        if(buf[l]=='\''){
            canshujiexi2(buf,outt);
            return;
        }
    }
    char *zhong;
    char *ch=strtok_r(buf," ",&zhong);
    int i=0;
    bz=0;
    while(ch!=NULL){
        if(strcmp(ch,"<")==0){
            ch=strtok_r(NULL," ",&zhong);
            if(ch!=NULL){
                infile=ch;
            }
        }else if(strcmp(ch,">")==0){
            ch=strtok_r(NULL," ",&zhong);
            if(ch!=NULL){
                outfile=ch;
                mark=0;
            }
        }else if(strcmp(ch,">>")==0){
            ch=strtok_r(NULL," ",&zhong);
            if(ch!=NULL){
                outfile=ch;
                mark=1;
            }
        }else if(strcmp(ch,"&")==0){
            bz=1;
        }else{
            outt->a[i++]=ch;
        }
        ch=strtok_r(NULL," ",&zhong);
    }
    outt->a[i]=NULL;
}
void zhixinml_gd(struct k *out, int outnum)
{
    pid_t childpid;
    int fd[2], FD = -1;
    for (int i = 0; i < outnum; i++)
    {
        if (i != outnum - 1)
        {
            pipe(fd);
        }
        if ((childpid = fork()) == 0)
        {
            if (FD != -1)
            {
                dup2(FD, STDIN_FILENO);
                close(FD);
            }
            if (i < outnum - 1)
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
                close(fd[0]);
            }
            if (infile != NULL && i == 0)
            {
                int wjin = open(infile, O_RDONLY);
                if (wjin < 0)
                    exit(1);
                dup2(wjin, STDIN_FILENO);
                close(wjin);
            }
            if (outfile != NULL && i == outnum - 1)
            {
                int flag = O_CREAT | O_WRONLY | (mark ? O_APPEND : O_TRUNC);
                int wjout = open(outfile, flag, 0644);
                if (wjout < 0)
                    exit(1);
                dup2(wjout, STDOUT_FILENO);
                close(wjout);
            }
            execvp(out[i].a[0], out[i].a);
            perror("execvp fail");
            exit(1);
        }
        if (FD != -1)
        {
            close(FD);
        }
        if (i != outnum - 1)
        {
            close(fd[1]);
            FD = fd[0];
        }
    }
    if (bz == 0)
    {
        while (wait(NULL) > 0);
    }
    else
    {
        printf("somethig behind %d\n", childpid);
    }
}
void changedir(char *dirpath)
{
    char curdir[1024];
    getcwd(curdir, sizeof(curdir));
    if (strcmp(dirpath, "-") == 0)
    {
        if (strlen(prvdir) == 0)
        {
            return;
        }
        if (chdir(prvdir))
        {
            perror("cd");
            return;
        }
    }
    else if (dirpath[0] == '.')
    {
        char nowdir[1024], zj[1024];
        strncpy(nowdir, dirpath + 1, strlen(dirpath + 1));
        getcwd(zj, 1024);
        strncat(zj, nowdir, strlen(nowdir));
        if (chdir(zj))
        {
            perror("cd");
            return;
        }
    }
    else
    {
        if (chdir(dirpath))
        {
            perror("cd");
            return;
        }
    }
    strncpy(prvdir, curdir, sizeof(prvdir));
}
