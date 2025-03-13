#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int cmp(const void *a,const void *b){
    return *(int *)a-*(int *)b;
}
#define all 100000
#define qiege 100
#define N 1000
static pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER; //互斥量的初始化
static pthread_cond_t cond=PTHREAD_COND_INITIALIZER; //条件变量的初始化
static void *T1(void *arg);
static void *T2(void *arg);
void shuchu();
int ans[all],mark=0,filsh_aln=0;
int main(){
    srand(time(NULL));
    pthread_t t1[qiege],t2;
    int *aln[N],bz=0;
    for(int i=0;i<qiege;i++){
        aln[i]=(int *)malloc(sizeof(int)*N);
    }
    for(int i=0;i<all;i++){
        aln[mark][i%N]=random()%INT_MAX;
        if((i+1)%N==0){
            pthread_create(&t1[mark],NULL,T1,aln[mark]);
            mark++;
            bz=1;
        }
        if(bz&&mark==qiege){
            pthread_create(&t2,NULL,T2,aln);
            pthread_join(t2,NULL);
            bz=0,mark=0;
        }
    }
    if(filsh_aln){
        pthread_create(&t2,NULL,T2,aln);
        pthread_join(t2,NULL);
    }
    for(int i=0;i<qiege;i++){
        pthread_join(t1[i],NULL);
    }
    for(int i=0;i<qiege;i++){
        free(aln[i]);
    }
    shuchu();
    return 0;
}
static void *T1(void *arg){
    int *aln=(int *)arg;
    pthread_mutex_lock(&mtx);
    qsort(aln,N,sizeof(int),cmp);
    filsh_aln++;
    if(filsh_aln==qiege){
        pthread_cond_signal(&cond); //当所有子数组排序完成后将t2唤醒
    }
    pthread_mutex_unlock(&mtx);
    return NULL;
}
static void *T2(void *arg){
    pthread_mutex_lock(&mtx);
    int **n=(int **)arg;
    while(filsh_aln<qiege){
        pthread_cond_wait(&cond,&mtx); //t1的排序未完成t2将一直等待下去
    }
    for(int i=0;i<qiege;i++){
        memcpy(ans+i*N,n[i],N*sizeof(int));
    }
    qsort(ans,qiege*N,sizeof(int),cmp);
    filsh_aln=0;
    pthread_mutex_unlock(&mtx);
    return NULL;
}
void shuchu(){
    for(int i=0;i<all;i++){
        printf("%d ",ans[i]);
        if((i+1)%7==0){
            printf("\n");
        }
    }
}