#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


#define len 10000000
#define minnum 5000  //当小数组里面数量少时,直接排序
static pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER; //互斥量的初始化
static pthread_cond_t cond=PTHREAD_COND_INITIALIZER; //条件变量的初始化

typedef struct {
    int *arr;
    int left;
    int right;
}px;
void hebin(int *arr, int left, int mid, int right);
void gbpx(int *arr, int left, int right);
static void *fen(void *args);
void shuchu(int *arr, int size);


int main() {
    int *arr = (int *)malloc(sizeof(int) * len);
    srand(time(NULL));
    for(int i=0;i<len;i++){
        arr[i]=random()%100000;
    }
    px args = {arr, 0, len - 1};
    pthread_t T;
    pthread_create(&T,NULL,fen,&args);
    pthread_join(T,NULL);
    shuchu(arr, len);
    free(arr);
    return 0; 
}
void hebin(int *arr, int left, int mid, int right) {
    int leftSize=mid-left+1;
    int rightSize=right-mid;
    int *leftarr=(int *)malloc(sizeof(int)*leftSize);
    int *rightarr=(int *)malloc(sizeof(int)*rightSize);

    for (int i=0;i<leftSize;i++){
        leftarr[i] = arr[left + i];
    }
    for (int i=0;i<rightSize;i++){
        rightarr[i] = arr[mid + 1 + i];
    }
    int i = 0, j = 0, k = left;
    while (i < leftSize && j < rightSize){
        if(leftarr[i]<=rightarr[j]){
            arr[k++]=leftarr[i++];
        }else{
            arr[k++]=rightarr[j++];
        }
    }
    while (i < leftSize){ 
    arr[k++] = leftarr[i++];
    }
    while (j < rightSize) {
    arr[k++] = rightarr[j++];
    }
    free(leftarr);
    free(rightarr);
}

void gbpx(int *arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        gbpx(arr, left, mid);
        gbpx(arr, mid + 1, right);
        hebin(arr, left, mid, right);
    }
}

static void *fen(void *args) {
    px *data=(px *)args;
    int left=data->left;
    int right=data->right;
    int *arr=data->arr;
    if (right-left+1<=minnum) {
        gbpx(arr, left, right);
    } else {
        int mid=left+(right-left)/2;
        px leftnum={arr,left,mid};
        px rightnum={arr,mid+1,right};
        pthread_t leftp, rightp;
        pthread_create(&leftp,NULL,fen,&leftnum);
        pthread_create(&rightp,NULL,fen,&rightnum);
        pthread_join(leftp,NULL);
        pthread_join(rightp,NULL);
        hebin(arr,left,mid,right);
        pthread_mutex_lock(&mtx);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

void shuchu(int *arr, int size) {
    for (int i =0;i<size;i++) {
        printf("%d ",arr[i]);
        if((i+1)%10==0){
            printf("\n");
        }
    }
}