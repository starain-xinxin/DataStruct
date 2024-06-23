/*
 * Created by mac on 2024/6/22.
 * 线性表代码
*/

#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define MAXSIZE 100


/* ------------------------------- 顺序表 --------------------------------- */
/* 顺序表的数据结构 */
typedef struct _Sequence_List{
    ElemType data[MAXSIZE];
    int length;
}SqList;

/* 1.1 顺序表的创建
 * 通过已有的数组来创建
 * */
SqList* CreateSqList(ElemType list[MAXSIZE], int len){
    int i;
    SqList* Pl = (SqList*) malloc(sizeof(SqList));
    for(i=0; i<len; i++){
        Pl->data[i] = list[i];
    }
    Pl->length = len;
    return Pl;
}

/* 1.2 顺序表的创建
 * 构造空的顺序表
 * */
SqList* InitList(){
    SqList* Pl = (SqList*) malloc(sizeof(SqList));
    Pl->length = 0;
    return Pl;
}

/* 2. 销毁List */
void DestroyList(SqList* Pl){
    free(Pl);
}

/* 3. 是否为空表 */
int IsEmpty_SqList(SqList* Pl){
    return Pl->length == 0;
}

/* 4. 顺序表长度 */
int SqLen(SqList* Pl){
    return Pl->length;
}

/* 5. 打印顺序表 */
void DispSqList(SqList* Pl){
    int len = Pl->length;
    printf("线性表：%d\n", len);
    for(int i=0; i<len; i++){
        printf("(%d):%d  ", i, Pl->data[i]);
    }
    printf("\n");
}

/* 6. 获取某data元素 */
int GetElem(SqList* Pl, int index, ElemType* e){
    if (index<0 || index>=Pl->length) return 0;
    *e = Pl->data[index];
    return 1;
}

/* 7. 查找元素 */
int FindElem(SqList* Pl, ElemType data){
    int len = Pl->length;
    int i;
    for (i=0; i<len; i++){
        if (data == Pl->data[i])
            break;
    }
    if (i == len)
        return -1;
    else
        return i;
}

/* 8. 插入数据 */
int InsertSqList(SqList* Pl, int index, ElemType data){
    int len = Pl->length;
    if (index >= len){      // 如果插入位置太大
        Pl->length++;
        Pl->data[len] = data;
        return 1;
    }
    else if (index < 0)
        return 0;
    else {
        for (int i = len - 1; i >= index; i--) {
            Pl->data[i + 1] = Pl->data[i];
        }
        Pl->data[index] = data;
        Pl->length++;
        return 1;
    }
}

/* 9. 删除元素 */
int DeleteSqList(SqList* Pl, int index){
    int len = Pl->length;
    if(index>=0 && index<len){
        Pl->length--;
        for(int i=index; i<len; i++) {
            Pl->data[i] = Pl->data[i + 1];
        }
        return 1;
    }
    else
        return 0;
}

/* 10. 删除所有data为特定值的元素
 * 时间O(n),空间O(1)
 * 双指针的算法，消除每次删除元素的重复搬移
 * */
void DeleteData(SqList* Pl, ElemType data){
    int new_p, p;
    int len = Pl->length;
    for (p=0,new_p=0; p<len; p++){
        if (Pl->data[p] == data)
            continue;
        else{
            Pl->data[new_p] = Pl->data[p];
            new_p++;
        }
    }
    Pl->length = new_p;     // 这一步不要忘记
}

/* 基准分割
 * 以首个元素为基准，小于等于放前面，大于放后面
 * 时间复杂度O(n),空间复杂度O(1)
 * */
void BaseMove(SqList* Pl){
    int len = Pl->length;
    int p1 = 0, p2 = len - 1;
    ElemType base = Pl->data[0];
    while(p2 > p1){
        // 首先p2移动
        for (;p2>p1;p2--){
            if (Pl->data[p2] <= base){
                Pl->data[p1] = Pl->data[p2];
                p1++;
                break;
            }
        }
        // p1移动
        for (;p2>p1;p1++){
            if (Pl->data[p1] > base){
                Pl->data[p2] = Pl->data[p1];
                p2--;
                break;
            }
        }
    }
    Pl->data[p1] = base;
}

/* ------------------------------- 链表 --------------------------------- */

/* 链表节点的数据结构 */
typedef struct _Link_Node{
    ElemType data;
    struct _Link_Node* next;
}LinkNode;

/* 1.1 创建链表
 * 头插法
 * */
void CreateLink_head(LinkNode* P_head, ElemType a[MAXSIZE], int len){
    for (int i=0; i<len; i++) {
        LinkNode *p_new = (LinkNode *) malloc(sizeof(LinkNode));
        p_new->data = a[i];
        p_new->next = P_head->next;
        P_head->next = p_new;
    }
    P_head->data = len;     // 头节点数据域：放置链表长度
}

/* 1.2 创建链表
 * 尾插法
 * */
void CreateLink_tail(LinkNode* P_head, ElemType a[MAXSIZE], int len){
    LinkNode* p_tail = P_head;
    for (int i=0; i<len; i++){
        LinkNode *p_new = (LinkNode *) malloc(sizeof(LinkNode));
        p_new->data = a[i];
        p_new->next = NULL;
        p_tail->next = p_new;
        p_tail = p_new;
    }
    P_head->data = len;     // 头节点数据域：放置链表长度
}

/* 2. 初始化链表
 * 即创建一个头节点
 * 需要注意的是记得初始化头节点的next指针
 * */
LinkNode* InitLink(){
    LinkNode* P_head = (LinkNode*) malloc(sizeof(LinkNode));
    P_head->next = NULL;
    return P_head;
}

/* 3. 销毁链表 */
void DestroyLink(LinkNode* P_head){
    LinkNode* p_del = P_head->next;
    while(p_del){
        free(P_head);
        P_head = p_del;
        p_del = P_head->next;
    }
    free(P_head);
}

/* 4. 输出链表 */
void DispLink(LinkNode* P_head){
    printf("链表：%d\n", P_head->data);
    P_head = P_head->next;
    int i = 0;
    while(P_head){
        printf("(%d):%d  ", i, P_head->data);
        P_head = P_head->next;
        i++;
    }
    printf("\n");
}

/* 5. 通过索引找到数据
 * 找到返回1，没找到返回0
 * */
int GetElem_link(LinkNode* P_head, int index, ElemType* p_data){
    LinkNode* p = P_head->next;
    int i = 0;
    while(p && i != index){
        i++;
        p = p->next;
    }
    if (i == index)
        *p_data = p->data;
    else
        return 0;
    return 1;
}

/* 6. 通过数据找到索引
 * 找到返回索引，没找到返回-1
 * */
int FindElem_link(LinkNode* P_head, ElemType data){
    LinkNode* p = P_head->next;
    int i = 0;
    while(p){
        if (p->data == data)
            return i;
        p = p->next;
        i++;
    }
    return -1;
}

/* 7. 插入元素
 * 大于链表总长度的一律放在队尾
 * 成功插入返回1，不成功返回0
 * ! 不要忘了头节点维护
 * */
int InsertElem_link(LinkNode* P_head, int index, ElemType data){
    int len = P_head->data;
    if (index < 0)
        return 0;
    LinkNode* p = P_head->next;
    LinkNode* p_pre = P_head;
    int i = 0;
    while (p && i != index){
        p_pre = p;
        p = p->next;
        i++;
    }
    LinkNode* p_new = (LinkNode*) malloc(sizeof(LinkNode));
    p_new->data = data;
    p_new->next = p;
    p_pre->next = p_new;
    P_head->data++;
    return 1;
}

/* 8. 删除元素
 * 成功删除返回1，不成功返回0
 * ! 不要忘了头节点维护
 * */
int DeleteElem_link(LinkNode* P_head, int index, ElemType* e){
    int len = P_head->data;
    if (index<0 || index >= len)
        return 0;
    LinkNode *p = P_head->next, *p_pre;
    int i = 0;
    while(p && i != index){
        p_pre = p;
        p = p->next;
        i++;
    }
    p_pre->next = p->next;
    free(p);
    P_head->data--;
    return 0;
}

/* 9. 链表逆序
 * 利用头插法即可
 * */
void Reverse_link(LinkNode* P_head){
    LinkNode* p_tmp = P_head->next, *p_next;
    P_head->next = NULL;
    while (p_tmp){
        p_next = p_tmp->next;
        p_tmp->next = P_head->next;
        P_head->next = p_tmp;
        p_tmp = p_next;
    }
}

/* 10. 查找倒数第k个元素
 * 利用双指针，一个先走k步，两个再同时走
 * (这里不利用头节点存储的链表Length)
 * */
int Reverse_Search_k(LinkNode* P_head, int k, ElemType* data){
    LinkNode* p1 = P_head, *p2 = P_head;
    // p2节点先走k步
    int i = 0;
    while(p2 && i != k){
        p2 = p2->next;
        i++;
    }
    if (i != k)
        return 0;
    // p1,p2同时走
    while (p2){
        p1 = p1->next;
        p2 = p2->next;
    }
    *data = p1->data;
    return 1;
}

/* 11. 删除给定指针的节点
 * 平均时间复杂度：O(1)
 * 思路是后继节点复制到删除节点上，然后删除后继节点
 * */
void FastDel_link(LinkNode* P_head, LinkNode* p_del){
    // 删除尾节点
    if (p_del->next == NULL){
        LinkNode* p_pre, *p = P_head;
        while(p != p_del){
            p_pre = p;
            p = p->next;
        }
        p_pre->next = NULL;
        free(p);
    }
    // 删除非尾部节点
    else{
        LinkNode* p_tmp = p_del->next;
        p_del->data = p_tmp->data;
        p_del->next = p_tmp->next;
        free(p_tmp);
    }
    P_head->data--;
}

/* 12. 单链表环入口
 * 时间复杂度：O(n)
 * 思路是快慢指针，先重合在第一个相遇点，
 * 然后慢指针重新回到头节点，然后快慢指针均每一步前进一个格子。
 * */
LinkNode* CycleEntry_link(LinkNode* P_head){
    LinkNode *fast = P_head, *slow = P_head;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        // 相遇 --> 有环
        if (fast == slow){
            slow = P_head;
            while(fast != slow){
                fast = fast->next;
                slow = slow->next;
            }
            return slow;
        }
    }
    return NULL;
}