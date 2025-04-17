#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <signal.h>
#include "uthash.h"
#include <fcntl.h>
#include <time.h>
#include <limits.h>
// typedef int (*Predicate)(int);
// int *filter(int *array, int length, Predicate predicate,
//             int *resultLength){
//                 int cnt=0;
//                 int *aln=(int *)malloc(sizeof(int *)*10);
//                 for(int i=0;i<length;i++){
//                     if(predicate(array[i])){
//                       aln[cnt]=array[i];
//                       cnt++;
//                     }
//                 }
//                 *resultLength=cnt;
//                 return aln;
//             }
// int isPositive(int num) { return num > 0; }
// int main(void) {
//     int array[] = {-3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
//     int length = sizeof(array) / sizeof(array[0]);
//     int resultLength;
//     int *filteredNumbers = filter(array, length, isPositive,&resultLength);
//     for (int i = 0; i < resultLength; i++) {
//       printf("%d ", filteredNumbers[i]);
//     }
//     printf("\n");
//     free(filteredNumbers);
//     return 0;
// }

// struct Student {
//     char *name;
//     int age;
// };

// void initializeStudent(struct Student *student, const char *name,
//                        int age) {
//     student->name = (char *)malloc(strlen(name) + 1);
//     strcpy(student->name, name);
//     student->age = age;
// }
// void aln(struct Student *s1,struct Student *s2){
//     free(s1->name);
//     s1->name=(char*)(malloc(strlen(s2->name)+1));
//     if(s1->name!=NULL){
//     strcpy(s1->name,s2->name);
//     }
// }
// int main(void) {
//     struct Student s1, s2;
//     initializeStudent(&s1, "Tom", 18);
//     initializeStudent(&s2, "Jerry", 28);
//     //s1 = s2;
//     aln(&s1,&s2);
//     s1.age=s2.age;
//     printf("s1的姓名: %s 年龄: %d\n", s1.name, s1.age);
//     printf("s2的姓名: %s 年龄: %d\n", s2.name, s2.age);
//     free(s1.name);
//     free(s2.name);
//     return 0;
// }

// int average(int nums[], int start, int end) {
//     if (start == end)
//         return nums[start];
//     int mid = (start + end) / 2;
//     int leftAvg = average(nums, start, mid);
//     int rightAvg = average(nums, mid + 1, end);
//     return (leftAvg & rightAvg) + ((leftAvg ^ rightAvg) >> 1);
// }
// int main(){
// int n;
// scanf("%d",&n);
// int aln[n];
// for(int i=0;i<n;i++){
//     scanf("%d",&aln[i]);
// }
// printf("%d", average(aln,0,n-1));
//     return 0;
// }

// union data {
//     int a;
//     double b;
//     short c;
// };
// typedef struct node {
//     long long a;
//     union data b;
//     void (*change)( struct node *n);
//     char string[0];
// } Node;
// void func(Node *node) {
//     for (size_t i = 0; node->string[i] != '\0'; i++)
//         node->string[i] = tolower(node->string[i]);
// }
// int main() {
//     const char *s = "WELCOME TO XIYOULINUX_GROUP!";
//     Node *P = (Node *)malloc(sizeof(Node) + (strlen(s) + 1) * sizeof(char));
//     strcpy(P->string, s);
//     P->change = func;
//     P->change(P);
//     printf("%s\n", P->string);
//     printf("%zu\n",sizeof(union data));
//     printf("%zu",sizeof(Node));
//     return 0;
// }

// int s(long long a){
//     int isprime=1;
//     if(a==2){
//         return isprime;
//     }
//     for(long long i=2;i<=sqrt(a);i++){
//         if(a%i==0){
//              isprime=0;
//              break;
//         }else{
//              isprime=1;
//         }
//     }
//     return isprime;
// }
// int main(){
//     long long n;
//     scanf("%lld",&n);
//     for(long long i=2;i<=sqrt(n);i++){
//         long long j=n-i;
//             if(n==i+j&&s(i)&&s(j)){
//                 printf("%lld=%lld + %lld ",n,i,j);
//                 break;
//             }
//     }
//     return 0;
// }

// int main(){
//    int aln[7],max=0;
//     for(int i=0;i<7;i++){
//        scanf("%d",&aln[i]);
//     }
//     for(int j=0;j<7;j++){
//        if(max<aln[j]){
//         max=aln[j];
//        }
//     }
//     printf("%d",max);
//     return 0;
// }

// int main(){
// int a,b;
// double sum=0;
//     scanf("%d %d",&a,&b);
//     for(int i=a;i<=b;i++){
//         sum+=(i*i+1/(i*1.0));
//     }
//     printf("%.6f",sum);
//     return 0;
// }

// int main(){
// int a,b,t,x,y,m;
// scanf("%d %d",&a,&b);
// x=a,y=b;
// while(b!=0){
//     t=a%b;
// 	a=b;
// 	b=t;
// }
//  m=x*y/a;
// printf("%d,%d",a,m);
//     return 0;
// }

// double s(long long a){
//     if(a==1){
//         return a;
//     }else{
//         a=a*s(a-1);
//         return a;
//     }
// }
// int main(){
//     int n;
//     double sum=1;
//     scanf("%d",&n);
//     for(int i=1;i<=n;i++){
//        sum+=1/(s(i)*1.0);
//     }
//     printf("%.8f",sum);
//     return 0;
// }

// int main(){
//     int i,n,sum=0,cnt=0;
//     scanf("%d",&n);
//     while(n>0){
//        sum+=n%10;
//        n/=10;
//        cnt++;
//     }
//   printf("%d %d",cnt,sum);
//     return 0;
// }

// int main(){
//     int n,h;
//     scanf("%d %d",&n,&h);
//     double t,sum=0;
//     for(int i=0;i<=n+2;n=1.0*n/2,t=1.0*n,i++){
//         sum+=(n+1.0*n/2);
//     }
//     printf("%.1f %.1f",sum,t);
//     return 0;
// }

// int main(){
//     int n,cnt=0;
//     scanf("%d",&n);
//     for(int i=1;i<=30;i++){
//         for(int j=1;j<=75;j++){
//             if(i*5+j*2+100-i-j==150&&cnt<n){
//                 printf("%d %d %d",i,j,100-i-j);
//                 if(cnt!=n-1){
//                     printf("\n");
//                 }
//                 cnt++;
//             }
//         }
//     }
//     return 0;
// }

// int k=0;
// void s(int z){
//     int aln[10000],cnt=0,sum=0;
//     for(int i=1;i<=z/2;i++){
//         if(z%i==0){
//             sum+=i;
//             aln[cnt]=i;
//             cnt++;
//         }
//     }
//     if(sum==z){
//         ++k;
//         if(k!=0&&k!=1){
//             printf("\n");
//         }
//         printf("%d = ",z);
//           for(int j=0;j<cnt;j++){
//             printf("%d",aln[j]);
//             if(aln[j]!=sum/2) printf(" ");
//             if(j!=cnt-1){
//                 printf("+ ");
//             }
//           }
//           sum=0;
//           cnt=0;
//     }
// }
// int main(){
//     int x,y,m=0;
//     scanf("%d %d",&x,&y);
//     for(int i=x;i<=y;i++){
//         s(i);
//     }
//     if(k==0){
//         printf("None");
//     }
//     return 0;
// }

// int s(int a){
//    int isprime=0;
//    if(a==2||a==1){
//     isprime=1;
//    }else{
//    for(int i=2;i<a;i++){
//       if(a%i==0){
//         isprime=0;
//         break;
//       }else{
//         isprime=1;
//       }
//    }
//    }
//    return isprime;
// }
// int main(){
//     int n;
//     scanf("%d",&n);
//     int t=n;
//     if(s(n)==1){
//         printf("error");
//     }else{
//     for(int j=2;j<=t;j++){
//         if(n%j==0&&s(j)==1){
//             while(n%j==0){
//             printf("%d",j);
//             if(n/j!=1){
//                 printf(" ");
//             }
//             n/=j;
//             }
//         }
//     }
//     }
//     return 0;
// }

// int main(){
//     int a,b,sum=0,cnt=0;
//     scanf("%d %d",&a,&b);
//     for(int i=a;i<=b;i++){
//         if(i<0){
//             printf("%5d",i);
//         }else{
//         printf("%5d",i);
//         }
//         cnt++;
//         sum+=i;
//         if(cnt==5){
//             printf("\n");
//             cnt=0;
//         }
//     }
//     if((b-a+1)%5==0)
//     printf("Sum = %d",sum);
//     else
//     printf("\nSum = %d",sum);
//     return 0;
// }

// int main(){
//     int h,n;
//     double sum=0,H,l=0;
//     scanf("%d %d",&h,&n);
//     H=(double)h;
//     for(int i=0;i<n;i++){
//         if(i==n-1){
//             sum+=(H);
//             H/=2;
//             break;
//         }
//         sum+=(H+H/2);
//         H/=2;
//     }
//     if(n==0){
//         printf("%.1f 0.0",sum);
//     }else{
//     printf("%.1f %.1f",sum,H);
//     }
//     return 0;
// }

// int k=0;
// int main(){
//     int n,sum=0,t;
//     scanf("%d",&n);
//     int x=pow(10,n-1);
//     int l=pow(10,n);
//     if(n==7){
//          for(int j=1500000;j<l;j++){
//             t=j;
//             while(t>0){
//            sum+=pow(t%10,n);
//            t/=10;
//             }
//            if(sum==j){
//             k++;
//             if(k!=1){
//                 printf("\n");
//             }
//             printf("%d",sum);
//             sum=0;
//             if(k==2){
//                 j+=5000000;
//             }else if(k==1){
//             j+=2440000;
//             }
//            }
//            sum=0;
//         }
//     }else{
//         for(int j=x;j<l;j++){
//             t=j;
//             while(t>0){
//            sum+=pow(t%10,n);
//            t/=10;
//             }
//            if(sum==j){
//             k++;
//             if(k!=1){
//                 printf("\n");
//             }
//             printf("%d",sum);
//             sum=0;
//            }
//            sum=0;
//         }
//     }
//     return 0;
// }

// int s(int a){
//    int isprime=0;
//    if(a==2||a==1){
//     isprime=1;
//    }else{
//    for(int i=2;i<a;i++){
//       if(a%i==0){
//         isprime=0;
//         break;
//       }else{
//         isprime=1;
//       }
//    }
//    }
//    return isprime;
// }
// int main(){
//     int n,cnt=0;
//     scanf("%d",&n);
//     for(int i=n-1;i>=sqrt(n);i--){
//      if(s(i)==1){
//         cnt++;
//         printf("%6d",i);
//         if(cnt==10){
//             break;
//         }
//      }
//     }
//     return 0;
// }

// int main(){
//     int n,x,sum=0,cnt=0;
//     scanf("%d",&n);
//     for(int i=1;i<=1000;i++){
//       x=i;
//       while(x>0){
//         sum+=x%10;
//         x/=10;
//       }
//       if(sum==n){
//         printf("%8d",i);
//         cnt++;
//       }
//       if(cnt==6){
//         printf("\n");
//         cnt=0;
//       }
//       sum=0;
//     }
//     return 0;
// }

// 菱形
//  int main(){
//      int n;
//      char x='*';
//      scanf("%d",&n);
//      for(int i=1;i<=n;i+2){
//          printf("%*c ",n-i,x);
//          for(int j=1;j<=(n-i)/2;j++){
//              printf("* ");
//          }
//          printf("\n");
//      }
//      return 0;
//  }

// int jiec(int n){
//     if(n==1){
//         return 1;
//     }else{
//         return n=n*jiec(n-1);
//     }
// }
// int main(){
//     int cnt=0;
//     double n,sum=1;
//     scanf("%lf",&n);
//     for(int i=2; ;i+2){
//      sum+=((1.0*(pow(-1,i/2)*pow(n,i)))/jiec(i)*1.0);
//      cnt++;
//      if((pow(n,i))/jiec(i)<0.00001){
//         break;
//      }
//     }
//     printf("cos(x)=%.6f\n",sum);
//     printf("count=%d",cnt);
//     return 0;
// }

// int main(){
//     char s[1000];
//     gets(s);
//     int len=strlen(s);
//     for(int i=0;i<len;i++){
//         if(s[i]>=65&&s[i]<=90){
//             if(s[i]==90){
//                 s[i]=97;
//             }else
//             s[i]+=33;
//         }else if(s[i]>=97&&s[i]<=122){
//             if(s[i]==122){
//                 s[i]=65;
//             }else
//             s[i]-=31;
//         }
//     }
//     for(int j=0;j<len;j++){
//         printf("%c",s[j]);
//     }
//     return 0;
// }

// int main(){
//     char ch[100];
//     int h=0,aln[1000],k=0,cnt=0;

//     for(int i=0; ;i++){
//        scanf("%c",&ch[i]);
//        if(ch[i]!=' '&&ch[i]!='.'){
//         cnt++;
//        }else if(cnt!=0&&ch[i]==' '||ch[i]=='.'){
//         if(k==0&&cnt!=0){
//             printf("%d",cnt);
//             k++;
//         }else if(cnt!=0){
//         printf(" %d",cnt);
//         k++;
//         }
//         cnt=0;
//        }
//        if(ch[i]=='.') break;
//     }
//     return 0;
// }

// int main(){
//     int max,aln[10],t=100,n,i=0;
//     scanf("%d",&n);
//     while(n>0){
//      scanf("%d",&aln[i]);
//      i++;
//      n--;
//     }
//     max=aln[0];
//     for(int j=0;j<i;j++){
//        if(aln[j]>max){
//         max=aln[j];
//        }
//     }
//     for(int z=0;z<i;z++){
//         if(aln[z]==max&&t>=z){
//           t=z;
//         }
//     }
//     printf("%d %d",max,t);
//     return 0;
// }

// int main(){
//     int n,cnt=0;
//     scanf("%d",&n);
//     if(n<0){
//     printf("0");
//     }else{
//     while(n>0){
//         n/=2;
//         cnt++;
//     }
//     printf("%d",32-cnt);
//     }
//     return 0;
// }

// struct strbuf {
//   int len;
//   int alloc;
//   char *buf;
// };
// void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len){
//     strncat(sb->buf,(char*)data,len);
//     printf("%s",sb->buf);
// }
// int main(){
//     struct strbuf *sn;
//     char *str;
//     sn->buf="loveforvevr";
//     scanf("%s",str);
//     int len=strlen(str);
//     strbuf_insert(sn,4,str,len);
//     return 0;
// }

// int main(){
//     int a,b;
//     int aln[100][100];
//     scanf("%d",&a);
//     scanf("%d",&b);
//     for(int i=1;i<=a;i++){
//         for(int j=1;j<=b;j++){
//            printf("(%d,%d) ",i,j);
//         }
//         printf("\n");
//     }
//     return 0;
// }

// int main(){
//     int n,aln1,aln2,i=0;
//     scanf("%d",&n);
//     char name[4];
//     char *aln;
//     for(int i=0;i<n;i++){
//      scanf("%s %d %d",name,&aln1,&aln2);
//      if(aln1<15||aln1>20||aln2<50||aln2>70){
//               *(aln+i)=name;
//               i++;
//            }
//         }
//       for(int j=0;j<=i;j++){
//         if(j==0){
//           printf("%s",*(aln+j));
//         }else{
//          printf("\n%s",*(aln+j));
//         }
//       }
//     return 0;
// }

// int main() {
//     int n;
//     scanf("%d",&n);
//     char name[4];
//     int a,b;
//     char names[n][4];
//     int count = 0;
//     for (int i = 0; i < n; i++) {
//         scanf("%s %d %d", name, &a, &b);
//         if (a < 15 || a > 20 || b < 50 || b > 70) {
//             snprintf(names[count], sizeof(names[count]), "%s", name);
//             count++;
//         }
//     }
//     for (int i = 0; i < count; i++) {
//         printf("%s\n", names[i]);
//     }

//     return 0;
// }

// int main(){
//     double da,s,xiao;
//     scanf("%lf %lf %lf",&da,&s,&xiao);
//     double x;
//     if(s==0){
//         x=da*2.455;
//     }else{
//         x=da*1.26;
//     }
//     if(x>xiao){
//         printf("%.2f T_T",x);
//     }else{
//         printf("%.2f ^_^",x);
//     }
//     return 0;
// }

// int main(){
//     int n;
//     scanf("%d",&n);
//     char aln[80][80],ch='A';
//     for(int i=0;i<2*n-1;i++){
//         if(i==0||i==2*n-2){
//             for(int j=0;j<2*n-1;j++){
//                 aln[i][j]=ch;
//             }
//         }
//         ch++;
//     }
//     return 0;
// }

// int main(){
//     char *s;
//     s=(char*)malloc(100*sizeof(char));
//     s="123\0132";
//     strncpy(s,"#",1);
//     printf("%s",s);
//     for(int i=0;*(s+i)!="#";i++){
//       if(*(s+i)=="\0"){
//         *(s+i)="A";
//       }
//     }
//     int len=strlen(s);
//     printf("%d",len);
//     return 0;
// }

// int main()
// {
//    FILE *fp = NULL;

//    fp = fopen("/tmp/test.txt", "w+");
//    fprintf(fp, "This is testing for fprintf...\n");
//    fputs("This is testing for fputs...\n", fp);
//    fclose(fp);
// }

// int s(int a){
//    int isprime=1;
//    if(a==1||a==2){
//       isprime=0;
//    }
//    for(int i=2;i<=sqrt(a);i++){
//       if(a%i==0){
//          isprime=1;
//          break;
//       }else isprime=0;
//    }
//    return isprime;
// }
// int main(){
//    int n;
//    scanf("%d",&n);
//    if(s(n)==0){
//       printf("是素数");
//    }else{
//       printf("不是素数");
//    }
//    return 0;
// }

// int main(){
//    int n;
//    char ch='A';
//    scanf("%d",&n);
//    int x=2*n-1;  //x=5
//    char aln[100][100];
//    for(int i=0;i<n;i++){
//       for(int j=i;j<x-i;j++){
//          aln[i][j]=ch;
//       }
//       for(int z=i+1;z<x-i-1;z++){
//          aln[z][i]=ch;
//          aln[z][x-1-i]=ch;
//       }
//       for(int h=i;h<x-i;h++){
//          aln[x-1-i][h]=ch;
//       }
//       ch++;
//    }
//    for(int k=0;k<n*2-1;k++){
//       for(int k1=0;k1<n*2-1;k1++){
//          printf("%c",aln[k][k1]);
//       }
//       printf("\n");
//    }
//    return 0;
// }

// int main(){
//     int n,aln[10],max,cnt=11;
//     scanf("%d",&n);
//     for(int i=0;i<n;i++){
//         scanf("%d",&aln[i]);
//     }
//     max=aln[0];
//     for(int j=0;j<n;j++){
//        if(max<aln[j]){
//         max=aln[j];
//         cnt=j;
//        }
//     }
//     if(max==aln[0]) printf("%d 0",max);
//     else printf("%d %d",max,cnt);
//     return 0;
// }

// int main(){
//     int n,aln[100],key;
//     scanf("%d",&n);
//     for(int i=0;i<n;i++){
//         scanf("%d",&aln[i]);
//     }
//     scanf("%d",&aln[n]);
//     int len=n+1;
//     for(int j=0;j<len;j++){
//         for(int h=0;h<len-j-1;h++){
//         if(aln[h]>aln[h+1]){
//             int t=aln[h];
//             aln[h]=aln[h+1];
//             aln[h+1]=t;
//         }
//         }
//     }
//     for(int z=0;z<len;z++){
//         printf("%d ",aln[z]);
//     }
//     return 0;
// }

// void swap(int *a,int *b){
//     int temp=*a;
//     *a=*b;
//     *b=temp;
// }
// int main(){
//     int n,aln[100],min,max,a=0,b=0;
//     scanf("%d",&n);
//     for(int i=0;i<n;i++){
//        scanf("%d",&aln[i]);
//     }
//     min=aln[0],max=aln[0];
//     for(int j=0;j<n;j++){
//        if(min>aln[j]) {
//         min=aln[j];
//         a=j;
//        }
//        if(max<aln[j]){
//         max=aln[j];
//         b=j;
//        }
//     }
//     printf("min=%d max=%d\n",min,max);
//     printf("a=%d b=%d\n",a,b);
//     if(n==2){
//     swap(&aln[n-1],&aln[b]);
//     }else{
//     swap(&aln[0],&aln[a]);
//     max=aln[0];
//     for(int j=0;j<n;j++){
//        if(max<aln[j]){
//         max=aln[j];
//         b=j;
//        }
//     }
//     swap(&aln[n-1],&aln[b]);
//     }
//     for(int z=0;z<n;z++){
//         printf("%d ",aln[z]);
//     }
//     return 0;
// }

// int main(){
//     int n,aln[100],a[100]={0},cnt=0;
//     scanf("%d",&n);
//     for(int i=0;i<n;i++){
//         scanf("%d",&aln[i]);
//         a[aln[i]]=1;
//     }
//     for(int z=0;z<n;z++){
//         if(a[aln[z]]==1&&cnt!=0){
//             printf(" %d",aln[z]);
//             a[aln[z]]-=1;
//             cnt++;
//         }
//         if(a[aln[z]]==1&&cnt==0){
//             printf("%d",aln[z]);
//             a[aln[z]]-=1;
//             cnt++;
//         }
//     }
//     return 0;
// }

// pta5

// int main(){
//     int aln1[20]={0},aln2[20]={0},c[20]={0},a=0,cnt=0;
//     scanf("%d",&aln1[0]);
//     for(int i=1;i<=aln1[0];i++){
//       scanf("%d",&aln1[i]);
//     }
//     scanf("%d",&aln2[0]);
//     for(int j=1;j<=aln2[0];j++){
//       scanf("%d",&aln2[j]);
//     }
//     for(int k=1;k<=aln1[0];k++){
//         for(int o=1;o<=aln2[0];o++){
//             if(aln1[k]==aln2[o]){
//                 a=1;
//                 break;
//             }
//         }
//         if(a==0) {
//             c[cnt]=aln1[k];
//             cnt++;
//         }
//         a=0;
//     }
//     a=0;

//     for(int k=1;k<=aln2[0];k++){
//         for(int o=1;o<=aln1[0];o++){
//             if(aln2[k]==aln1[o]){
//                 a=1;
//                 break;
//             }
//         }
//         if(a==0) {
//             c[cnt]=aln2[k];
//             cnt++;
//         }
//         a=0;
//     }
//         for(int y=0;y<cnt;y++){
//         printf("%d ",c[y]);
//     }
//     printf("\n");
//     int pi=0,pp=0;
//     for(int p=0;p<cnt;p++){
//         for(int p1=p;p1<cnt;p1++){
//            if(c[p]==c[p1]&&p!=p1){
//              pi=1;
//              break;
//            }
//         }
//         if(pi==0&&pp==0){
//         printf("%d",c[p]);
//         pp++;
//         }else if(pi==0){
//             printf(" %d",c[p]);
//         }
//         pi=0;
//     }
//     return 0;
// }

// int main(){
//    int aln[10],sum=0;
//    for(int i=0;i<10;i++){
//       scanf("%d",&aln[i]);
//    }
//    for(int j=0;j<10;j++){
//       if(aln[j]%5==0){
//          sum+=aln[j];
//       }
//    }
//    printf("%d",sum);
//    return 0;
// }

// int main(){
//    int aln1[1000],aln2[1000]={1},x,i=0,max=0,len=0;
//    scanf("%d",&aln1[0]);
//    for(int i=1;i<=aln1[0];i++){
//       scanf("%d",&aln1[i]);
//    }
//    if(aln1[0]==1){
//     printf("%d %d",aln1[1],1);
//    }else{
//    len=aln1[0];
//    for(int j=1;j<=len;j++){
//       for(int z=1;z<=len;z++){
//         if(aln1[j]==aln1[z]&&j!=z){
//             aln2[j]++;
//         }
//       }
//    }
//    for(int k=1;k<=len;k++){
//     if(max<aln2[k]){
//         max=aln2[k];
//         x=k;
//     }
//    }
//    printf("%d %d",aln1[x],max+1);
//    }
//    return 0;
// }

// int main(){
//    int n,x,aln[20],cnt=0;
//    scanf("%d %d",&n,&x);
//    for(int i=0;i<n;i++){
//       scanf("%d",&aln[i]);
//    }
//    for(int j=0;j<n;j++){
//       if(aln[j]==x){
//          printf("%d",j);
//          break;
//       }
//       cnt++;
//    }
//    if(cnt==n) printf("Not Found");
//    return 0;
// }

// int main(){
//    int n,x,aln[1000]={0};
//    scanf("%d",&n);
//    for(int i=0;i<n;i++){
//       scanf("%d",&aln[i]);
//    }
//    scanf("%d",&x);
//    aln[n]=x;
//    int len=n+1;
//    for(int j=0;j<len;j++){
//       for(int z=0;z<=len-j;z++){
//          if(aln[z]<aln[z+1]){
//             int t=aln[z+1];
//             aln[z+1]=aln[z];
//             aln[z]=t;
//          }
//       }
//    }
//    for(int h=0;h<len;h++){
//       printf("  %d",aln[h]);
//    }
//    return 0;
// }

// int main(){
//    char *s;
//    s=(char*)malloc(sizeof(char)*9998);
//    scanf("%s",s);
//    int len=strlen(s);
//    int aln[1000]={0};
//    for(int i=0;i<len;i++){
//       aln[s[i]]=1;
//    }
//    for(int j=0;j<len;j++){
//       if(aln[s[j]]==1){
//       printf("%c",s[j]);
//       aln[s[j]]-=100;
//       }
//    }
//    free(s);
//    return 0;
// }

// //二阶 fun1
// int fun1(int arr[2][2],int i,int m,int n)
// {
//     int res2;
//     //i=0,n=1,m=0
//     res2=arr[i][m]*arr[i+1][n]-arr[i][n]*arr[i+1][m];
//     return res2;
//  }

// //从三阶行列式中框选出二阶行列式
// int (*cut(int arr2[3][3], int x, int y,int arr3[2][2]))[2] //x表示需要删除的行数，y表示需要删除的列数
//  {
//      static int static_arr3[2][2];

//      int a=0;
//      int b=0;
//      int i,j;

//      for(i=0;i<3;i++){
//          if(i==x){
//              continue;
//         }
//         for(j=0;j<3;j++){
//              if(j==y){
//                 continue;
//              }
//         arr3[a][b]=arr2[i][j];
//         b++;
//         }
//     a++;
//     b=0; //处理完一行后，将索引重置为0
//     if(a==2){
//         break;
//     }
//     }
//     int (*arr4)[2]=static_arr3;
//     return arr4;
//  }

//  //三阶 fun2
// int fun2(int arr1[3][3])
//  {    int arrA[2][2],arrB[2][2],arrC[2][2];
//      cut(arr1,0,0,arrA); //分别表示出对应的二阶行列式 //  a00 a01 a02
//     cut(arr1,0,1,arrB);                                   //  a10 a11 a12
//     cut(arr1,0,2,arrC);                                 //  a20 a21 a22
//      int n[3];
//      n[0]=fun1(arrA,1,1,2);        //j=0:m=1,n=2
//     n[1]=fun1(arrB,1,0,2);        //j=1:m=0,n=2
//     n[2]=fun1(arrC,1,0,1);        //j=2:m=0,n=1

//     int res3=0;
//     int j;
//      for(j=0;j<3;j++){
//          res3+=(int)pow(-1, j)*n[j]*arr1[0][j];
//      }
//     return res3;

//    }

// int reverse(int x) {
//     long long aln[32],len=0,num=0;
//      if(x==0||x>pow(2,31)-1||x<-pow(2,31)){
//         num=0;
//         return num;
//     }else if(x>0&&x<=pow(2,31)-1){
//         while(x>0){
//             aln[len]=x%10;
//             x/=10;
//             len++;
//         }
//     }else if(x<0&&x>=-pow(2,31)){
//         int f=-x;
//         while(f>0){
//             aln[len]=f%10;
//             f/=10;
//             len++;
//         }
//         for(int i=0;i<=len;i++){
//             aln[i]-=2*aln[i];
//         }
//     }
//     int k=0;
//     while(k<len){
//     num+=aln[k]*pow(10,len-k-1);
//     k++;
//     }
//     if(num==0||num>pow(2,31)-1||num<-pow(2,31)){
//         num=0;
//         return num;
//     }
//     return num;
// }

// int main(){
//     printf("%d",reverse(1534236469));
//     return 0;
// }

// int myAtoi(char* s) {
//     int len=strlen(s),aln[200],cnt=0;
//     for(int i=0;i<len-1;i++){
//         if(i==0&&s[i]>=48&&s[i]<=57&&s[i+1]>=48&&s[i+1]<=57){
//             aln[cnt]=(int)s[i]-48;
//             cnt++;
//         }else{
//             if(s[i]>=48&&s[i]<=57&&s[i+1]>=48&&s[i+1]<=57){
//                 aln[cnt]=(int)s[i]-48;
//                 cnt++;
//             }
//         }
//     }
//     int llg=0;
//     if(cnt==len){
//     aln[cnt]=(int)s[len]-48;
//     llg=cnt+1;
//     }
//     else {
//         llg=cnt;
//     }
//     int k=0;
//     int num=0;
//     whlie(k<llg){
//     num+=aln[k]*pow(10,llg-k);
//     k++;
//     }
//     return num;
// }

// int main(){
// int n=2;
// char s[2]={'a','b'};
// int stk[n + 1], top = 0;
//     for (int i = 0; i < n; i++) {
//         char ch ='a';
//         if (ch) {
//             if (top == 0 || stk[top - 1] != ch) {
//                 return 123;
//             }
//             top--;
//         } else {
//             stk[top++] = s[i];
//         }
//     }
//     return 123;
// }

// int main(){
//     int nums[]={5,3,3,1,1},numsSize=sizeof(nums)/sizeof(nums[0]);
//     int slow=1,fast=1;
//     for(;fast<numsSize;fast++){
//         if(nums[fast]!=nums[fast-1]){
//             nums[slow]=nums[fast];
//             slow++;
//         }
//     }
//     printf("%d\n",slow);
//     for(int j=0;j<slow;j++){
//     printf("%d ",nums[j]);
//     }
//     return 0;
// }

// struct Student{
//     char *name;
//     int xuehao;
//     int grade[3];
// }student[10];
// int main(){
//     double average[10];
//     for(int i=0;i<10;i++){
//         scanf("%s %d %d %d %d",&student[i].name,&student[i].xuehao,&student[i].grade[0],&student[i].grade[1],&student[i].grade[2]);
//     }
//     for(int j=0;j<10;j++){
//         average[j]=(student[j].grade[0]+student[j].grade[1]+student[j].grade[2])*1.0/3.0;
//     }
//     for(int z=0;z<10;z++){
//         for(int h=0;h<10-z;h++){
//             if(average[h]<average[h+1]){
//                 double temp=average[h+1];
//                 average[h+1]=average[h];
//                 average[h]=temp;
//             }
//         }
//     }
//     for(int p=0;p<10;p++){
//         printf("%.2lf\n",average[p]);
//     }
//     return 0;
// }

// int cmp(const void *a,const void *b){
//     return (*(int*) a - *(int *)b);
// }
// int main(){
//     int aln[]={4,9,8,1,2,6,7,3,5},len=sizeof(aln)/sizeof(aln[0]);
//     qsort(aln,len,sizeof(int),cmp);
//     for(int i=0;i<len;i++){
//         printf("%d ",aln[i]);
//     }
//     return 0;
// }

// int reverse( int number ){
//     int y=0;
//     if(number>0){
//         while(number>0){
//             y=y*10+number%10;
//             number/=10;
//         }
//     }else{
//         number-=2*number;
//         while(number>0){
//             y=y*10+number%10;
//             number/=10;
//         }
//         y-=2*y;
//     }
//     return y;
// }

// int main()
// {
//     int n;
//     scanf("%d", &n);
//     printf("%d\n", reverse(n));
//     return 0;
// }

// double funcos( double e, double x ){
//     double cos=0;
//     for(int i=0; ;){
//         double num=1;
//         for(int j=1;j<=i;j++){
//             num*=j;
//         }
//         cos+=pow(-1,i/2)*((pow(x,i)*1.0/num));
//         double p=(pow(x,i)*1.0/num);
//         if(p>0&&p<e||p<0&&-p<e) break;
//         i=i+2;
//         num=0;
//     }
//     return cos;
// }
// int main()
// {
//     double e, x;
//     scanf("%lf %lf", &e, &x);
//     printf("cos(%.2f) = %.6f\n", x, funcos(e, x));
//     return 0;
// }

// int I(int a){
//     int isprime=1;
//     if(a==1) return isprime=0;
//     else{
//         for(int i=2;i<=sqrt(a);i++){
//             if(a%i==0){
//                 isprime=0;
//                 return isprime;
//             }
//         }
//     }
//     return isprime;
// }
// int main(){
//     int cnt=0,n,k,p=0,sum=0;;
//     scanf("%d %d",&n,&k);
//     for(int i=n; ;i--){
//         if(cnt==k||i==1) break;
//         if(p==0&&I(i)!=0){
//             sum+=i;
//             printf("%d",i);
//             p++;
//             cnt++;
//         }else if(p!=0&&I(i)!=0){
//             sum+=i;
//             printf("+%d",i);
//             cnt++;
//         }
//     }
//     printf("=%d",sum);
//     return 0;
// }

// #define MAXLENGTH 100
// int isPalindrome(const char* str, char* pch);
// int main(){
//     char str[MAXLENGTH],mid;
//     scanf("%s",str);
//     if(isPalindrome(str, &mid))
//         printf("是回文！中间字符是%c\n",mid);
//     else
//         printf("不是回文！中间字符是%c\n",mid);
//     return 0;
// }
// int isPalindrome(const char* str, char* pch){
//     int len=strlen(str);
//     if(len%2==0) {
//     *pch=str[len/2-1];
//     return 0;
//     }
//     else *pch=str[len/2];
//     for(int i=0;i<len/2;i++){
//         if(str[i]!=str[len-i-1]){
//             return 0;
//         }
//     }
//     return 1;
// }

// #define p 3.1415926
// int main()
// {
//         int num;
//         double r,h,v;
//         do
//         {	printf("1-Ball\n2-Cylinder\n3-Cone\nother-Exit\nPlease enter your command:\n");
//             scanf("%d",&num);
//             if(!(num==1||num==2||num==3))
//                 break;
//             if(num==1)
//             {
//                 printf("Please enter the radius:\n");
//                 scanf("%lf",&r);
//                 v=4.0/3*p*(r*r*r);
//                 printf("%.2lf\n",v);
//                 continue;
//             }
//             if(num==2)
//             {
//                 printf("Please enter the radius and the height:\n");
//                 scanf("%lf %lf",&r,&h);
//                 v=p*(r*r)*h;
//                 printf("%.2lf\n",v);
//                 continue;
//             }
//             if(num==3)
//             {
//                 printf("Please enter the radius and the height:\n");
//                 scanf("%lf %lf",&r,&h);
//                 v=1.0/3*p*(r*r)*h;
//                 printf("%.2lf\n",v);
//                 continue;
//             }
//         }while(1);
//         return 0;
//     }

// int main(){
//     char *s="101";
//     int sum=0,len=strlen(s);
//     printf("%d\n",len);
//     for(int i=0;i<len;i++){
//         sum+=(s[i]-48)*pow(2,len-i-1);
//     }
//     printf("%d",sum);
//     return 0;
// }

// int main(){
//     char *str="fweasfasefasf";
//     char flag='a';
//     char **str2=(char**)malloc(sizeof(char*)*20);
//     int len=strlen(str);
//     for(int i=0;i<len;i++){
//         while(str[i]==flag){

//         }
//     }
//     return 0;
// }

// char* addBinary(char* a, char* b) {
//     int x=0,y=0,lena=strlen(a),lenb=strlen(b);
//     int max=fmax(lena,lenb);
//     for(int i=0;i<lena;i++){
//         x+=(a[i]-48)*pow(2,lena-i-1);
//     }
//     for(int i=0;i<lena;i++){
//         y+=(b[i]-48)*pow(2,lenb-i-1);
//     }
//     char str[max+2];
//     int sum=x,carry=y;
//     while(carry){
//         int temp=sum;
//         sum=temp^carry;
//         carry=(temp&carry)<<1;
//     }
//     sprintf(str,"%d",sum);
//     return str;
// }
// int main(){
//     char *x="11";
//     char *y="1";
//     printf("%s",addBinary(x,y));
//     return 0;
// }

// int main(){
//     int h,m,s,time;
//     scanf("%d:%d:%d",&h,&m,&s);
//     scanf("%d",&time);
//     int t=time+s;
//     s=t-60;
//     if(s<0) s+=60;
//     t/=60;
//     m+=t;
//     int z=m;
//     z/=60;
//     h+=z;
//     m%=60;
//     if(h==24) h=0;
//     if(m==60) m=0;
//     printf("%02d:%02d:%02d",h,m,s);
//     return 0;
// }

// struct people{
//     char name[10];
//     int birthday;
//     char phone[17];
// };
// void change(struct people *a,struct people *b){
//     struct people temp=*a;
//     *a=*b;
//     *b=temp;
// }
// int main(){
//     int h;
//     scanf("%d",&h);
//     struct people s[h];
//     for(int i=0;i<h;i++){
//         scanf("%s %d %s",s[i].name,&s[i].birthday,s[i].phone);
//     }
//     for(int i=0;i<h;i++){
//         for(int j=0;j<h-i;j++){
//             if(s[j].birthday<s[j+1].birthday){
//                 change(&s[j],&s[j+1]);
//             }
//         }
//     }
//     int isprime=0;
//     for(int j=h-1;j>=0;j--){
//         if(isprime==0){
//             printf("%s %d %s",s[j].name,s[j].birthday,s[j].phone);
//             isprime++;
//         }else{
//             printf("\n%s %d %s",s[j].name,s[j].birthday,s[j].phone);
//         }
//     }
//     return 0;
// }

// struct p{
//     int sex;
//     char name[8];
// };
// int main(){
//     int people,isprime=0;
//     scanf("%d",&people);
//     struct p hh[people];
//     for(int i=0;i<people;i++){
//         scanf("%d %s",&hh[i].sex,hh[i].name);
//     }
//     for(int i=0;i<people;i++){
//         for(int j=people-1;j>=0;j--){
//             if(hh[i].sex+hh[j].sex==1&&i!=j){
//                 if(isprime==0){
//                 printf("%s %s",hh[i].name,hh[j].name);
//                 isprime++;
//                 }else{
//                 printf("\n%s %s",hh[i].name,hh[j].name);
//                 }
//                 hh[i].sex=-2,hh[j].sex=-2;
//             }
//         }
//     }
//     return 0;
// }

// struct number{
//     int up;
//     char c;
//     int down;
// };
// int gys(int a,int b){
//     int t;
//     while(b!=0){
//   	t=a%b;
// 	a=b;
// 	b=t;
//   }
//   return a;
// }
// int main(){
//     struct number chu[2];
//     for(int i=0;i<2;i++){
//         scanf("%d%c%d",&chu[i].up,&chu[i].c,&chu[i].down);
//     }
//     int fm=gys(chu[0].down,chu[1].down);
//     int x,s;
//     x=(chu[0].down*chu[1].down)/fm;
//     s=chu[0].up*(x/chu[0].down)+chu[1].up*(x/chu[1].down);
//     int g=gys(x,s);
//     if(x/g!=1){
//     printf("%d/%d",s/g,x/g);
//     }else{
//         printf("%d",s/g);
//     }
//     return 0;
// }

// struct s{
//     char name[10];
//     float basic;
//     float move;
//     float out;
// };
// int main(){
//     int n,isprime=0;
//     scanf("%d",&n);
//     struct s p[n];
//     for(int i=0;i<n;i++){
//         scanf("%s %f %f %f",p[i].name,&p[i].basic,&p[i].move,&p[i].out);
//     }
//     for(int i=0;i<n;i++){
//         if(isprime==0){
//         printf("%s %.2f",p[i].name,p[i].basic+p[i].move-p[i].out);
//         isprime++;
//         }
//         else
//         printf("\n%s %.2f",p[i].name,p[i].basic+p[i].move-p[i].out);
//     }
//     return 0;
// }

// struct s{
//     char testnumber[16];
//     int sj;
//     int test;
// };
// int main(){
//     int n,isprime=0;
//     scanf("%d",&n);
//     struct s x[n];
//     for(int i=0;i<n;i++){
//         scanf("%s %d %d",x[i].testnumber,&x[i].sj,&x[i].test);
//     }
//     int choose;
//     scanf("%d",&choose);
//     int aln[choose];
//     for(int i=0;i<choose;i++){
//         scanf("%d",&aln[i]);
//     }
//     for(int j=0;j<choose;j++){
//         for(int k=0;k<n;k++){
//             if(aln[j]==x[k].sj&&isprime==0){
//                 printf("%s %d",x[k].testnumber,x[k].test);
//                 isprime++;
//             }else if(aln[j]==x[k].sj&&isprime!=0){
//                 printf("\n%s %d",x[k].testnumber,x[k].test);
//             }
//         }
//     }
//     return 0;
// }

// struct s{
//     char name[5];
//     int xuehao;
//     int score[3];
// };
// double average(int a,int b,int c){
//     return ((a+b+c)/3.0);
// }
// int main(){
//     struct s p[5];
//     for(int i=0;i<5;i++){
//         scanf("%s %d",p[i].name,&p[i].xuehao);
//         for(int j=0;j<3;j++){
//             scanf("%d",&p[i].score[j]);
//         }
//     }
//     for(int k=0;k<5;k++){
//         printf("%s %d %.2f\n",p[k].name,p[k].xuehao,average(p[k].score[0],p[k].score[1],p[k].score[2]));
//     }
//     return 0;
// }

// int main(){
//     char s[]="A man, a plan, a canal: Panama";
//     int len=strlen(s),j=0;
//     char n[len];
//     for(int i=0;i<len;i++){
//         if(s[i]>='a'&&s[i]<='z'||s[i]>='A'&&s[i]<='Z'||s[i]>='0'&&s[i]<='9'){
//             n[j]=s[i];
//             j++;
//         }
//     }
//     for(int k=0;k<=j;k++){
//         printf("%c",n[k]);
//     }
//     return 0;
// }

// struct film{
//     char name[20];
//     int rating;
//     struct film*next;
// };
// int main(){
//     struct film*head;
//     struct film*prev,*current;
//     while()
//     current=(struct film*)malloc(sizeof(struct film));
//     if(head==NULL){
//         head=current;
//     }else{
//         prev->next=current;
//         current->next=NULL;
//     }
//     return 0;
// }

// struct Node {
//     int data;
//     struct Node* next;
// };
// // 创建链表
// struct Node* createList() {
//     struct Node* head = NULL;
//     return head;
// }
// // 插入结点
// void insertNode(struct Node** head, int data) {
//     struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
//     newNode->data = data;
//     newNode->next = *head;
//     *head = newNode;
// }
// // 删除结点
// void deleteNode(struct Node** head, int data) {
//     struct Node* temp = *head, *prev;
//     if (temp != NULL && temp->data == data) {
//         *head = temp->next;
//         free(temp);
//         return;
//     }
//     while (temp != NULL && temp->data != data) {
//         prev = temp;
//         temp = temp->next;
//     }
//     if (temp == NULL) return;
//     prev->next = temp->next;
//     free(temp);
// }
// // 遍历链表
// void traverseList(struct Node* head) {
//     struct Node* temp = head;
//     while (temp != NULL) {
//         printf("%d ", temp->data);
//         temp = temp->next;
//     }
// }

// int main() {
//     struct Node* head = createList();
//     insertNode(&head, 1);
//     insertNode(&head, 2);
//     insertNode(&head, 3);
//     traverseList(head);
//     deleteNode(&head, 3);
//     printf("\n");
//     traverseList(head);
//     return 0;
// }

// struct film{
//     char name[20];
//     int money;
//     struct film *next;
// };
// struct film* creatlist(struct film *node){
//         node=NULL;
//         return node;
// }
// void insert(struct film**head,int m){
//     struct film*newnode=(struct film*)malloc(sizeof(struct film));
//     newnode->money=m;
//     newnode->next=*head;
//     *head=newnode;
// }
// void printlist(struct film*head){
//     while(head!=NULL){
//         printf("%d ",(head)->money);
//         head=head->next;
//     }
// }
// void dele(struct film**head,int flag){
//     struct film *temp=*head,*front;
//     if(temp==NULL) return;
//     while(temp!=NULL&&temp->money!=flag){
//         front=temp;
//         temp=temp->next;
//     }
//     if(temp->money==flag){
//         if(temp==*head){
//             temp=temp->next;
//         }else{
//             front->next=temp->next;
//         }
//         free(temp);
//     }
// }
// int main(){
//     struct film *head=creatlist(head);
//     insert(&head,1);
//     insert(&head,2);
//     insert(&head,3);
//     printlist(head);
//     dele(&head, 2);
//     printf("\n");
//     printlist(head);
//     return 0;
// }

// int main(int argc,char **argv){
//     int n=0,left=0;
//     for(int right=0;right<=len;right++){
//       if(str[right]==terminator||right==len-1){
//         a[n]->buf=NULL;
//         a[n]->len=0;
//         a[n]->alloc=0;
//         strbuf_add(a[n],str+right,right-left);
//         left=right+1;
//         n++;
//         a[n]=NULL;
//       }
//     }
//     return a;
//     return 0;
// }

// int main(){
//     int aln[]={1,5,4,31,2};
//     int *kl=(int *)malloc(sizeof(int)*5);
//     kl=aln;
//     for(int i=0;i<5;i++){
//         printf("%d ",kl[i]);
//     }
//     // free(kl);
//     return 0;
// }

// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>
// #include <getopt.h>
// int main(int argc,char**argv){
//         int flag;
//         char *str="a::b:c:d";
//         while((flag=getopt(argc,argv,str))!=-1){
//            printf("flag = %c\t\t",flag);
//            printf("optarg = %s\t\t",optarg);
//            printf("optind = %d\t\t",optind);
//            printf("argv[optind] = %s\n",argv[optind]);
// }
// return 0;
// }

// void toLowerString(char *str) {
//     while (*str) {
//         *str = tolower(*str);
//         str++;
//     }
// }
// int main() {
//     char str = "HELLO, WORLD!";
//     toLowerString(str);
//     printf("Lowercase: %sn", str);
//     return 0;
// }

// int main(){
//     // printf("color\n");
//     // printf("color\n");
//     // printf("\033[32;1m color\033[0m\n");//  粗体和绿色
//     char str1[]="abc";
//     char str2[]="def";
//     strncat(str1,str2,3);
//     printf("%s",str1);
//     return 0;
// }

// typedef struct con con;
// struct con{
//     int xh;
//     char name[20];
//     char tel[20];
//     struct con *next;
// };
// con* creatList(){
//     con*node=(con*)malloc(sizeof(con));
//     int n;
//     scanf("%d",&n);
//     for(int i=0;i<n;i++){
//         scanf("%d",&node->xh);
//         scanf("%s",node->name);
//         scanf("%s",node->tel);
//         node=node->next;
//     }
//     node->next=NULL;
//     return node;
// }
// int main(){
//     con *head,*p;
//     head=creatList();
//     for(p=head;p!=NULL;p=p->next )
//         printf("%d %s %s\n",p->xh ,p->name ,p->tel );
//     return 0;
// }

// struct ListNode {
//     int data;
//     struct ListNode *next;
// };

// struct ListNode *Createlist(int n);
// struct ListNode *Del_absrepeat( struct ListNode **head );
// void Printlist(struct ListNode *head);
// int main()
// {
//     struct ListNode *head = NULL,*head2=NULL;
//     int n;
//     scanf("%d",&n);
//     head = Createlist(n);
//     printf("原始链表：");
//     Printlist(head);

//    head2=Del_absrepeat( &head );
//    printf("删除重复结点的链表：");
//    Printlist(head);

//    printf("被删除的结点组成的链表：");
//    Printlist(head2);
//    return 0;
// }
// void Printlist(struct ListNode *head)
// {
//     struct ListNode *p;
//     for ( p = head; p != NULL; p = p->next )
//             printf("%d ", p->data);
//         printf("\n");
// }
// struct ListNode *Createlist(int n){
//     struct ListNode*head=NULL;
//     int number;
//     for(int i=0;i<n;i++){
//         scanf("%d",&number);
//         struct ListNode*nnode=(struct ListNode*)malloc(sizeof(struct ListNode));
//         nnode->data=number;
//         nnode->next=head;
//         head=nnode;
//     }
//     return head;
// }
// struct ListNode *Del_absrepeat(struct ListNode **head) {
//     if (*head == NULL) return NULL;
//     struct ListNode *current = *head;
//     struct ListNode *prev = NULL;
//     struct ListNode *deleted_head = NULL;
//     struct ListNode *deleted_tail = NULL;
//     int seen[1000000] = {0};
//     while (current != NULL) {
//         int abs_data = (current->data < 0) ? -current->data : current->data;
//         if (seen[abs_data]) {
//             struct ListNode *to_delete = current;
//             if (prev) {
//                 prev->next = current->next;
//             } else {
//                 *head = current->next;
//             }
//             current = current->next;
//             to_delete->next = NULL;
//             if (deleted_tail == NULL) {
//                 deleted_head = deleted_tail = to_delete;
//             } else {
//                 deleted_tail->next = to_delete;
//                 deleted_tail = to_delete;
//             }
//         } else {
//             seen[abs_data] = 1;
//             prev = current;
//             current = current->next;
//         }
//     }
//     return deleted_head;
// }

// typedef struct ListNode {
//     int num;
//     struct ListNode *next;
// }Node;
// Node* list_reverse(Node* head);
// void display(Node *head);
// int main(void)
// {
//     Node  *head,*p;
//     head = createlist();
//     head = list_reverse(head);
//     display(head);
//     return 0;
// }
// Node* list_reverse(Node* head){
//     Node*pre,*cur,*next;
//     cur=head;
//     pre=NULL,next=NULL;
//     while(cur!=NULL){
//         next=cur->next;
//         cur->next=pre;
//         pre=cur;
//         cur=next;
//     }
//     return pre;
// }

//  pta4

// typedef struct con con;
// struct con{
//     int xh;
//     char name[20];
//     char tel[20];
//     struct con *next;
// };
// con* creatList(){
//     con *list,*tail=NULL,*head=NULL;
//     int n;
//     scanf("%d",&n);
//     while(n>0){
//     list=(con *)malloc(sizeof(con));
//     scanf("%d %s %s",&list->xh,list->name,list->tel);
//     list->next=NULL;
//     if (head == NULL) {
//         head = list;
//     } else {
//         tail->next = list;
//     }
//     tail = list;
//     n--;
//     }
//     return head;
// }
// int main(){
//     con *head,*p;
//     head=creatList();
//     for(p=head;p!=NULL;p=p->next )
//         printf("%d %s %s\n",p->xh ,p->name ,p->tel );
//     return 0;
// }

// pta 10
// struct Node {
//     int data;
//     struct Node* next;
// };

// /* 建立单链表并返回单链表的头指针 */
// struct Node* buildLinkedList(int* arr, int n){
//     struct Node*news=NULL,*head=NULL,*tail=NULL;
//     for(int i=0;i<n;i++){
//         news=(struct Node*)malloc(sizeof(struct Node));
//         news->data=arr[i];
//         news->next=NULL;
//         if(head==NULL) head=news;
//         else{
//             tail->next=news;
//         }
//         tail=news;
//     }
//     return head;
// }
// /* 求单链表值最大的结点 */
// struct Node* getMax(struct Node* head){
//     struct Node*max=head,*find=NULL;
//     find=head;
//     while(find!=NULL){
//         if(max->data<find->data){
//             max=find;
//         }
//         find=find->next;
//     }
//     return max;
// }

// int main(int argc, char const *argv[])
// {
//     int *a, n, i;
//     scanf("%d", &n);
//     a = (int*)malloc(n * sizeof(int));
//     for (i = 0; i < n; ++i) {
//         scanf("%d", &a[i]);
//     }
//     struct Node* head = NULL;
//     head = buildLinkedList(a, n);
//     struct Node* pMax = getMax(head);
//     if (pMax)
//         printf("%d\n", pMax->data);
//     else
//         printf("-1\n");
//     free(a);
//     return 0;
// }

// struct List
// {
//     int val;
//     struct List*next;
// };
// struct List*cl(struct List*head);
// //struct List*creatlist(struct List *head);
// void prinlist(struct List *hd);
// int main(){
//     struct List*head;
//     head=cl(head);
//     //head=creatlist(head);
//     prinlist(head);
//     return 0;
// }
// struct List*creatlist(struct List*head){  //头插法，将数据从头开始插入链表
//     struct List*tail;
//     int n,x;
//     head=(struct List*)malloc(sizeof(struct List));
//     scanf("%d",&n);
//     while(n>0){
//         tail=(struct List *)malloc(sizeof(struct List));
//         scanf("%d",&x);
//         tail->val=x;
//         tail->next=head->next;
//         head->next=tail;
//         n--;
//     }
//     return head->next;
// }
// struct List *cl(struct List *head){   //尾插法，数据顺序不变
//     head=(struct List*)malloc(sizeof(struct List));
//     struct List*cur=head,*tail;
//     int n,x;
//     scanf("%d",&n);
//     while(n>0){
//         tail=(struct List*)malloc(sizeof(struct List));
//         scanf("%d",&x);
//         tail->val=x;
//         cur->next=tail;
//         cur=tail;
//         n--;
//     }
//     return head->next;
// }
// void prinlist(struct List *hd){
//     struct List*pre=hd;
//     while(pre){
//         printf("%d ",pre->val);
//         pre=pre->next;
//     }
// }

// struct List
// {
// 	int val;
// 	struct List *next;
// };
// struct List *creatlist(struct List *head);
// void printlist(struct List *head);
// struct List *turnlist(struct List *head);
// void freelist(struct List *head);
// int main()
// {
// 	struct List *head;
// 	head = creatlist(head);
// 	printlist(head);
// 	head = turnlist(head);
// 	printf("\n");
// 	printlist(head);
// 	freelist(head);
// 	return 0;
// }
// struct List *creatlist(struct List *head)
// {
// 	int n = 0, x;
// 	head = (struct List *)malloc(sizeof(struct List));
// 	head->next = NULL;
// 	struct List *r, *cur = head;
// 	scanf("%d", &n);
// 	while (n)
// 	{
// 		r = (struct List *)malloc(sizeof(struct List));
// 		scanf("%d", &x);
// 		r->val = x;
// 		r->next = NULL;
// 		cur->next = r;
// 		cur = r;
// 		n--;
// 	}
// 	return head->next;
// }
// void printlist(struct List *head)
// {
// 	struct List *newl = head;
// 	while (newl)
// 	{
// 		printf("%d ", newl->val);
// 		newl = newl->next;
// 	}
// }
// struct List *turnlist(struct List *head)
// {
// 	struct List *prv = NULL, *cur = head, *xia = NULL;
// 	while (cur)
// 	{
// 		xia=cur->next;
// 		cur->next=prv;
// 		prv=cur;
// 		cur=xia;
// 	}
// 	return prv;
// }
// void freelist(struct List *head)
// {
// 	struct List *current=head;
// 	struct List *ne;
// 	while (current!=NULL)
// 	{
// 		ne=current->next;
// 		free(current);
// 		current=ne;
// 	}
// 	head = NULL;
// }

// int main()
// {
//     FILE *fp;
// 	char ch;
// 	if((fp=fopen("test.txt","r"))==NULL){
// 		printf("cannot open file.\n");
// 		exit(0);
// 	}
// 	while((ch=fgetc(fp))!=EOF){
// 		if(ch>='a'&&ch<='z'){
// 			ch=ch-32;
// 		}
// 		putchar(ch);
// 	}
// 	fclose(fp);
// 	return 0;
//  }

// int main(int argc,char *argv[]){
//     struct winsize info;
//     ioctl(STDIN_FILENO,TIOCGWINSZ,&info);
//     printf("当前终端为%d行%d列\n",info.ws_row,info.ws_col);
//     return 0;
// }

// struct s{
//     int val;
//     struct s *next;
// };
// struct s *suru(struct s *head){
//     struct s *cur;
//     head=(struct s*)malloc(sizeof(struct s));
//     cur=head;
//     int n;
//     scanf("%d",&n);
//     while(n){
//         struct s*list;
//         list=(struct s*)malloc(sizeof(struct s));
//         int x;
//         scanf("%d",&x);
//         list->val=x;
//         cur->next=list;
//         cur=list;
//         n--;
//     }
//     return head->next;
// }
// void print(struct s*p){
//     while(p){
//         printf("%d ",p->val);
//         p=p->next;
//     }
// }
// void f(struct s*pr){
//     struct s*cur;
//     while(pr){
//         cur=pr->next;
//         free(pr);
//         pr=cur;
//     }
// }
// int main(){
//     struct s *head;
//     head=suru(head);
//     print(head);
//     f(head);
//     return 0;
// }

// int main()
// {
//     double weight;
//     double sum=0;
//     scanf("%lf",&weight);
//     if(weight<0){
//         printf("Error!");
//     }
//     if(weight<=10){
//         sum=weight*1.3;
//     }else if(weight>10&&weight<=50){
//         sum=10*1.3+(weight-10)*1.8;
//     }else if(weight>50&&weight<=200){
//         sum=10*1.3+40*1.8+(weight-50)*2.4;
//     }else{
//         sum=10*1.3+40*1.8+150*2.4+(weight-200)*4.5;
//     }
//     printf("%.2f",sum);
//     return 0;
// }

// int main(){
//     double z,sum=1.0;
//     scanf("%lf",&z);
//     z*=0.01;
//     int cnt=0;
//     while(sum<2){
//         sum=sum+sum*z;
//         cnt++;
//     }
//     printf("%d",cnt);
//     return 0;
// }

// int main()
// {
//     int m, n, cnt = 1, temp;
//     scanf("%d %d", &m, &n);
//     int aln[7][7];
//     for (int i = 1; i <= n; i++)
//     {
//         for (int j = 1; j <= n; j++)
//         {
//             scanf("%d", &aln[i][j]);
//         }
//     }
//     for (int i = 1; i < n; i++)
//     {
//         if (m + 1 > n)
//         {
//             temp = aln[1][(m + 1) % n];
//         }
//         else
//         {
//             temp = aln[1][m + 1];
//         }
//         while (cnt < n)
//         {
//             if (m + 1 > n)
//             {
//                 aln[i][(m + 1) % n] = aln[i][cnt];
//             }
//             else
//             {
//                 aln[i][m + 1] = aln[i][cnt];
//             }
//             cnt++;
//             if (cnt == n)
//             {
//                 aln[n][m + 1] = temp;
//             }
//         }
//         cnt=1;
//     }

//     for (int i = 1; i <= n; i++)
//     {
//         for (int j = 1; j <= n; j++)
//         {
//             printf("%d ", aln[i][j]);
//         }
//         printf("\n");
//     }
//     return 0;
// }

// void findmax( int *px, int *py, int *pmax );
// int main()
// {    
//     int max, x, y; 

//     scanf("%d %d", &x, &y);
//     findmax( &x, &y, &max );
//     printf("%d\n", max);

//     return 0;
//     } 
// void findmax( int *px, int *py, int *pmax ){
//     *pmax=(*px>*py?*px:*py);
// }

// struct ListNode {
//     int data;
//     struct ListNode *next;
// };

// struct ListNode *createlist();

// int main()
// {
//     struct ListNode *p, *head = NULL;
//     head = createlist();
//     for ( p = head; p != NULL; p = p->next )
//         printf("%d ", p->data);
//     printf("\n");
//     return 0;
// }
// struct ListNode *createlist(){
// struct ListNode *prv=NULL,*head;
//     int x;
//     head=(struct ListNode*)malloc(sizeof(struct ListNode));
//     head->next=NULL;
//     do{
//         prv=(struct ListNode*)malloc(sizeof(struct ListNode));
//         scanf("%d",&x);
//         if(x==-1) break;
//         prv->data=x;
//         prv->next=head->next;
//         head->next=prv;
//     }while(x!=-1);
//     head=head->next;
//     return head;
// }


// int main(){
//     int p=0,a,b,sum=0;
//     scanf("%d %d",&a,&b);
//     for(int i=a;i<=b;i++){
//         for(int j=1;j<=i/2;j++){
//             if(i%j==0&&i!=1){
//                 sum+=j;
//             }
//         }
//         if(sum==i){
//             p=1;
//         printf("%d\n",i);
//         }
//         sum=0;
//     }
//     if(p==0) printf("None");
//     return 0;
// }

// int main() {
//     int m, n;
//     scanf("%d %d", &m, &n);
//     int matrix[n][n];
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             scanf("%d", &matrix[i][j]);
//         }
//     }
//     for (int i = 0; i < n; i++) {
//         int temp[n];
//         for (int j = 0; j < n; j++) {
//             temp[(j + m) % n] = matrix[i][j];
//         }
//         for (int j = 0; j < n; j++) {
//             printf("%d ", temp[j]);
//         }
//         printf("\n");  
//     }
//     return 0;
// }

// void factorize(long int N) {
//     int first = 1;  
//     if (N % 2 == 0) {
//         int count = 0;
//         while (N % 2 == 0) {
//             count++;
//             N /= 2;
//         }
//         if (!first) {
//             printf("*");
//         }
//         printf("2");
//         if (count > 1) {
//             printf("^%d", count);
//         }
//         first = 0;
//     }
//     for (long int i = 3; i * i <= N; i += 2) {
//         if (N % i == 0) {
//             int count = 0;
//             while (N % i == 0) {
//                 count++;
//                 N /= i;
//             }
//             if (!first) {
//                 printf("*");
//             }
//             printf("%ld", i);
//             if (count > 1) {
//                 printf("^%d", count);
//             }
//             first = 0;
//         }
//     }
//     if (N > 1) {
//         if (!first) {
//             printf("*");
//         }
//         printf("%ld", N);
//     }
//     printf("\n");
// }
// int main() {
//     long int N;
//     scanf("%ld", &N);  
//     printf("%ld=",N);
//     factorize(N); 
//     return 0;
// }

// struct list{
//     int val;
//     struct list*next;
// };
// // struct list*tou(struct list*head){
// //     struct list *prv;
// //     head=(struct list*)malloc(sizeof(struct list));
// //     head->next=NULL;
// //     int n;
// //     scanf("%d",&n);
// //     while(n){
// //         prv=(struct list*)malloc(sizeof(struct list));
// //         scanf("%d",&prv->val);
// //         prv->next=head->next;
// //         head->next=prv;
// //         n--;
// //     }
// //     head=head->next;
// //     return head;
// // }

// struct list *tail(struct list*head){
//     struct list*pre,*cur=head;
//     int n;
//     scanf("%d",&n);
//     while(n){
//         pre=(struct list*)malloc(sizeof(struct list));
//         scanf("%d",&pre->val);
//         cur->next=pre;
//         cur=pre;
//         n--;
//     }
//     return head->next;
// }
// void print(struct list *p)
// {
//     while(p){
//         printf("%d ",p->val);
//         p=p->next;
//     }
// }
// void f(struct list *fr){
//     struct list *cur;
//     while(fr){
//         cur=fr->next;
//         free(fr);
//         fr=cur;
//     }
// }
// struct list*turn(struct list*head){
//     struct list*cur,*prv,*Next;
//     cur=head;
//     while(cur){
//         Next=cur->next;
//         cur->next=prv;
//         prv=cur;
//         cur=Next;
//     }
//     return prv;
// }
// int main(){
//     struct list *head;
//     head=tail(head);
//     //head=tou(head);
//     print(head);
//     printf("\n");
//     head=turn(head);
//     print(head);
//     f(head);
//     return 0;
// }

// int multiply(int A, int B) {
//     if(B==1) return A;
//     return A+multiply(A,B-1);
// }
// int main(){
//     int a=3,b=4;
//     printf("%d",multiply(a,b));
//     return 0;
// }

// #define r 100
// struct Stack{
//     int *top;
//     int *base;
//     int capacity;
// };
// int creatstack(struct Stack *s);
// int stackempty(struct Stack *s);
// int stackfull(struct Stack *s);
// int getstack(struct Stack *s);
// void instack(struct Stack *s,int data);
// int popstack(struct Stack *s);
// int main(){
//     int num,a;
//     struct Stack *stack;
//     creatstack(stack);
//     if(!stackempty(stack)) 
//     printf("stack is empty");
//     if(!stackfull(stack))
//     printf("stack is full");
//     printf("enter a num push stack:");
//     scanf("%d",&num);
//     instack(stack,num);
//     a=getstack(stack);
//     printf("%d",a);
//     return 0;
// }
// int creatstack(struct Stack *s){
//     s->base=(int *)malloc(sizeof(int)*r);
//     if(!s->base) return 0;
//     s->base=s->top;
//     s->capacity=r;
// }
// int stackempty(struct Stack *s){
//     return s->base==s->top;
// }
// int stackfull(struct Stack *s){
//     return s->top-s->base==s->capacity;
// }
// int getstack(struct Stack *s){
//     int val;
//     if(s->top==s->base) return 0;
//     val=s->top--;
//     return val;
// }
// void instack(struct Stack *s,int data){
//     if(s->top-s->base>=s->capacity){
//         s->top=(int*)realloc(s->top,sizeof(int)*(s->capacity+1));
//         s->top=s->base+s->capacity;
//         s->capacity++;
//     }
//     s->top=data;
//     s->top++;
// }
// int popstack(struct Stack *s){
//     if(s->base==s->top) {
//     printf("stack is empty");
//     return;
//     }
//     int num=s->top;
//     s->top--;
//     return num;
// }

//栈

// struct Stack{
//     int capacity;
//     int top;
//     int *move;
// };
// void stackcreat(struct Stack *s);
// void StackPush(struct Stack *s,int data);
// int stackout(struct Stack *s);
// void stackdestroy(struct Stack *s);
// int stackempty(struct Stack *s);
// int main(){
//     struct Stack stack;
//     stackcreat(&stack);
//     StackPush(&stack, 1);
// 	StackPush(&stack, 2);
//     StackPush(&stack, 3);
//     StackPush(&stack, 4);
//     StackPush(&stack, 5);
//     while(!stackempty(&stack)){
//         printf("%d ",stackout(&stack));
//     }
//     stackdestroy(&stack);
//     return 0;   
// }
// int stackempty(struct Stack *s){
//     return s->top==0;
// }
// void stackcreat(struct Stack *s){
//     s->top=0;
//     s->capacity=4;
//     s->move=(int *)malloc(sizeof(int)*4);
//     //s->move=NULL;
// }
// void StackPush(struct Stack *s,int data){
//     if(s->top>=s->capacity){
//         int *tmp;
//         tmp=(int *)realloc(s->move,sizeof(int)*(s->capacity*2));
//         if(tmp==NULL){
//             perror("realloc fail");
//             return;
//         }
//         s->move=tmp;
//         s->capacity=s->capacity*2;
//     }
//     s->move[s->top]=data;
//     s->top++;
// }
// int stackout(struct Stack *s){
//     return s->move[--s->top];
// }
// void stackdestroy(struct Stack *s){
//     if(s->move==NULL) return;
//     free(s->move);
//     s->move=NULL;
//     s->capacity=0;
//     s->top=0;
// }

// void turn(char *aln[]){
//     int end=2;
//     for(int i=0;i<3/2;i++){
//         char *temp=aln[i];
//         aln[i]=aln[end];
//         aln[end]=temp;
//         end--;
//     }
// }
// int main(){
//     char *aln[]={"asg","heqh","qtet"};
//     for(int i=0;i<3;i++){
//         printf("%s ",aln[i]);
//     }
//     turn(aln);
//     printf("\n");
//     for(int i=0;i<3;i++){
//         printf("%s ",aln[i]);
//     }
//     return 0;
// }

//队列

// #define qmax 10
// typedef struct{
//     int front;
//     int rear;
//     int *element;
// }Queqe;
// void qinit(Queqe *q);
// void qpush(int val,Queqe*q);
// int qout(Queqe*q,int *value);
// int qempty(Queqe *s);
// void qtravel(Queqe *s);
// int main(){
//     Queqe q;
//     qinit(&q);
//     qpush(1,&q);
//     qpush(2,&q);
//     qpush(3,&q);
//     qpush(4,&q);
//     qtravel(&q);
//     printf("\n");
//     int value;
//     qout(&q,&value);
//     printf("%d\n",value);
//     qtravel(&q);
//     free(q.element);
//     return 0;
// }
// void qinit(Queqe *q){
//     q->element=(int*)malloc(sizeof(Queqe)*qmax);
//     q->front=0;
//     q->rear=0;
// }
// void qpush(int val,Queqe*q){
//     if(qempty(q)){
//         printf("q is full");
//         return;
//     }
//     q->element[q->rear]=val;
//     q->rear=(q->rear+1)%qmax;
// }
// int qout(Queqe*q,int *value){
//     if(q->front==q->rear){
//         printf("q is empty");
//         return 0;
//     }
//     *value=q->element[q->front];
//     q->front=(q->front+1)%qmax;
//     return 1;
// }
// void qtravel(Queqe *s){
//     if(s->rear==s->front){
//         printf("q is empty");
//         return;
//     }
//     for(int i=s->front;i!=s->rear;i=(i+1)%qmax){
//         printf("%d ",s->element[i]);
//     }
// }
// int qempty(Queqe *s){
//     return (s->rear+1)%qmax-s->front==0;
// }

//环形链表

// typedef struct list{
//     int val;
//     struct list *next;
// }node;
// void creatlist(node **head,int num);
// node*cyclelist(node*head,int aln[]);
// void travellist(node *head);
// int main(){
//     node *head;
//     creatlist(&head,1);
//     int aln[]={2,3,4,5};
//     cyclelist(head,aln);
//     travellist(head);
// }
// void creatlist(node**head,int num){
//     *head=(node*)malloc(sizeof(node));
//     (*head)->val=num;
//     (*head)->next=NULL;
// }
// node*cyclelist(node*head,int aln[]){
//     node* cur=head;
//     for (int i =0;i<=2;i++) {
//         node* newNode=(node*)malloc(sizeof(node));
//         newNode->val=aln[i];
//         newNode->next=NULL;
//         cur->next=newNode;
//         cur=newNode;
//     }
//     cur->next=head;
//     return head;
// }
// void travellist(node *head){
//     node *cur=head;
//     node *pre;
//     for(int i=0;i<10;i++){
//         printf("%d ",cur->val);
//         cur=cur->next;
//     }
// }

// struct Listnode{
//     int val;
//     struct Listnode *next;
// };
// struct Listnode *creat(struct Listnode *head,int aln[],int len);
// void travellist(struct Listnode *head);
// void listfree(struct Listnode *head);
// int main(){
//     struct Listnode *head;
//     head=(struct Listnode *)malloc(sizeof(struct Listnode));
//     int aln[]={1,2,3,4};
//     int len=sizeof(aln)/sizeof(aln[0]);
//     head=creat(head,aln,len);
//     travellist(head);
//     int i=0;
//     struct Listnode *curr=head;
//     for(;curr!=NULL;){
//         curr=curr->next;
//         i++;
//     }
//     printf("  %d",i);
//     return 0;
// }
// struct Listnode *creat(struct Listnode *head,int aln[],int len){
//     struct Listnode dummp={0,head};
//     struct Listnode *cur=head;
//     printf("%d\n",len);
//     for(int i=0;i<len;i++){
//         struct Listnode *newnode;
//         newnode=(struct Listnode*)malloc(sizeof(struct Listnode));
//         newnode->val=aln[i];
//         newnode->next=NULL;
//         cur->next=newnode;
//         cur=newnode;
//     }
//     return dummp.next->next;
// }
// void travellist(struct Listnode *head){
//     while(head){
//         printf("%d ",head->val);
//         head=head->next;
//     }
// }
// void listfree(struct Listnode *head){
//     struct Listnode *f=head;
//     if(f!=NULL){
//         struct Listnode *Next=f->next; 
//         free(f);
//         f=Next;
//     }
// }

// 栈实现队列

// #define MAX 100
// typedef struct Stack
// {
//     int top;
//     int num[MAX];
// }S;
// void stackinit(S *stack){
//     stack->top=-1;
// }
// int stackempty(S *stack){
//     return stack->top==-1;
// }
// void stackpush(S *stack,int val){
//     if(stack->top<MAX-1){
//         stack->num[++(stack->top)]=val;
//     }else{
//         printf("stack is full\n");
//     }
// }
// int stackpop(S *stack){
//     if(stackempty(stack)){
//         printf("stack is empty\n");
//         return -1;
//     }else{
//         return stack->num[(stack->top)--];
//     }
// }
// int stacktoppop(S *stack){
//     if(stackempty(stack)){
//         printf("stack is empty\n");
//         return -1;
//     }else{
//         return stack->num[stack->top];
//     }
// }

// typedef struct queue{
//     S stack1; // 入队
//     S stack2; // 出队
// }Q;

// void queueinit(Q *queue){
//     stackinit(&queue->stack1);
//     stackinit(&queue->stack2);
// }
// void queuepush(Q *queue,int val){
//     stackpush(&queue->stack1,val);
// }
// int queuepop(Q *queue){
//     if(stackempty(&queue->stack2)){
//         while(!stackempty(&queue->stack1)){
//             stackpush(&queue->stack2,stackpop(&queue->stack1));
//         }
//     }
//     if(stackempty(&queue->stack2)){
//         printf("queue is empty\n");
//         return -1;
//     }
//     return stackpop(&queue->stack2);
// }
// int queueempty(Q *queue){
//     return stackempty(&queue->stack1)&&stackempty(&queue->stack2);
// }
// int main(){
//     Q queue;
//     queueinit(&queue);
//     queuepush(&queue,1);
//     queuepush(&queue,2);
//     queuepush(&queue,3);
//     printf("%d ",queuepop(&queue));
//     printf("%d ",queuepop(&queue));
//     printf("%d ",queuepop(&queue));
//     if(queueempty(&queue)){
//         printf("empty\n");
//     }
//     return 0;
// }

// long long j(int a){
//     if(a==0) return 0;
//     if(a==1) return 1;
//     return a*j(a-1);
// }
// int main(){
//     printf("%d",j(5));
//     return 0;
// }



// int main(){
//     int aln[5]={};
//     for(int i=0;i<5;i++){
//         printf("%d ",aln[i]);
//     }
//     return 0;
// }

// int main(){
//     int aln[][3]={{1},{2,3,4}};
//     int aln1[]={1,2,3,4};
//     int row=2,line=3;
//     for(int i=0;i<row;i++){
//         for(int j=0;j<line;j++){
//             if(aln[i][j+1]=='\0'||j==line-1){
//             printf("%d ",aln[i][j]);
//             break;
//             }
//         }
//     }
//     return 0;
// }

// uthash的使用

// struct hash{
//     int id;
//     char name[10];
//     UT_hash_handle hh;
// };
// struct hash *user=NULL; //每一次使用时都必须将其初始化为零，很重要
//    /*  HASH_ADD_INT表示添加的键值为int类型
//    HASH_ADD_STR表示添加的键值为字符串类型
//     HASH_ADD_PTR表示添加的键值为指针类型
//     HASH_ADD表示添加的键值可以是任意类型*/
// void add_user(int user_id,char *name){
//     struct hash *check;
//     HASH_FIND_INT(user,&user_id,check); //检查哈希表中不存在这个id，防止重复添加
//     if(!check){
//         check=(struct hash*)malloc(sizeof(*check));
//         check->id=user_id;
//         HASH_ADD_INT(user,id,check);
//     }
//     strcpy(check->name,name);
// }
// // HASH_ADD_INT函数中，第一个参数users是哈希表，第二个参数id是键字段的名称。最后一个参数s是指向要添加的结构的指针
// struct hash *find(int user_id){
//     struct hash *s;
//     HASH_FIND_INT(user,&user_id,s);
//     return s;
// }
// void deleteh(struct hash *u){
//     HASH_DEL(user,u);
//     free(u);
// }
// void deleteall(){ //将哈希表中所有数据删除但不会释放相应的内存
//     struct hash *tmp,*curr;
//     HASH_ITER(hh,user,curr,tmp){
//     HASH_DEL(user,curr);
//     free(curr); //如果想释放内存就加上这一行
//     }
// }
// //  如果只想删除所有项目，但不释放它们或进行每个元素的清理，则用下面这一行会更简洁
// // HASH_CLEAR(hh,users); 此后users将被设置为NULL
// void printhash(){
//     struct hash *s;
//     for(s=user;s!=NULL;s=(struct hash*)(s->hh.next)){
//         printf("user id is %d name:%s",s->id,s->name);
//     }
// }
// // 哈希表的排序(与qsort相同的使用)
// int name_sort(struct hash *a,struct hash *b){
//     return strcmp(a->name,b->name);
// }
// int id_sort(struct hash *a,struct hash *b){
//     return (a->id-b->id);
// }
// void namesort(){
//     HASH_SORT(user,name_sort);
// }
// void idsort(){
//     HASH_SORT(user,id_sort);
// }
// int main(){
//     char in[10];
//     int id=1, running=1;
//     struct hash *s;
//     unsigned num_users;
//     while (running) {
//         printf(" 1. add user\n");
//         printf(" 2. add/rename user by id\n");
//         printf(" 3. find user\n");
//         printf(" 4. delete user\n");
//         printf(" 5. delete all users\n");
//         printf(" 6. sort items by name\n");
//         printf(" 7. sort items by id\n");
//         printf(" 8. print users\n");
//         printf(" 9. count users\n");
//         printf("10. quit\n");
//         gets(in);
//         switch(atoi(in)) {
//             case 1:
//                 printf("name?\n");
//                 add_user(id++, gets(in));
//                 break;
//             case 2:
//                 printf("id?\n");
//                 gets(in); id = atoi(in);
//                 printf("name?\n");
//                 add_user(id, gets(in));
//                 break;
//             case 3:
//                 printf("id?\n");
//                 s = find(atoi(gets(in)));
//                 printf("user: %s\n", s ? s->name : "unknown");
//                 break;
//             case 4:
//                 printf("id?\n");
//                 s = find(atoi(gets(in)));
//                 if (s) deleteh(s);
//                 else printf("id unknown\n");
//                 break;
//             case 5:
//                 deleteall();
//                 break;
//             case 6:
//                 namesort();
//                 break;
//             case 7:
//                 idsort();
//                 break;
//             case 8:
//                 printhash();
//                 break;
//             case 9:
//                 num_users=HASH_COUNT(user);
//                 printf("there are %u users\n", num_users);
//                 break;
//             case 10:
//                 running=0;
//                 break;
//         }
//     }
//     deleteall();  /* free any structures */
//     return 0;
// }


//链式二叉树

// typedef struct ecs{
//     char data;
//     struct ecs *lchild;
//     struct ecs *rchild;
// }tree,node;
// char str[24] = {19, 'A','B','D','G','#','#','H','#','#','#','C','E','#','I','#','#','F','#','#'}; //用作测试
// int index=1;
// // 前序遍历 
// // 规则:二叉树为空，则返回，否则先访问根结点，然后前序遍历左子树，再前序遍历右子树

// void fronttravel(tree *T){
//     if(!T) return;
//     printf("%c ",T->data);
//     fronttravel(T->lchild);
//     fronttravel(T->rchild);
// }

// // 中序遍历
// // 规则:若树为空，则空操作返回，否则从根结点开始（注意并不是先访问根结点），
// // 中序遍历根结点的左子树，然后是访问根结点，最后中序遍历右子树

// void middletravel(tree *T){
//     if(!T) return;
//     middletravel(T->lchild);
//     printf("%c ",T->data);
//     middletravel(T->rchild);
// }

// // 后序遍历
// // 规则:若树为空，则空操作返回，否则从左到右先叶子后结点的方式遍历访问左右子树，最后是访问根结点

// void reartravel(tree *T){
//     if(!T) return;
//     reartravel(T->lchild);
//     reartravel(T->rchild);
//     printf("%c ",T->data);
// }

// void creatrtree(tree **T){
//     char ch;
//     ch=str[index++];
//     if(ch!='#'){
//         *T=(tree *)malloc(sizeof(tree));
//         if(!*T) return;
//         (*T)->data=ch;
//         creatrtree(&(*T)->lchild);
//         creatrtree(&(*T)->rchild);
//     }else{
//         (*T)=NULL;
//     }
// }


// struct list{
//     int val;
//     struct list *next;
// };
// void listtc(int aln[],struct list **head,int len);
// void listtravel(struct list *head);
// void listfree(struct list **head);
// struct list *listturn(struct list *head);
// int main(){
//     struct list *head;
//     head=(struct list *)malloc(sizeof(struct list));
//     int a[]={1,2,3,4,5};
//     listtc(a,&head,5);
//     listtravel(head);
//     head=listturn(head);
//     printf("\n");
//     listtravel(head);
//     listfree(&head);
//     return 0;
// }
// struct list *listturn(struct list *head){
//     struct list *cur=head;
//     struct list *pre=NULL,*N=NULL;
//     while(cur){
//         N=cur->next;
//         cur->next=pre;
//         pre=cur;
//         cur=N;
//     }
//     return pre;
// }
// void listtc(int aln[],struct list **head,int len){
//     struct list *cur=*head;
//     for(int i=0;i<len;i++){
//         struct list *pre;
//         pre=(struct list *)malloc(sizeof(struct list));
//         pre->val=aln[i];
//         cur->next=pre;
//         cur=pre;
//     }
// }
// void listtravel(struct list *head){
//     while(head){
//         printf("%d ",head->val);
//         head=head->next;
//     }
// }
// void listfree(struct list **head){
//     struct list *cur=*head;
//     while(cur){
//         struct list *p=cur->next;
//         free(cur);
//         cur=p;
//     }
// }

// bool backspaceCompare(char* s, char* t) {
//     int lens=strlen(s),lent=strlen(t);
//     char *stks,*stkt;
//     stks=(char *)malloc(sizeof(char)*(lens+1));
//     stkt=(char *)malloc(sizeof(char)*(lent+1));
//     stks[0]='1',stkt[0]='1';
//     int tops=0,topt=0;
//     for(int i=lens-1;i>=0;i--){
//         if(stks[tops]!='#'){
//             tops++;
//             stks[tops]=s[i];
//         }
//     }
//     stks[tops]='\0';
//     for(int i=lent-1;i>=0;i--){
//         if(stkt[topt]!='#'){
//             topt++;
//             stkt[topt]=t[i];
//         }
//     }
//     stkt[topt]='\0';
//     printf("%s\n%s",stks,stkt);
//     stkt[topt]='\0';
//     int x=strcmp(stks,stkt);
//     if(x==0)
//     return true;
//     else return false;
// }
// int main(){
//     char *s="xyw\0rrmp";
//     char *t="xyw\0rrmp";
//     backspaceCompare(s,t);
//     printf("\n%d",strcmp(s,t));
// }

// int main(){
//     char str[20]="123";
//     int val=atoi(str);
//     printf("%d ",val);
//     return 0;
// }


// int main(){
//     int x,y;
//     scanf("%d %d",&x,&y);
//     char s[x+1];
//     int sum=1,zhi=1;
//     int i,j;
//     for( i=0;i<y;i++)
// 	{
//         scanf("%s",s);
//         for( j=x-1;j>=0;j--)
// 		{
//             if (s[j]=='n') 
// 			sum+=zhi;
//             zhi*=2;
//         }
//         printf("%d\n",sum);
//         zhi=1;sum=1;
//     }
//     return 0;
// }


// void canshujiexi(char *buf,char **out){
//     char *ch=strtok(buf," ");
//     int i=0;
//     while(ch!=NULL&&i<63){
//         printf("ch=%s\n",ch);
//         ch=strtok(NULL," ");
//     }
// }
// int main(int argc,char *argv[]){
//     //char aln[]="cat < 1.txt";
//     char *out[64];
//     char aln[]="ls | grep .c > test.txt";
//     char *token = strtok(aln, "|");  // 以空格 " " 作为分隔符
//     while (token != NULL) {
//         printf("%s\n", token);  // 逐个打印子字符串
//         canshujiexi(token,out);
//         token = strtok(NULL, "|");  // 获取下一个子字符串
//     }
//     printf("剩下的：%s",aln);
//     return 0;
// }

// #define zorq(a) a>0 ? O_APPEND : O_TRUNC
// #define MAX(a,b) a>b ? a:b
// int main(){
//     int a=1,b=2;
//     char *s;
//     printf("%c",zorq(a));
//     return 0;
// }


// void can(char *buf,int *num);
// int main() {
//     int cnt=0;
//     char zjml[1024];
//     char str[] = "ls -a | wc -l | ls -l";
//     char *token = strtok(str, "|");  
//     while (token != NULL) {
//         printf("%s\n", token);
//         cnt++;
//         strncpy(zjml,token,strlen(token));
//         printf("tnow = %s\n",token);
//         can(zjml,&cnt);
//         token = strtok(NULL, "|");  
        
//     }
//     return 0;
// }
// void can(char *buf,int *num){
//     printf("buf=%s\n",buf);
//     char *ch=strtok(buf," ");
//     printf("第%d个\n",*num);
//     while(ch!=NULL){
//         printf("ch= %s\n",ch);
//         ch=strtok(NULL," ");
//     }
// }


// void can(char *buf, int *num);

// int main() {
//     int cnt = 0;
//     char str[] = "ls -a | wc -l | ls -l";  
//     char *token;
//     char *saveptr;
//     token = strtok_r(str, "|", &saveptr);
//     while (token != NULL) {
//         cnt++;
//         char zjml[1024];
//         strncpy(zjml, token, sizeof(zjml) - 1);
//         zjml[sizeof(zjml) - 1] = '\0';  
//         can(zjml, &cnt);
//         token = strtok_r(NULL, "|", &saveptr); 
//     }
//     return 0;
// }
// void can(char *buf, int *num) {
//     printf("buf=%s\n", buf);
//     char *ch;
//     char *saveptr;
//     printf("第%d个\n", *num);
//     ch = strtok_r(buf, " ", &saveptr);
//     while (ch != NULL) {
//         printf("ch= %s\n", ch);
//         ch = strtok_r(NULL, " ", &saveptr);
//     }
// }

// int main() {
//     char s[1024] = "awk 'print{ as}'   feqqe ls -l";
//     char *out[100];
//     int cnt = 0;
//     char *p = s;
//     int len=strlen(p),right=0;
//     for(int left=0;left<len,right<len;left++){
//         if(p[right+1]=='\''){
//             left++,right+=2;
//             while(p[right]!='\''){
//                 right++;
//             }
//             p[right++]='\0';
//             out[cnt++]=p+left;
//         }else{
//             while(p[left]==' '||p[left]=='\0') {
//                 left++;
//             }
//             if(p[right]==' '&&right<len-1){
//             right++;
//             }
//             while(p[right]!=' '){
//                 right++;
//             }
//             p[right]='\0';
//             out[cnt++]=p+left;
//         }
//         left=right;
//     }
//     for (int i = 0; i < cnt; i++) {
//         printf("Arg %d: %s\n", i, out[i]);
//     }
//     return 0;
// }

// int main() {
//     char s[1024] = "ls -a | wc -l";
//     char *out[100]; 
//     int cnt=0;
//     int left=0,right=0,len=strlen(s);
//     while (left<len) {
//         while (left<len&&s[left]==' ') left++;
//         if (left>=len) break;
//         if (s[left]=='\'') {
//             left++; 
//             right=left;
//             while (right<len&&s[right]!='\'') right++; 
//             if (right>=len) {
//                 return 1;
//             }
//             s[right++]= '\0'; 
//         }
//         else {
//             right=left;
//             while (right<len&&s[right]!=' ') right++;  
//             if (right<len) s[right++]= '\0';  
//         }
//         out[cnt++]=s+left;
//         left=right;  
//     }
//     for (int i = 0; i < cnt; i++) {
//         printf("Arg %d: %s\n", i, out[i]);
//     }
//     return 0;
// }

// #define MAXLEN 101  

// void cxzl(char *s, char *op) {
//     char test[MAXLEN]; 
//     int right = strlen(s);
//     strcpy(test, s); 
//     int len = right; 
//     char *token = strtok(op, " "); 
//     while (token) {
//         if (strcmp(token, "LEFT") == 0) {
//             if (right > 0) right--; 
//         } else if (strcmp(token, "RIGHT") == 0) {
//             if (right < len) right++; 
//         } else if (strcmp(token, "CTRL") == 0) {
//             token = strtok(NULL, " "); 
//             if (!token) break;
//             if (strcmp(token, "S") == 0) {
//                 test[len] = '\0';  
//                 printf("%s\n", test);
//             } else if (token[0] == 'D') {
//                 int x = atoi(token + 1); 
//                 if (right > 0) { 
//                     char ch = test[right - 1];
//                     memmove(test + right + x, test + right, len - right + 1);
//                     for (int i = 0; i < x; i++) {
//                         test[right + i] = ch;
//                     }
//                     right += x; 
//                     len += x;    
//                 }
//             }
//         }
//         token = strtok(NULL, " "); 
//     }
//     test[len] = '\0';  
//     printf("%s\n", test); 
// }
// int main() {
//     char s[MAXLEN];  
//     char op[100001];  
//     fgets(s, sizeof(s), stdin); 
//     fgets(op, sizeof(op), stdin); 
//     s[strcspn(s, "\n")] = 0; 
//     op[strcspn(op, "\n")] = 0;
//     cxzl(s, op); 
//     return 0;
// }

// int cmp(const void *a,const void *b){
//     return *(int *)a-*(int *)b;
// }
// int main(){
//     int num;
//     int aln[10];
//     printf("原数组：");
//     for(int i=0;i<10;i++){
//         aln[i]=random()%101;
//         printf("%d ",aln[i]);
//     }
//     printf("\n");
//     qsort(aln,10,sizeof(int),cmp);
//     printf("排序后：");
//     for(int i=0;i<10;i++){
//         printf("%d ",aln[i]);
//     }
//     return 0;
// }

// int main(){
//     int *ans;
//     ans=(int *)malloc(sizeof(int)*5);
//     for(int i=0;i<5;i++){
//         ans[i]=i;
//     }
//     int aln[5]={1,2,3,4,5};
//     int *temp;
//     temp=(int *)realloc(ans,sizeof(int)*10);
//     if(temp==NULL){
//         free(ans);
//         printf("fail");
//     }
//     ans=temp;
//     memmove(ans+5,aln,sizeof(int)*5);
//     for(int i=0;i<10;i++){
//         printf("%d ",ans[i]);
//     }
//     free(ans);
//     return 0;
// }

// void fen(int *arr,int start,int end);
// void zhi(int *arr,int start,int mid,int end);
// int main(){
//     int arr[10]={5, 1, 8, 4, 7, 2, 3, 9, 0, 6};
//     int len=sizeof(arr)/sizeof(arr[0]);
//     fen(arr,0,len-1);
//     for(int i=0;i<len;i++){
//         printf("%d ",arr[i]);
//     }
//     return 0;
// }
// void fen(int *arr,int start,int end){
//     int mid=start+(end-start)/2;
//     if(start>=end){
//         return;
//     }
//     fen(arr,start,mid);
//     fen(arr,mid+1,end);
//     zhi(arr,start,mid,end);
// }
// void zhi(int *arr,int start,int mid,int end){
//     int *aln=(int *)malloc(sizeof(int)*(end-start+1));
//     int i=start;
//     int j=mid+1,k=0;
//     while(i<=mid&&j<=end){
//         if(arr[i]<=arr[j]){
//             aln[k++]=arr[i++];
//         }else{
//             aln[k++]=arr[j++];
//         }
//     }
//     while(i<=mid){
//         aln[k++]=arr[i++];
//     }
//     while(j<=end){
//         aln[k++]=arr[j++];
//     }
//     for(int i=0;i<k;i++){
//         arr[start+i]=aln[i];
//     }
//     free(aln);
// }

int main(){
    char buf1[100];
    char buf2[100]="hello";
    printf("%d\n",strlen(buf2));
    printf("%d",sizeof(buf2));
    return 0;
}