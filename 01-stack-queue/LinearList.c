/*
 * Created by mac on 2024/6/22.
 * 线性表测试代码
*/

#include "Linear_list.h"

int main(){
    ElemType arr[10] = {1,2,3,2,4,10,7,2,6,9};

    printf("/* ------------------------------- 顺序表 --------------------------------- */\n");
    // 1. 创建顺序表
    SqList* PList;
    PList = CreateSqList(arr, 10);
    DispSqList(PList);

    // 2. 增删查改
    InsertSqList(PList, 4, 10);
    DispSqList(PList);

    DeleteSqList(PList, 8);
    DispSqList(PList);

    int data = 2;
    int find_index = FindElem(PList, data);
    printf("找到的索引：%d", find_index);

    // 3. 删除所有data=2的元素
    DeleteData(PList, data);
    DispSqList(PList);

    PList->data[0] = 7;
    DispSqList(PList);

    // 4. 基准分割
    BaseMove(PList);
    DispSqList(PList);

    printf("/* ------------------------------- 链表 --------------------------------- */\n");
    // 1. 创建链表与销毁链表
    LinkNode* link = InitLink();
    LinkNode* link2 = InitLink();

    CreateLink_head(link, arr, 10);
    DispLink(link);
    CreateLink_tail(link2, arr, 10);
    DestroyLink(link2);

    // 2. 索引 --> 数据     数据 --> 索引
    int flag = GetElem_link(link, 3, &data);
    printf("flag:%d  index:%d  data:%d\n", flag, 3, data);

    data = 3;
    flag = FindElem_link(link, data);
    printf("data:%d  找到索引:%d\n", data, flag);

    data = 13;
    flag = FindElem_link(link, data);
    printf("没找到索引,flag:%d\n", flag);

    // 3. 增 删
    flag = InsertElem_link(link, 8, data);
    DispLink(link);

    flag = DeleteElem_link(link, 8, &data);
    DispLink(link);

    // 4. 翻转链表
    Reverse_link(link);
    DispLink(link);

    // 5. 查找倒数第k个元素
    flag = Reverse_Search_k(link, 3, &data);
    printf("flag:%d  k:%d  data:%d\n", flag, 3, data);

    // 6. 平均 O(1) 删除给定节点
    LinkNode *pp = link, *p_tail = link;
    int num = 0;
    while(num != 5){
        pp = pp->next;
        num++;
    }
    while(p_tail->next){
        p_tail = p_tail->next;
    }
    FastDel_link(link, pp);
    DispLink(link);
    FastDel_link(link, p_tail);
    DispLink(link);

    // 7. 单链表成环的判断与环入口
    pp = link, p_tail = link, num = 0;
    while(num != 5){
        pp = pp->next;
        num++;
    }
    while(p_tail->next){
        p_tail = p_tail->next;
    }
    p_tail->next = pp;
    printf("已知环入口指针：%p\n", pp);

    LinkNode* p_entry = CycleEntry_link(link);
    printf("算法给出的入口指针：%p\n", p_entry);

}
