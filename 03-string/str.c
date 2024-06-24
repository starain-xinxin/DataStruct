/*
 * Created by mac on 2024/6/24.
 * 串
*/

#include <stdio.h>

#define True 1
#define False 0
#define MAXSIZE 100

/* 1. 串长度 */
int GetLen(char* arr){
    int len = 0;
    char ch = arr[len];
    while(ch != '\0'){
        len++;
        ch = arr[len];
    }
    return len;
}

/* 2. 串匹配判断函数
 * 给出目标字符串，和匹配字符串的起点指针，判断是否匹配
 * 这里并不关心两个串的长度是否一致
 * */
int IsEqual(char* src, char* dst){
    int src_len = GetLen(src);
    int dst_len = GetLen(dst);
    if (dst_len < src_len)
        return False;
    int i = 0;
    for(; i < src_len; i++){
        if (src[i] != dst[i])
            return False;
    }
    return True;
}

/* 3. 字符串匹配函数
 * 暴力解法
 * */
int BruteForce(char* src, char* dst){
    int dst_len = GetLen(dst);
    int i;
    for (i = 0; i < dst_len; i++){
        if (IsEqual(src, dst + i))
            return True;
    }
    return False;
}

/* 4.1 KMP--next数组生成 */
void GetNext(char* arr, int* next){
    int i = 0;      // 计算next值时，先指向前一个元素，如果分支1对，i++后指向写入元素位置
    int k = -1;      // 这个用于求解时的跳转着-->找与前一个元素相等的元素，直到找到或者为-1（代表没有）
    next[0] = -1;   // 首个next数组的值一定为-1
    int len = GetLen(arr);
    while(i < len - 1){
        if (k==-1 || arr[i]==arr[k]){
            i++;        // 如果分支1对，i++后指向写入元素位置
            k++;        // 找到的最大的与前一个元素相等的位置，++表示填入next的值
            next[i] = k;    // 写值
        }
        else
            k = next[k];    // 不等就跳转
    }
}

/* 4.2 KMP算法
 * 匹配返回匹配的索引
 * 不匹配返回-1
 * */
int KMPIndex(char* src, char* dst){
    int next[MAXSIZE];
    int i = 0;      // 目标字符串的指针（长字符串）
    int j = 0;      // 匹配字符串的指针（短字符串）
    GetNext(src, next);

    int SLen = GetLen(src);
    int DLen = GetLen(dst);

    while (i < DLen && j < SLen){
        if (j==-1 || src[j]==dst[i]){   //要么子串回溯到-1了，要么匹配上了
            i++; j++;
        }
        else                            // 没匹配上，回溯子串指针
            j = next[j];
    }

    if (j == SLen)
        return i - SLen;
    else
        return -1;

}

int main(){
    char src[100] = "abcdabd";
    char dst[100] = "bbc abcdab abcdabcdabde";

    // 1. 暴力解法
    printf("%d\n", BruteForce(src, dst));

    // 2. KMP
    printf("%d\n", KMPIndex(src, dst));

}
