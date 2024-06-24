/*
 * Created by mac on 2024/6/23.
 * 栈
 * 说明：为了与计算机体系结构的栈匹配
 * 栈指针top总是指向栈顶元素，无元素时，top=-1
*/

#include <stdio.h>
#include <stdlib.h>

#define ElemType char
#define  STACK_MAXSIZE 100
#define True 1
#define False 0

/* 顺序栈的数据结构 */
typedef struct _stack{
    ElemType data[STACK_MAXSIZE];
    int top;
}Stack;

/* ------------------------------- 栈的基本操作 --------------------------------- */

/* 1. 初始化栈 */
Stack* InitStack(){
    Stack *Ps = (Stack*) malloc(sizeof(Stack));
    Ps->top = -1;
    return Ps;
}

/* 2. 销毁栈 */
void DestroyStack(Stack* Ps){
    free(Ps);
}

/* 3.1 栈是否为空
 * 空返回True
 * */
int IsEmpty_stack(Stack* Ps){
    return (Ps->top == -1);
}

/* 3.2 栈是否满
 * 满返回True
 * */
int IsFull_stack(Stack* Ps){
    return (Ps->top == STACK_MAXSIZE - 1);
}

/* 4.1 进栈
 * 栈溢出 --> False
 * */
int Push_stack(Stack* Ps, ElemType data){
    if (IsFull_stack(Ps))
        return False;
    Ps->top++;
    Ps->data[Ps->top] = data;
    return True;
}

/* 4.2 出栈
 * 栈下溢出 --> False
 * */
int Pop_stack(Stack* Ps, ElemType* e){
    if (IsEmpty_stack(Ps))
        return False;
    *e = Ps->data[Ps->top];
    Ps->top--;
    return True;
}

/* 5. 取栈顶元素 */
int GetTop_stack(Stack* Ps, ElemType* e){
    if (IsEmpty_stack(Ps))
        return False;
    *e = Ps->data[Ps->top];
    return True;
}

/* 打印栈 */
void DispStack(Stack* Ps){
    printf("栈指针：top = %d\n", Ps->top);
    if (IsEmpty_stack(Ps))
        return;
    int i = Ps->top;
    while(i >= 0){
        printf("(%d): %c\n", i, Ps->data[i]);
        i--;
    }
}


/* ------------------------------- 栈的应用 --------------------------------- */

/* 1. 判断字符串的对称性
 * 用顺序栈天然解决
 * */
int IsSymmetry(char* arr){
    int i = 0;
    char ch;
    // 入栈
    Stack* stack = InitStack();
    while(True){
        ch = arr[i];
        if (ch == '\0')
            break;
        Push_stack(stack, ch);
        i++;
    }
    // 出栈 对比
    int flag = True;
    i = 0;
    while (!IsEmpty_stack(stack)){
        Pop_stack(stack, &ch);
        if (ch != arr[i]){
            flag = False;
            break;
        }
        i++;
    }

    return flag;
}

/* 2. 简单的表达式求值
 *  这里限定的简单表达式求值问题是：
 *    用户输入一个包含 +，-，*，/，() 正整数的合法算术表达式
 *    程序计算该表达式的运算结果。
 *  这里的算法详见：/01-stack-queue/readme.md 文件阐述
 * */

/* 2.1 中缀表达式 --> 后缀表达式 */
//TODO

/* 2.2 后缀表达式求值 */
//TODO

/* 3. 走迷宫
 *  设置一个迷宫数组mg，其中每个元素表示一个方块的状态，为0时表示对应方块是通道，为1时表示对应方块不可走。
 *  这里的算法详见：/01-stack-queue/readme.md 文件阐述
 * */
// TODO





