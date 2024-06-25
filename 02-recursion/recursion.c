/*
 * Created by mac on 2024/6/24.
 * 递归
 * 主要是递归与非递归版本的转换
*/

#include <stdio.h>

#define MAXSIZE 1000
#define True 1
#define False 0

/* 1. 递归版本的汉诺塔问题 */
void Hanoi1(int n,char X, char Y, char Z){
    //只有一个盘片的情况
    if (n==1)
        printf("\t将第%d个盘片从%c移动到%c\n", n, X, Z);
    //有两个或多个盘片的情况
    else{
        Hanoi1(n-1, X, Z, Y);
        printf("\t将第%d个盘片从%c移动到%c\n", n, X, Z);
        Hanoi1(n-1, Y, X, Z);
    }
}

/* 2. 非递归版本的汉诺塔问题 */
typedef struct
{  int n;			//盘片个数
    char x, y, z;		//3个塔座
    int flag;	               //可直接移动盘片时为true，否则为false
} ElemType;			//顺序栈中元素类型

typedef struct
{  ElemType data[MAXSIZE];	//存放元素
    int top;			//栈顶指针
} StackType;			//顺序栈类型




int main(){
    Hanoi1(3, '1', '2', '3');
}
