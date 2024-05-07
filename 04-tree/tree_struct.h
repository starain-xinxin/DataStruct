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
#define MaxQueue 32

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
                flag = 0;
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

/*-------------------------------3. 二叉树的递归遍历-------------------------------------------*/
/*
 * 先序遍历
 * 根-左-右
 * */
void PreOrder(BTNode* b){
    if(b){
        printf("%c", b->data);
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
        printf("%c", b->data);
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
        printf("%c", b->data);
    }
}
void PostDisp(BTNode* b){
    PostOrder(b);
    printf("\n");
}


/*-------------------------------4. 一些树的递归的无聊问题-------------------------------------------*/
/*
 * 树的节点总数
 * */
int NodeNum(BTNode* b){
    if(b==NULL) return 0;
    return NodeNum(b->Rp) + NodeNum(b->Lp) + 1;
}
void DispNum(BTNode* b){
    printf("%d", NodeNum(b));
}

/*
 * 输出树的叶子节点
 * */
void DispLeaf(BTNode* b){
    if(b == NULL) return;
    if(!(b->Lp) && !(b->Rp))
        printf("%c",b->data);
    DispLeaf(b->Lp);
    DispLeaf(b->Rp);
}

/*
 * 查找指定data的节点所在树的层级
 * */
int Level(BTNode* b, int level, Data x){
    if(b==NULL) return 0;
    if(b->data == x)
        return level;
    else{
        int L = Level(b->Lp, level+1, x);
        if(L) return L;
        else return Level(b->Rp, level+1, x);
    }
}

/*
 * 计算树的第k层的节点数
 * */
void KLevelNodes(BTNode* b, int AimLevel, int NodeLevel, int* mem_num){
    if(b==NULL) return;
    if(NodeLevel==AimLevel) *mem_num = *mem_num + 1;
    else if(NodeLevel < AimLevel)  {
        KLevelNodes(b->Rp, AimLevel, NodeLevel+1, mem_num);
        KLevelNodes(b->Lp, AimLevel, NodeLevel+1, mem_num);
    }
    else return;
}
int NumberOfKLevelNodes(BTNode* b, int AimLevel, int NodeLevel){
    int num = 0;
    KLevelNodes(b, AimLevel, NodeLevel, &num);
    return num;
}

/*
 * TODO:树B PPT 例7-15，7-16
 * */

/*-------------------------------5. 树的非递归遍历-------------------------------------------*/

/*-------------------------------6. 树的层次遍历-------------------------------------------*/
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
        printf("%c", p->data);
    }
    printf("\n");
}