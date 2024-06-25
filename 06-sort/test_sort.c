/*
 * Created by mac on 2024/6/25.
 * 排序测试代码
*/

#include "Sort.h"

int main(){
    // 准备待排列数据
    int arr[ListSize] = {7, 1, 5, 2, 9, 10, 6, 8, 3, 4,10,3};
    RecType list[ListSize];
    for (int i=0; i<ListSize; i++){
        list[i].key = arr[i];
    }
    Print(list);

    // 1. 直接插入
    InsertSort(list, ListSize);
    Print(list);

    // 2. 折半插入
    Gap
    for (int i=0; i<ListSize; i++){
        list[i].key = arr[i];
    }
    Print(list);

    BinInsertSort(list, ListSize);
    Print(list);

    // 3. 希尔排序
    Gap
    for (int i=0; i<ListSize; i++){
        list[i].key = arr[i];
    }
    Print(list);

    ShellSort(list, ListSize);
    Print(list);

    // 4. 冒泡排序
    Gap
    for (int i=0; i<ListSize; i++){
        list[i].key = arr[i];
    }
    Print(list);

    BubbleSort(list, ListSize);
    Print(list);

    // 5. 快速排序
    Gap
    for (int i=0; i<ListSize; i++){
        list[i].key = arr[i];
    }
    Print(list);

    QuickSort(list, ListSize);
    Print(list);

    // 6. 选择排序
    Gap
    for (int i=0; i<ListSize; i++){
        list[i].key = arr[i];
    }
    Print(list);

    SelectSort(list, ListSize);
    Print(list);

    // 7. 堆排序
//    Gap
//    for (int i=0; i<ListSize; i++){
//        list[i].key = arr[i];
//    }
//    Print(list);
//
//    HeapSort(list, ListSize);
//    Print(list);

    // 8. 归并排序
    Gap Gap
    for (int i=0; i<ListSize; i++){
        printf("list[i] %d  arr[i] %d\n", list[i].key, arr[i]);
    }
    printf("\n%d\n",list[0]);
    for (int i=0; i<ListSize; i++){
        list[i].key = arr[i];
        printf("list[i] %d  arr[i] %d\n", list[i].key, arr[i]);
    }

    Print(list);

    MergeSort(list, ListSize);
    Print(list);
}




