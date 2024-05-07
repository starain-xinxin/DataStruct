/*
 * Created by mac on 2024/5/7.
 * OJ2 子树移动
 * */

#include<stdio.h>

#define MaxSon 60
#define MaxNode 60
#define DEBUG 1

typedef struct{
    int son[MaxSon];
    int num_of_son;
}Node;

typedef struct{
    int jump;
    int index[MaxSon];
}Point;

typedef struct {
    Point src;
    Point dst;
    int rank;
}Op;

void clean(int* son, int num){
    int arr[MaxSon] = {0};
    for(int i=0; i<MaxSon; i++){
        arr[i] = son[i];
    }
    // 按次序
    int idx = 0;
    for(int i=0; i<MaxSon; i++){
        if(arr[i]){
            son[idx] = arr[i];
            idx++;
        }
    }
}

void son_put(int* son, int rank, int src_idx){
    for(int i=MaxSon-2; i>=rank; i--){
        son[i+1] = son[i];
    }
    son[rank] = src_idx;
}

int main(){
    int N,M;
    Node tree[MaxNode];

    // 初始化tree
    for(int nn=0; nn<MaxNode; nn++){
        tree[nn].num_of_son = 0;
        for(int nnn=0; nnn<MaxSon; nnn++){
            tree[nn].son[nnn] = 0;
        }
    }

    scanf("%d %d", &N, &M);

    int check[MaxNode] = {0};   // 用于check根节点
    for(int i=1; i<=N; i++){
        scanf("%d",&(tree[i].num_of_son));
        for(int k=0; k<tree[i].num_of_son; k++){
            int a;
            scanf("%d", &a);
            check[a] = 1;
            tree[i].son[k] = a;
        }
    }

    // 找出根节点
    int root;
    for(root=1; root<=N; root++){
        if(!check[root]) break;
    }

    // 进行操作
    for(int ops=0; ops<M; ops++){   // M次操作
        // init一个操作,然后接受输入
        Op op;
        int src_jp, dst_jp;

        scanf("%d", &src_jp);
        op.src.jump = src_jp;
        for(int i=0; i<src_jp; i++){
            int idx;
            scanf("%d", &idx);
            op.src.index[i] = idx;
        }

        scanf("%d", &dst_jp);
        op.dst.jump = dst_jp;
        for(int i=0; i<dst_jp; i++){
            int idx;
            scanf("%d", &idx);
            op.dst.index[i] = idx;
        }
        scanf("%d", &(op.rank));

        // 找到src_index, dst_index
        int src_idx, dst_idx, src_father, dst_father;
        int toward = root;
        int father = root;
        int j1,j2;
        for(j1=0; j1<op.src.jump; j1++){
            if (op.src.index[j1] > tree[toward].num_of_son) {j1;break;}
            father = toward;
            toward = tree[toward].son[op.src.index[j1]];
        }
        j1--;
        src_idx = toward;           // 范例：5
        src_father = father;        // 3

        toward = root;
        for(j2=0; j2<op.dst.jump; j2++){
            if (op.dst.index[j2] > tree[toward].num_of_son) {j2; break;}
            father = toward;
            toward = tree[toward].son[op.dst.index[j2]];
        }
        j2--;
        dst_idx = toward;           // 范例：7
        dst_father = father;        // 2

        // 移动
        //在src的父亲中删去
        tree[src_father].num_of_son--;
        tree[src_father].son[op.src.index[j1]] = 0;
        // 重新整理
        clean(tree[src_father].son, tree[src_father].num_of_son);
        // 添加src_idx进dst[rank]
        tree[dst_idx].num_of_son++;
//        while(1){
//            if(tree[dst_idx].son[op.rank] != 0) op.rank++;
//            else break;
//        }
        son_put(tree[dst_idx].son, op.rank, src_idx);
//        tree[dst_idx].son[op.rank] = src_idx;

    }

    /* 输出 */

    if(DEBUG) printf("--------------\n");
    // 初始化一个队列
    int stack[MaxNode] = {0};
    int top = -1;
    int tail = -1;
    // 将头节点放入
    tail++; // 进队先tail++
    stack[tail] = root;
    top++;  // 标识下一次操作的idx
    // 层次遍历
    int ppp;
    while(top<=tail){
        // 先出队
        ppp = stack[top];
        top++;
        // 输出打印
        printf("%d\n", ppp);
        // 然后进队
        int count = 0;  // 记录有多少孩子被遍历
        int lll = 0;    // 遍历孩子的idx
        while(count < tree[ppp].num_of_son){
            if (tree[ppp].son[lll] != 0){   // 找到孩子了
                count++;
                // 孩子进队
                tail++;
                stack[tail] = tree[ppp].son[lll];
            }
            lll++;
        }
    }


}




