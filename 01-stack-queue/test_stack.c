/*
 * Created by mac on 2024/6/23.
 * 栈测试代码
*/

#include "Stack.h"

#define DispLine printf("\n");

int main(){
    // 1.初始化栈
    Stack* stack1 = InitStack();

    // 2.入栈，出栈
    char data;
    Push_stack(stack1, 'a');
    Push_stack(stack1, 'b');
    Push_stack(stack1, 'c');
    Push_stack(stack1, 'b');
    Push_stack(stack1, 'd');
    Push_stack(stack1, 'f');
    Push_stack(stack1, 'e');
    DispStack(stack1);

    Pop_stack(stack1, &data);
    DispLine
    DispStack(stack1);

    // 3. 判断字符对称性
    char arr[10] = "abba";
    int flag = IsSymmetry(arr);
    DispLine
    printf("%d\n", flag);




}