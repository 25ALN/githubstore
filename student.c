#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct s
{
    char xuehao[20];
    char name[20];
    char sex[10];
    int age;
    int grade[5];
};
struct s student[10000];
int studentnum = 0;
void messageout();
void messagein();
void searchxueahao();
void searchname();
void studentin();
void studentdelete();
void studentpaixu();
void savemessage();
void loaddata();
void printneed();
int main()
{
    loaddata();
    printneed();
    int choice,l=1;
    scanf("%d", &choice);
    while (l==1)
    {
        switch (choice)
        {
        case 1:
            messageout();
            break;
        case 2:
            messagein();
            break;
        case 3:
            searchxueahao();
            break;
        case 4:
            searchname();
            break;
        case 5:
            studentin();
            break;
        case 6:
            studentdelete();
            break;
        case 7:
            studentpaixu();
            break;
        case 8:
            savemessage();
            break;
        case 9:
            l=0;
            return 0;
            break;
        default:
            break;
        }
        printneed();
        scanf("%d",&choice);
    }
    return 0;
}
void printneed()
{
    printf("学生信息管理系统\n");
    printf("2. 输入学生信息\n");
    printf("1. 输出学生信息\n");
    printf("3. 按学号查询学生信息\n");
    printf("4. 按姓名查询学生信息\n");
    printf("5. 插入学生信息\n");
    printf("6. 删除学生信息\n");
    printf("7. 按姓名排序学生信息\n");
    printf("8. 保存学生信息到文件\n");
    printf("9. 退出系统\n");
}
void messagein() {
    if (studentnum >= 10000) {
        printf("学生人数已满。\n");
        return;
    }

    printf("请输入学号，姓名，性别与年龄: ");
    scanf("%s %s %s %d", student[studentnum].xuehao, student[studentnum].name, student[studentnum].sex, &student[studentnum].age);
    getchar(); // 清除输入缓冲区中的换行符
    printf("请输入五门课的成绩: ");
    for (int j = 0; j < 5; j++) {
        scanf("%d", &student[studentnum].grade[j]);
    }

    studentnum++; // 学生数量增加
    printf("学生信息已保存。\n");

    // 打印当前学生信息以确认
    printf("当前学生信息: %s %s %s %d\n", student[studentnum-1].xuehao, student[studentnum-1].name, student[studentnum-1].sex, student[studentnum-1].age);
}

void messageout()
{
    if (studentnum == 0)
    {
        printf("no stuent");
        return;
    }
    for (int i = 0; i < studentnum; i++)
    {
        printf("学号\t姓名\t性别\t年龄\t成绩1\t成绩2\t成绩3\t成绩4\t成绩5\n");
        printf("%s\t%s\t%s\t%d", student[i].xuehao, student[i].name, student[i].sex, student[i].age);
        for (int j = 0; j < 5; j++)
        {
            printf("\t%d", student[i].grade[j]);
        }
        printf("\n");
    }
}
void searchxueahao()
{
    char kl[20];
    printf("请输入你需要查询的学号:");
    scanf("%s", kl);
    for (int i = 0; i < studentnum; i++)
    {
        if (strcmp(student[i].xuehao, kl)==0)
        {
            printf("该学生信息如下\n");
            printf("学号\t姓名\t性别\t年龄\t成绩1\t成绩2\t成绩3\t成绩4\t成绩5\n");
            printf("%s\t%s\t%s\t%d", student[i].xuehao, student[i].name, student[i].sex, student[i].age);
            return;
        }
    }
    printf("未找到该学生相关信息:");
}
void searchname()
{
    char n[10];
    printf("请输入你需要查询的姓名:");
    scanf("%s", n);
    for (int i = 0; i < studentnum; i++)
    {
        if (strcmp(student[i].name, n))
        {
            printf("该学生信息如下\n");
            printf("学号\t姓名\t性别\t年龄\t成绩1\t成绩2\t成绩3\t成绩4\t成绩5\n");
            printf("%s\t%s\t%s\t%d", student[i].xuehao, student[i].name, student[i].sex, student[i].age);
            return;
        }
    }
    printf("未找到该学生相关信息:");
}
void studentin()
{
    if (studentnum >= 10000)
    {
        printf("stuents' numbers over");
        return;
    }
    printf("请输入学号，姓名，性别与年龄:");
    scanf("%s %s %s %d", student[studentnum].xuehao, student[studentnum].name, student[studentnum].sex, &student[studentnum].age);
    getchar();
    printf("请输入五门课的成绩:");
    for (int j = 0; j < 5; j++)
    {
        scanf("%d", &student[studentnum].grade[j]);
    }
}
void studentdelete()
{
    if (studentnum == 0)
    {
        printf("没有任何学生的信息");
        return;
    }
    char nm[10];
    printf("请输入你想删除的学生姓名:\n");
    scanf("%s", nm);
    for (int i = 0; i < studentnum; i++)
    {
        if (strcmp(nm, student[i].name) == 0)
        {
            for (int j = i; j < studentnum - 1; j++)
            {
                student[j] = student[j + 1];
            }
            studentnum--;
            printf("该生信息已删除\n");
            return;
        }
    }
    printf("未找到该学生相关信息\n");
}
void studentpaixu()
{
    if (studentnum == 0)
    {
        printf("未找到任何学生相关信息\n");
        return;
    }
    for (int i = 0; i < studentnum; i++)
    {
        for (int j = i; j < studentnum; j++)
        {
            if (strcmp(student[i].name, student[j].name) >0)
            {
                struct s uo = student[i];
                student[i] = student[j];
                student[j] = uo;
            }
        }
    }
}
void savemessage() {
    FILE* fp2 = fopen("stu.txt", "w");
    if (fp2 == NULL) {
        perror("打开文件失败");
        return;
    }

    // 保存每个学生的信息
    for (int i = 0; i < studentnum; i++) {
        printf("正在保存学生数据: %s %s %d\n", student[i].xuehao, student[i].name, student[i].age);  // 调试输出
        fprintf(fp2, "%s %s %s %d", student[i].xuehao, student[i].name, student[i].sex, student[i].age);
        for (int j = 0; j < 5; j++) {
            fprintf(fp2, " %d", student[i].grade[j]);
        }
        fprintf(fp2, "\n");
    }

    // 检查文件是否成功关闭
    if (fclose(fp2) != 0) {
        perror("关闭文件失败");
    } else {
        printf("学生信息保存成功！\n");
    }
}
void loaddata() {
    FILE*fp3=fopen("stu.txt", "r");
    if(fp3==NULL){
        printf("fail");
        return;
    }
    while((fscanf(fp3,"%s %s %s %d",student[studentnum].xuehao,student[studentnum].name,student[studentnum].sex,&student[studentnum].age))!=EOF){
        for(int j=0;j<5;j++){
            fscanf(fp3,"%d",&student[studentnum].grade[j]);
        }
        studentnum++;
    }
    fclose(fp3);
}


