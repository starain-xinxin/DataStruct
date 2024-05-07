/*
 * Created by mac on 2024/5/7.
 * 这个文件是一些算法的实现
 * */

#include "tree_struct.h"
#include<assert.h>

/*
 * 孩子链存储结构
 * 求出树的高度
 * 递归解法，出口是指针指向空，所以这个指针指向的子树是一个空树，返回子树高度为0*/
int TreeHeight1(TSonNode* t){
    int i;
    int h, MaxH = 0;
    if(t==NULL) return 0;
    else {
        for (i = 0; i < MaxSons; i++) {
            h = TreeHeight1(t->sons[i]);
            if (h > MaxH) MaxH = h;
        }
        return MaxH + 1;
    }
}

/*
 * 孩子兄弟链存储结构
 * 求出树的高度
 * 递归解法，出口是指针指向空，所以这个指针指向的子树是一个空树，返回子树高度为0*/
int TreeHeight2(TSBNode* t){
    TSBNode* p;
    int h, MaxH = 0;
    if(t==NULL) return 0;
    else{
        p = t->Kp;
        while(p){
            h = TreeHeight2(p);
            if(h > MaxH) MaxH = h;
            p = p->Bp;
        }
        return MaxH + 1;
    }
}

int main(){
    BTNode *p = NULL, *k1, *k2;

    /* 1.根据括号表示发创建二叉树的字符串 */
    Data tree_str1[100] = "A(B(D(,G)),C(E,F))";
    CreateBTree(&p, tree_str1);

    /* 2.查找 */
    k1 = FindNode(p, 'D');
    k2 = FindNode(p, 'H');
    assert(k1->data == 'D');
    assert(k2 == NULL);

    DispTree(p);


}