#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// int cmp(const void *a,const void *b){
//     return *(int *)a-*(int *)b;
// }
// #define all 100000
// #define qiege 100
// #define N 1000
// static pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER; //互斥量的初始化
// static pthread_cond_t cond=PTHREAD_COND_INITIALIZER; //条件变量的初始化
// static void *T1(void *arg);
// static void *T2(void *arg);
// void shuchu();
// int ans[all],mark=0,filsh_aln=0;
// int main(){
//     srand(time(NULL));
//     pthread_t t1[qiege],t2;
//     int *aln[N],bz=0;
//     for(int i=0;i<qiege;i++){
//         aln[i]=(int *)malloc(sizeof(int)*N);
//     }
//     for(int i=0;i<all;i++){
//         aln[mark][i%N]=random()%INT_MAX;
//         if((i+1)%N==0){
//             pthread_create(&t1[mark],NULL,T1,aln[mark]);
//             mark++;
//             bz=1;
//         }
//         if(bz&&mark==qiege){
//             pthread_create(&t2,NULL,T2,aln);
//             pthread_join(t2,NULL);
//             bz=0,mark=0;
//         }
//     }
//     if(filsh_aln){
//         pthread_create(&t2,NULL,T2,aln);
//         pthread_join(t2,NULL);
//     }
//     for(int i=0;i<qiege;i++){
//         pthread_join(t1[i],NULL);
//     }
//     for(int i=0;i<qiege;i++){
//         free(aln[i]);
//     }
//     shuchu();
//     return 0;
// }
// static void *T1(void *arg){
//     int *aln=(int *)arg;
//     pthread_mutex_lock(&mtx);
//     qsort(aln,N,sizeof(int),cmp);
//     filsh_aln++;
//     if(filsh_aln==qiege){
//         pthread_cond_signal(&cond); //当所有子数组排序完成后将t2唤醒
//     }
//     pthread_mutex_unlock(&mtx);
//     return NULL;
// }
// static void *T2(void *arg){
//     pthread_mutex_lock(&mtx);
//     int **n=(int **)arg;
//     while(filsh_aln<qiege){
//         pthread_cond_wait(&cond,&mtx); //t1的排序未完成t2将一直等待下去
//     }
//     for(int i=0;i<qiege;i++){
//         memcpy(ans+i*N,n[i],N*sizeof(int));
//     }
//     qsort(ans,qiege*N,sizeof(int),cmp);
//     filsh_aln=0;
//     pthread_mutex_unlock(&mtx);
//     return NULL;
// }
// void shuchu(){
//     for(int i=0;i<all;i++){
//         printf("%d ",ans[i]);
//         if((i+1)%7==0){
//             printf("\n");
//         }
//     }
// }



#define len 100

struct px {
    int start;
    int end;
    int *aln;
};

static void *fen(void *arg);
void zhi(int *arr, int start, int end);
void shuchu(int *arr);

int main() {
    srand(time(NULL));
    struct px *x = (struct px *)malloc(sizeof(struct px));
    x->aln = (int *)malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++) {
        x->aln[i] = rand() % 1000;  
    }

    printf("原始数组:\n");
    shuchu(x->aln);

    pthread_t T;
    x->start = 0;
    x->end = len - 1;
    pthread_create(&T, NULL, fen, x);
    pthread_join(T, NULL);

    printf("\n排序后:\n");
    shuchu(x->aln);

    free(x->aln);
    free(x);
    return 0;
}

static void *fen(void *arg) {
    struct px *y = (struct px *)arg;
    if (y->start >= y->end) {
        free(y);
        return NULL;
    }

    int mid = y->start + (y->end - y->start) / 2;

    struct px *left = (struct px *)malloc(sizeof(struct px));
    struct px *right = (struct px *)malloc(sizeof(struct px));

    left->aln = y->aln;
    left->start = y->start;
    left->end = mid;

    right->aln = y->aln;
    right->start = mid + 1;
    right->end = y->end;

    pthread_t leftp, rightp;
    pthread_create(&leftp, NULL, fen, left);
    pthread_create(&rightp, NULL, fen, right);

    pthread_join(leftp, NULL);
    pthread_join(rightp, NULL);

    zhi(y->aln, y->start, y->end);
    free(y);  
    pthread_exit(NULL);
}


// 归并操作
void zhi(int *arr, int start, int end) {
    int mid = start + (end - start) / 2;
    int leftSize = mid - start + 1;
    int rightSize = end - mid;

    int *leftArr = (int *)malloc(sizeof(int) * leftSize);
    int *rightArr = (int *)malloc(sizeof(int) * rightSize);

    for (int i = 0; i < leftSize; i++) {
        leftArr[i] = arr[start + i];
    }
    for (int i = 0; i < rightSize; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = start;
    while (i < leftSize && j < rightSize) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }
    while (i < leftSize) {
        arr[k++] = leftArr[i++];
    }
    while (j < rightSize) {
        arr[k++] = rightArr[j++];
    }

    free(leftArr);
    free(rightArr);
}

// 输出数组
void shuchu(int *arr) {
    for (int i = 0; i < len; i++) {
        printf("%3d ", arr[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
}

// #define len 100

// static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER; // 互斥量
// static pthread_cond_t cond = PTHREAD_COND_INITIALIZER; // 条件变量

// struct px {
//     int start;
//     int end;
//     int *aln;
// };

// // 线程函数
// static void *fen(void *arg);
// // 归并函数
// void zhi(int *arr, int start, int end);
// // 打印数组
// void shuchu(int *arr);

// int main() {
//     srand(time(NULL));

//     struct px *x = (struct px *)malloc(sizeof(struct px));
//     x->aln = (int *)malloc(sizeof(int) * len);

//     for (int i = 0; i < len; i++) {
//         x->aln[i] = rand() % 1000;  
//     }

//     printf("原始数组:\n");
//     shuchu(x->aln);

//     pthread_t T;
//     x->start = 0;
//     x->end = len - 1;
//     pthread_create(&T, NULL, fen, x);
//     pthread_join(T, NULL);

//     printf("\n排序后:\n");
//     shuchu(x->aln);
//     if(x->aln!=NULL) free(x->aln);
//     if(x!=NULL) free(x);
//     return 0;
// }

// // 线程函数：归并排序
// static void *fen(void *arg) {
//     struct px *y = (struct px *)arg;
//     if (y->start >= y->end) {
//         if(y!=NULL){
//         free(y); 
//         }
//         return NULL;
//     }

//     int mid = y->start + (y->end - y->start) / 2;

//     // **动态分配子任务结构体，避免局部变量失效**
//     struct px *left = (struct px *)malloc(sizeof(struct px));
//     struct px *right = (struct px *)malloc(sizeof(struct px));

//     left->aln = y->aln;
//     left->start = y->start;
//     left->end = mid;

//     right->aln = y->aln;
//     right->start = mid + 1;
//     right->end = y->end;

//     pthread_t leftp, rightp;
//     pthread_create(&leftp, NULL, fen, left);
//     pthread_create(&rightp, NULL, fen, right);
//     pthread_join(leftp, NULL);
//     pthread_join(rightp, NULL);
//     zhi(y->aln, y->start, y->end);
//     if(left!=NULL) free(left);
//     if(right!=NULL) free(right);
//     if(y!=NULL) free(y);  
//     return NULL;
// }

// // 归并操作
// void zhi(int *arr, int start, int end) {
//     int mid = start + (end - start) / 2;
//     int leftSize = mid - start + 1;
//     int rightSize = end - mid;

//     int *leftArr = (int *)malloc(sizeof(int) * leftSize);
//     int *rightArr = (int *)malloc(sizeof(int) * rightSize);

//     for (int i = 0; i < leftSize; i++) {
//         leftArr[i] = arr[start + i];
//     }
//     for (int i = 0; i < rightSize; i++) {
//         rightArr[i] = arr[mid + 1 + i];
//     }

//     int i = 0, j = 0, k = start;
//     while (i < leftSize && j < rightSize) {
//         if (leftArr[i] <= rightArr[j]) {
//             arr[k++] = leftArr[i++];
//         } else {
//             arr[k++] = rightArr[j++];
//         }
//     }
//     while (i < leftSize) {
//         arr[k++] = leftArr[i++];
//     }
//     while (j < rightSize) {
//         arr[k++] = rightArr[j++];
//     }

//     if(leftArr!=NULL) free(leftArr);
//     if(rightArr!=NULL) free(rightArr);
// }

// // 输出数组
// void shuchu(int *arr) {
//     for (int i = 0; i < len; i++) {
//         printf("%3d ", arr[i]);
//         if ((i + 1) % 10 == 0) {
//             printf("\n");
//         }
//     }
// }

// static pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER; //互斥量的初始化
// static pthread_cond_t cond=PTHREAD_COND_INITIALIZER; //条件变量的初始化
// static void *fen(void *arg);
// void zhi(int *arr,int start,int end);
// void shuchu();
// #define len 100
// struct px{
//     int start;
//     int end;
//     int *aln;
// };
// int main(){
//     srand(time(NULL));
//     struct px *x;
//     x=(struct px *)malloc(sizeof(struct px));
//     x->aln=(int *)malloc(sizeof(int)*len);
//     for(int i=0;i<len;i++){
//         x->aln[i]=random()%INT_MAX;
//     }
//     pthread_t T;
//     x->start=0;
//     x->end=len-1;
//     pthread_create(&T,NULL,fen,x);
//     shuchu();
//     free(x->aln);
//     free(x);
//     return 0;
// }
// static void *fen(void *arg){
//     struct px *y=(struct px*)arg;
//     if(y->start>=y->end){
//         return NULL;
//     }
//     struct px left;
//     int mid=y->start+(y->end-y->start)/2;
//     left.aln=y->aln;
//     left.start=y->start;
//     left.end=mid;
//     struct px right;
//     right.aln=y->aln;
//     right.start=mid+1;
//     right.end=y->end;
//     pthread_t leftp,rightp;
//     int s;
//     s=pthread_create(&leftp,NULL,fen,&left);
//     if(s){
//         printf("left thread fail\n");
//         return NULL;
//     }
//     s=pthread_create(&rightp,NULL,fen,&right);
//     if(s){
//         printf("right thread fail\n");
//         return NULL;
//     }
//     pthread_join(leftp,NULL);
//     pthread_join(rightp,NULL);
//     zhi(y->aln,y->start,y->end);
//     return NULL;
// }
// void zhi(int *arr,int start,int end){
//     int *temp=(int *)malloc(sizeof(int)*(end-start+1));
//     int i=start;
//     int j=(end-start)/2+1;
//     int mid=j;
//     int k=0;
//     while(i<=mid&&j<=end){
//         if(arr[i]<=arr[j]){
//             temp[k++]=arr[i++];
//         }else{
//             temp[k++]=arr[j++];
//         }
//     }
//     while(i<=start){
//         temp[k++]=arr[i++];
//     }
//     while(j<=end){
//         temp[k++]=arr[j++];
//     }
//     free(temp);
// }
// void shuchu(){
//     struct px num;
//     for(int i=0;i<len;i++){
//         printf("%d ",num.aln[i]);
//         if(i%7==0){
//             printf("\n");
//         }
//     }
// }
