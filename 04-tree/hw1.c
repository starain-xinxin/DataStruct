/*
 * Created by mac on 2024/5/7.
 * OJ1 根据两种遍历确定树的结构
 * */
#include<stdio.h>
#include<stdlib.h>

#define MaxN 100
#define MaxQueue 100

typedef int Data;

typedef struct BiTree_LinkNode{
    Data data;
    struct BiTree_LinkNode *Lp; // 左孩子
    struct BiTree_LinkNode *Rp; // 右孩子
}BTNode;

/*
 * 先序遍历
 * 根-左-右
 * */
void PreOrder(BTNode* b){
    if(b){
        printf("%d ", b->data);
        PreOrder(b->Lp);
        PreOrder(b->Rp);
    }
}
void PreDisp(BTNode* b){
    PreOrder(b);
    printf("\n");
}

/*
 * 中序遍历
 * 左-根-右
 * */
void InOrder(BTNode* b){
    if(b){
        InOrder(b->Lp);
        printf("%d ", b->data);
        InOrder(b->Rp);
    }
}
void InDisp(BTNode* b){
    InOrder(b);
    printf("\n");
}

/*
 * 后序遍历
 * 左-右-根
 * */
void PostOrder(BTNode* b){
    if(b){
        PostOrder(b->Lp);
        PostOrder(b->Rp);
        printf("%d ", b->data);
    }
}
void PostDisp(BTNode* b){
    PostOrder(b);
    printf("\n");
}

void LevelOrder(BTNode* b){
    BTNode *p;

    // 1.定义一个队列
    BTNode* queue[MaxQueue] = {0};
    int top = -1;
    int tail = -1;

    // 2.初始化队列
    if (b == NULL) return;
    else queue[0] = b;
    top++;
    tail++;

    // 3.遍历
    while(top <= tail){
        p = queue[top];
        top++;
        if(p->Lp) {
            tail++;
            queue[tail] = p->Lp;
        }
        if(p->Rp){
            tail++;
            queue[tail] = p->Rp;
        }
        printf("%d ", p->data);
    }
}

/* 先序+中序 */
BTNode* PreAndIn(Data str1[MaxN], Data str2[MaxN], int n){
    // 创建节点
    if(n <= 0) return NULL;
    BTNode* b = (BTNode*)malloc(sizeof(BTNode));

    // 找到节点数据和位置
    int flag = 1;
    int i;
    for(i=0; i<n; i++){
        if(str1[0] == str2[i]) {flag = 0; break;}
    }
    if (flag) return NULL;  // 没找到匹配的数据

    // 更新节点信息
    b->data = str1[0];
    b->Lp = PreAndIn(str1+1, str2, i);
    b->Rp = PreAndIn(str1+i+1, str2+i+1, n-i-1);
    return b;
}

/*
 * 先序+后序列
 * 这里的坑在于边界检查 if(n==1)那里
 * */
BTNode* PreAndPost(Data str1[MaxN], Data str2[MaxN], int n){
    // 创建节点
    if(n <= 0) return NULL;
    BTNode* b = (BTNode*)malloc(sizeof(BTNode));
    if(n == 1){
        b->data = str1[0];
        b->Lp = NULL;
        b->Rp = NULL;
        return b;
    }
    else if(n==2){  // 这一段实际不需要
        b->data = str1[0];
        BTNode* bb = (BTNode*)malloc(sizeof(BTNode));
        bb->data = str1[1];
        b->Lp = bb;
        b->Rp = NULL;
        bb->Lp = NULL; bb->Rp = NULL;
        return b;
    }

    // 找到节点数据和位置
    int flag1 = 1, flag2 = 1;
    int i1, i2;
    for(i1=0; i1<n; i1++){  // 左节点的开端
        if(str1[1] == str2[i1]) {flag1 = 0; break;}
    }
    if (flag1) return NULL;
    for(i2=0; i2<n; i2++){  // 右节点的开端
        if(str1[i2] == str2[n-2]) {flag2 = 0; break;}
    }
    if (flag2) return NULL;

    // 更新节点信息
    b->data = str1[0];
    b->Lp = PreAndPost(str1+1, str2, i1+1);
    b->Rp = PreAndPost(str1+i2, str2+i2-1,n-i2);

    return b;
}

/* 中序+后序列 */
BTNode* InAndPost(Data str1[MaxN], Data str2[MaxN], int n){
    // 创建节点
    if(n <= 0) return NULL;
    BTNode* b = (BTNode*)malloc(sizeof(BTNode));

    // 找到节点数据和位置
    int flag = 1;
    int i;
    for(i=0; i<n; i++){
        if(str1[i] == str2[n-1]) {flag = 0; break;}
    }
    if (flag) return NULL;  // 没找到匹配的数据

    // 更新节点信息
    b->data = str1[i];
    b->Lp = InAndPost(str1, str2, i);
    b->Rp = InAndPost(str1+i+1, str2+i, n-i-1);
    return b;
}


int main(){
    // 1.接受输入
    int n,k;
    int str1[MaxN] = {0}; int str2[MaxN] = {0};
    scanf("%d %d", &n, &k);
    for(int i=0; i<n; i++)
        scanf("%d", str1+i);
    for(int i=0; i<n; i++)
        scanf("%d", str2+i);

    // 2.获得树的结构
    BTNode *p;
    switch(k) {
        case 0:
            p = PreAndPost(str1, str2, n);
            break;
        case 1:
            p = PreAndIn(str1, str2, n);
            break;
        case 2:
            p = InAndPost(str1, str2, n);
            break;
        case 3:
            p = PreAndPost(str1, str2, n);
            break;
    }

    // 3.输出
    switch(k) {
        case 0:
            InOrder(p);
            break;
        case 1:
            PostOrder(p);
            break;
        case 2:
            PreOrder(p);
            break;
        case 3:
            LevelOrder(p);
            break;
    }
}