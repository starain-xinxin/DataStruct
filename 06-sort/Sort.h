/*
 * Created by mac on 2024/6/25.
 * 排序
 * 均从小到大排序
*/

#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0
#define ListSize 12
#define Gap printf("\n");
#define MAXE 20		    //线性表中最多元素个数
#define MAXR 10		    //基数的最大取值
#define MAXD 8			//关键字位数的最大取值

/* 排序的抽象数据类型 */
typedef int KeyType;
typedef char InfoType;
typedef struct {
    KeyType key;
    InfoType data;
} RecType;

void Print(RecType R[]){
    printf("List：");
    for (int i=0; i<ListSize; i++){
        printf("%d ", R[i].key);
    }
    printf("\n");
}


/*--------------------------------- 插入排序 ------------------------------------*/

/* 1.1 直接插入排序 */
void InsertSort(RecType R[], int n){
    printf("直接插入排序: ");
    int i, j;
    for (i=1; i<n; i++){
        RecType tmp = R[i];
        j = i - 1;
        while (j >= 0 && tmp.key < R[j].key){
            R[j+1] = R[j];
            j--;
        }
        R[j+1] = tmp;
    }
}

/* 2. 折半插入排序 */
void BinInsertSort(RecType R[], int n){
    printf("折半插入排序: ");
    int i, j;
    int high, low, mid;

    for (i=1; i<n; i++) {
        if (R[i].key < R[i-1].key){     // 需要插入
            RecType tmp = R[i];
            // 二分查找
            low = 0; high = i - 1;
            while (low <= high){
                mid = (low + high) / 2;
                if (tmp.key < R[mid].key)
                    high = mid - 1;
                else
                    low = mid + 1;
            }
            // 记录后移
            for (j=i-1; j>=high+1; j--){
                R[j+1] = R[j];
            }
            // 插入R[i] 也就是 tmp
            R[high+1] = tmp;
        }
    }
}

/* 3. 希尔排序 */
void ShellSort(RecType R[], int n) {
    printf("希尔排序: ");
    int gap = n / 2;    // 同组间的元素间隔
    while (gap > 0){
        // 遍历每一个元素（0～gap-1）不用管
        for (int i=gap; i<n; i++){
            // 对组内元素插入排序
            RecType tmp = R[i];
            int j = i - gap;
            while (j>=0 && R[j].key > tmp.key){
                R[j+gap] = R[j];
                j = j - gap;
            }
            R[j+gap] = tmp;
        }
        // 减小增了，增多组数
        gap = gap / 2;
    }
}

/*--------------------------------- 交换排序 ------------------------------------*/

/* 1. 冒泡排序 */
void BubbleSort(RecType R[], int n){
    printf("冒泡排序: ");
    int iter = 1;
    while(iter <= n-1) {
        for (int i = 0; i <= n - 2; i++) {
            // 当前与后一个元素比较
            if (R[i + 1].key < R[i].key) {     // 需要交换
                RecType tmp = R[i];
                R[i] = R[i + 1];
                R[i + 1] = tmp;
            }
        }
        iter++;
    }
}

/* 2. 快速排序 */
void _QuickSort(RecType R[], int s, int t){
    int i = s, j = t;   // 用于划分的指针
    if(s<t){
        // 以基准划分
        RecType base = R[s];
        while(i != j){
            while(R[j].key >= base.key && j > i)
                j--;
            R[i] = R[j];
            while(R[i].key <= base.key && j > i)
                i++;
            R[j] = R[i];
        }
        // 把基准放进去
        R[i] = base;

        // 递归左右
        _QuickSort(R, s, i-1);
        _QuickSort(R, i+1, t);
    }
    else
        return;
}

void QuickSort(RecType R[], int n){
    printf("快速排序: ");
    _QuickSort(R, 0, n-1);
}

/*--------------------------------- 选择排序 ------------------------------------*/

/* 1. 选择排序 */
void SelectSort(RecType R[], int n){
    printf("选择排序: ");
    int i = 0;
    while (i < n-1){
        // 找最小值
        int min = R[i].key, min_index = i;
        for (int j=i; j<n; j++){
            if (R[j].key < min){
                min = R[j].key;
                min_index = j;
            }
        }
        // 交换i与min_index
        RecType tmp = R[i];
        R[i] = R[min_index];
        R[min_index] = tmp;
        // 迭代加一
        i++;
    }
}

/* 2. 堆排序 */
void back1(RecType R[], int n){
    for (int i = n-1; i >=0; i--){
        R[i+1] = R[i];
    }
}

void sift(RecType R[], int root, int n){
    int i = 2 * root;
    int j = i + 1;
    while(i <= n ){
        if (j <= n)
            if (R[i].key > R[j].key)
                i = j;
        if (R[root].key > R[i].key){
            RecType tmp = R[root];
            R[root] = R[i];
            R[i] = tmp;
            root = i;
            i = 2 * root;
            j = i + 1;
        }
        else
            break;
    }
}

void HeapSort(RecType R[], int n){
    printf("堆排序: ");
    // 建二叉树
    back1(R, n);
    // 建堆
    for (int i=n/2; i>=1; i--)
        sift(R, i, n);
    // 循环（输出+调整）
    for (int i=n; i>=1; i--){
        // 输出
        printf("%d ", R[1].key);
        // 叶子移到根
        R[1] = R[i];
        // 调整
        sift(R, 1, i-1);
    }
}

/* 1. 归并排序 */
void Merge(RecType R[], int low, int mid, int high)
{
    RecType *R1;
    int i = low, j = mid + 1, k = 0;
    // k是R1的下标，i、j分别为第1、2段的下标
    R1 = (RecType *)malloc((high - low + 1) * sizeof(RecType));
    while (i <= mid && j <= high)
    {
        if (R[i].key <= R[j].key)  	//将第1段中的记录放入R1中
        {
            R1[k] = R[i];
            i++;
            k++;
        }
        else    //将第2段中的记录放入R1中
        {
            R1[k] = R[j];
            j++;
            k++;
        }
    }
    while (i <= mid)         //将第1段余下部分复制到R1
    {
        R1[k] = R[i];
        i++;
        k++;
    }
    while (j <= high)        //将第2段余下部分复制到R1
    {
        R1[k] = R[j];
        j++;
        k++;
    }
    for (k = 0, i = low; i <= high; k++, i++) 	//将R1复制回R中
        R[i] = R1[k];
    free(R1);
}

void MergePass(RecType R[], int length, int n)
{
    int i;
    for (i = 0; i + 2 * length - 1 < n; i = i + 2 * length)   //归并length长的两相邻子表
        Merge(R, i, i + length - 1, i + 2 * length - 1);
    if (i + length - 1 < n) 		      //余下两个子表，后者长度小于length
        Merge(R, i, i + length - 1, n - 1);  //归并这两个子表
}

void MergeSort(RecType R[], int n)
{
    printf("归并排序: ");
    int length;
    for (length = 1; length < n; length = 2 * length)
        MergePass(R, length, n);
}

/* 1. 基数排序 */
typedef struct node
{    char data[MAXD];		//记录的关键字定义的字符串
    struct node *next;
}  RecType1;

void RadixSort(RecType1 *p, int r, int d){
    // 定义指针数组
    RecType1 *head[MAXR], *tail[MAXR], *t;
    for (int i=0; i<d; i++){
        // 初始化队列
        for (int j=0; j<r; j++){
            head[j] = NULL;
            tail[j] = NULL;
        }
        // 所有数据进入相应的队列
        while(p){
            int k = p->data[i] - '0';
            if (!head[k]){
                head[k] = p;
                tail[k] = p;
            }
            else{
                tail[k]->next = p;
                tail[k] = p;
            }
            p = p->next;
        }
        // 出队
        p = NULL;
        for (int i=0; i<r; i++){
            // 如果队列有元素
            if (head[i]){
                if (p){
                    t->next = head[i];
                    t = tail[i];
                }
                else{
                    p = head[i];
                    t = tail[i];
                }
            }
        }
        t->next = NULL;
    }
}