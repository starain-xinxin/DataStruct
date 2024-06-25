#include "stdio.h"
#include "stdlib.h"

#define QUEUE_MAXSIZE 1000
#define ElemType int
#define True 1
#define False 0

typedef struct _circle_queue{
    ElemType data[QUEUE_MAXSIZE];
    int front;
    int count;      // 队列元素个数
}CrQueue;

/* 1. 初始化队列 */
CrQueue* InitQueue_cr(){
    CrQueue* Pcq = (CrQueue*) malloc(sizeof(CrQueue));
    Pcq->front = 0;
    Pcq->count = 0;
    return Pcq;
}

/* 2. 队列是否为空 */
int IsEmpty_cq(CrQueue* Pcq){
    return Pcq->count == 0;
}

/* 3. 入队操作 */
int Push_CrQueue(CrQueue* Pcq, ElemType data){
    int rear;
    if (Pcq->count == QUEUE_MAXSIZE)    // 上溢出
        return False;
    rear = (Pcq->front + Pcq->count) % QUEUE_MAXSIZE;   // 队尾的位置
    // 如顺序队列一样入队
    rear = (rear + 1) % QUEUE_MAXSIZE;
    Pcq->data[rear] = data;
    Pcq->count++;       // 这一步不要忘记
    return True;
}

/* 4. 出队操作 */
int Pop_CrQueue(CrQueue* Pcq, ElemType* data){
    if (IsEmpty_cq(Pcq))
        return False;
    Pcq->front = (Pcq->front + 1) % QUEUE_MAXSIZE;
    *data = Pcq->data[Pcq->front];
    Pcq->count--;
    return True;
}
