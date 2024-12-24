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
void printneed()
{
    printf("学生信息管理系统\n");
    printf("1. 输入学生信息\n");
    printf("2. 输出学生信息\n");
    printf("3. 按学号查询学生信息\n");
    printf("4. 按姓名查询学生信息\n");
    printf("5. 插入学生信息\n");
    printf("6. 删除学生信息\n");
    printf("7. 按姓名排序学生信息\n");
    printf("8. 保存学生信息到文件\n");
    printf("9. 从文件加载学生信息\n");
    printf("0. 退出系统\n");
}
int main()
{
    FILE *fp = fopen("stu.txt", "r");
    char str[100000];
    while (fgets(str, sizeof(str), fp) != NULL)
        studentnum++;
    void printneed();
    int choice,l=1;
    scanf("%d", &choice);
    while (l==1)
    {
        scanf("%d", &choice);
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

            break;
        case 9:
            l=0;
            break;
        default:
            break;
        }
    }
    return 0;
}
void messagein()
{
    if (studentnum >= 10000)
    {
        printf("stuents' numbers over");
        return;
    }
    for (int i = 0; i < studentnum; i++)
    {
        printf("请输入学号，姓名，性别与年龄");
        scanf("%s %s %s %d", student[i].xuehao, student[i].name, student[i].sex, &student[i].age);
        printf("请输入五门课的成绩");
        for (int j = 0; j < 5; j++)
        {
            scanf("%d", &student[i].grade[j]);
        }
    }
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
            printf("\t%d", &student[i].grade[j]);
        }
        printf("\n");
    }
}
void searchxuehao()
{
    char kl[20];
    printf("请输入你需要查询的学号");
    scanf("%s", kl);
    for (int i = 0; i < studentnum; i++)
    {
        if (strcmp(student[i].xuehao, kl))
        {
            printf("该学生信息如下\n");
            printf("学号\t姓名\t性别\t年龄\t成绩1\t成绩2\t成绩3\t成绩4\t成绩5\n");
            printf("%s\t%s\t%s\t%d", student[i].xuehao, student[i].name, student[i].sex, student[i].age);
            return;
        }
    }
    printf("未找到该学生相关信息");
}
void searchname()
{
    char n[10];
    printf("请输入你需要查询的姓名");
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
    printf("未找到该学生相关信息");
}
void studentin()
{
    if (studentnum >= 10000)
    {
        printf("stuents' numbers over");
        return;
    }
    printf("请输入学号，姓名，性别与年龄");
    scanf("%s %s %s %d", student[studentnum].xuehao, student[studentnum].name, student[studentnum].sex, &student[studentnum].age);
    printf("请输入五门课的成绩");
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
    printf("请输入你想删除的学生姓名\n");
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
            printf("该生信息已删除");
            return;
        }
    }
    printf("未找到该学生相关信息");
}
void studentpaixu()
{
    if (studentnum == 0)
    {
        printf("未找到任何学生相关信息");
        return;
    }
    for (int i = 0; i < studentnum; i++)
    {
        for (int j = i; j < studentnum; j++)
        {
            if (strcmp(student[i].name, student[j].name) <= 0)
            {
                struct s uo = student[i];
                student[i] = student[j];
                student[j] = uo;
            }
        }
    }
}