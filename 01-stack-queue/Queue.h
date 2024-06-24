/*
 * Created by mac on 2024/6/23.
 * 队列
 *   front的后一个为即将出队的元素
 *   rear的指向最后一个入队的元素（也就是最新入队）
*/

#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define QUEUE_MAXSIZE 100
#define True 1
#define False 0

/* ------------------------- 顺序队列 ------------------------------- */

/* 队列数据结构
 * 顺序存储的实现
 * */
typedef struct _queue{
  ElemType data[QUEUE_MAXSIZE];
  int front, rear;
} Queue;

/* 1. 初始化对列
 * 空队列，front rear 指针均设置为-1
 * */
Queue* InitQueue(){
    Queue* Pq = (Queue*) malloc(sizeof(Queue));
    Pq->front = -1;
    Pq->rear = -1;
    return Pq;
}

/* 2. 销毁队列 */
void DestroyQueue(Queue* Pq){
    free(Pq);
}

/* 3. 判断是否为空 */
int IsEmpty_queue(Queue* Pq){
    return Pq->front == Pq->rear;
}

/* 4. 入队操作 */
int Push_queue(Queue* Pq, ElemType data){
    if (Pq->rear == QUEUE_MAXSIZE - 1)
        return False;
    Pq->rear++;
    Pq->data[Pq->rear] = data;
    return True;
}

/* 5. 出队操作 */
int Pop_queue(Queue* Pq, ElemType* data){
    if(IsEmpty_queue(Pq))
        return False;
    Pq->front++;
    *data = Pq->data[Pq->front];
    return True;
}

/* ------------------------- 环形队列操作 ------------------------------- */

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

/* ------------------------- 链表队列操作 ------------------------------- */
// TODO