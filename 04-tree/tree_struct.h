/*
 * Created by mac on 2024/5/7.
 * 本头文件定义树的数据结构
 * this file is used to define the data struct of tree
 * 空指针数：n个节点，m次树
 * */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*宏定义*/
#define PTree_MaxSize 32
#define MaxSons 5
#define MaxSize 32

/*节点数据类型*/
typedef char Data;

/*-------------------------------1. 树的存储结构-------------------------------------------*/
/*
 * 双亲存储结构
 * 优点：查找双亲很快
 * 缺点：浪费存储空间
 * */
struct Tree_Parents_mem_node{
   Data data;   // 节点数据
   int parent;  // 双亲在数组的位置
} PTree[PTree_MaxSize];

/* 孩子链存储结构
 * 空指针：m*n-(n-1) O(mn)
 * 优点：查孩子快速
 * 缺点：浪费指针
 * */
typedef struct Tree_KidLink_node{
    Data data;
    struct Tree_KidLink_node* sons[MaxSons];
}TSonNode;

/*
 * 孩子兄弟链存储
 * 空指针：n+1 O(n)
 * */
typedef struct Tree_KidBro_node{
    Data data;
    struct Tree_KidBro_node *Kp;   // 孩子指针
    struct Tree_KidBro_node *Bp;   // 兄弟指针
}TSBNode;

/*
 * 二叉链表存储
 * */
typedef struct BiTree_LinkNode{
    Data data;
    struct BiTree_LinkNode *Lp; // 左孩子
    struct BiTree_LinkNode *Rp; // 右孩子
    struct BiTree_LinkNode *Pp; // 双亲
    char LRTag; // 左右孩子标识, 左L， 右R， root^
}BTNode;

/*-------------------------------2. 二叉树的基本运算-------------------------------------------*/
/*
 * 创建二叉树
 * 易错点：这里需要修改头节点指针，所以要传入二级指针
 * */
void CreateBTree(BTNode** b, char* str){
    BTNode* stack[MaxSize]; // 栈，用于存储根节点
    BTNode *p;  // 生成的新节点指针
    int top = -1;   // 栈顶指针
    char ch;
    *b = NULL;   // 初始化头节点
    int flag = 0;   // 左右标识符

    int str_length = strlen(str);
    for(int i=0; i<str_length; i++){
        // 1.取字符
        ch = str[i];

        // 2.进入不同的情况
        switch (ch) {
            case '(':
                top++;
                stack[top] = p;
                break;
            case ')':
                flag = 0;
                top--;
                break;
            case ',':
                flag = 1;
                break;
            default:
                p = (BTNode*) malloc(sizeof(BTNode));   // 创建节点
                if(*b==NULL) *b = p;  //如果头节点空，给头节点赋指针
                p->data = ch;   // 数据域赋值
                p->Lp = NULL;   // 指针域赋值
                p->Rp = NULL;

                if(flag && top!=-1) {
                    stack[top]->Rp = p;
                    p->LRTag = 'R';
                }
                else if(!flag && top!=-1) {
                    stack[top]->Lp = p;
                    p->LRTag = 'L';
                }
                else p->LRTag = '^';
                break;
        }
    }
}

/*
 * 销毁二叉树
 * */
void DestroyBTree(BTNode* b){
    if(b==NULL) return;
    else{
        DestroyBTree(b->Lp);
        DestroyBTree(b->Rp);
        free(b);
    }
}

/*
 * 查找节点
 * */
BTNode* FindNode(BTNode* b, Data x){
    BTNode *p;
    if(b == NULL)   return NULL;
    if(b->data == x) return b;
    else{
        p = FindNode(b->Lp, x);
        if(p!=NULL) return p;
        else return FindNode(b->Rp, x);
    }
}

/*
 * 集合化输出二叉树
 * TODO:这里存在一个bug，就是无论有没有子树，()和，均会出现
 * */
void Display(BTNode* b){
    if (b==NULL) return;
    printf("%c(", b->data);
    Display(b->Lp);
    printf(",");
    Display(b->Rp);
    printf(")");
}
void DispTree(BTNode* b){
    /*再封装一次*/
    Display(b);
    printf("\n");
}







