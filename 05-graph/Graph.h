/*
 * Created by mac on 2024/6/24.
 * 图
*/

#include <stdio.h>
#include <stdlib.h>
#include "BFS_queue.h"

#define MAXV 100
#define MAXE 1000
#define InfoType int
#define INF 9999


/* ----------------- 图的存储结构 -----------------------  */

/* 1.邻接矩阵 */
typedef struct {
    int no;         // 顶点的编号
    InfoType info;  // 顶点的信息
} VertexType;

typedef struct {
    int edges[MAXV][MAXV];      // 邻接矩阵
    int n, e;                   // 顶点数和边数
    VertexType Vexes[MAXV];     // 顶点的编号与信息
} MatGraph;


/* 2. 邻接表 */
typedef struct _ArcNode {            // 边节点
    int adj_vex;        // 边另一个节点编号
    struct _ArcNode* NextArc;   // 下一个边
    InfoType weight;            // 边权重
} ArcNode;

typedef struct _VexNode {
    InfoType info;          // 顶点信息
    ArcNode* first_arc;     // 首个边
} VexNode;

typedef struct {
    VexNode AdjList[MAXV];  // 邻接表
    int n, e;               // 顶点数和边数
} AdjGraph;


/* ----------------- 图的基本操作 -----------------------  */

/* 1.1 根据矩阵创建邻接表 */
AdjGraph* CreateAdj(int A[MAXV][MAXV], int n){
    int i, j;
    int num_e = 0;

    AdjGraph* G = (AdjGraph*) malloc(sizeof(AdjGraph));
    // 1. 邻接表指针域赋初值
    for(i=0; i<n; i++)
        G->AdjList[i].first_arc = NULL;
    // 2. 遍历矩阵，有边的头插法插入
    for (i=0; i<n; i++){
        for (j=n-1; j>=0; j--){
            if (A[i][j] && A[i][j] != INF) {
                ArcNode *p_edge = (ArcNode *) malloc(sizeof(ArcNode));
                p_edge->weight = A[i][j];       // 权重
                p_edge->adj_vex = j;            // 另一个节点
                // 插入链表
                p_edge->NextArc = G->AdjList[i].first_arc;
                G->AdjList[i].first_arc = p_edge;
                num_e++;
            }
        }
    }
    // 3. 邻接表的节点，边个数
    G->n = n;
    G->e = num_e / 2;

    return G;
}

/* 1.2 根据矩阵创建邻接矩阵 */
MatGraph* CreateMat(int A[MAXV][MAXV], int n){
    MatGraph *G = (MatGraph*) malloc(sizeof(MatGraph));
    G->n = n;
    int e = 0;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            G->edges[i][j] = A[i][j];
            if (A[i][j] && A[i][j] != INF)
                e++;
        }
    }
    G->e = e / 2;
    return G;
}

/* 2. 输出图
 * 按照n个链表依次输出
 * */
void DispAdj(AdjGraph* G){
    int list_num = G->n;    // n个链表
    ArcNode *p_edge;        //

    for(int i=0; i<list_num; i++){
        printf("节点【%d】: ", i);
        p_edge = G->AdjList[i].first_arc;
        while(p_edge){
            printf("%d[%d]  ", p_edge->adj_vex, p_edge->weight);
            p_edge = p_edge->NextArc;
        }
        printf("^\n");
    }
}

void DispMat(MatGraph* G){
    int n = G->n;
    for (int i=0; i<n; i++){
        printf("节点【%d】: ", i);
        for (int j=0; j<n; j++){
            if (G->edges[i][j] && G->edges[i][j] != INF){
                printf("%d[%d]  ", j, G->edges[i][j]);
            }
        }
        printf("^\n");
    }
}

/* 3. 销毁图 */
void DestroyAdj(AdjGraph* G){
    int n = G->n;
    int i;
    // 遍历每个链表
    for (i=0; i<n; i++){
        ArcNode *p_del = G->AdjList[i].first_arc;
        ArcNode *p_tmp;
        while(p_del){
            p_tmp = p_del->NextArc;
            free(p_del);
            p_del = p_tmp;
        }
    }
    // 删除图
    free(G);
}

/* 4. DFS--深度优先搜索
 * 这里使用 DFS函数 包装 dfs函数，以避免使用全局变量
 * */
void dfs(AdjGraph* G, int v, int DFS_visited[MAXV]){
    DFS_visited[v] = 1;     // 记录访问节点

    // 这一段代表对于遍历到的点做操作
    printf("%d  ", v);
    G->AdjList[v].info = v;

    // 递归深度优先
    ArcNode *p_edge = G->AdjList[v].first_arc;
    while (p_edge){
        // 如果节点没遍历过
        if (DFS_visited[p_edge->adj_vex] == 0){
            int next_node = p_edge->adj_vex;
            dfs(G, next_node, DFS_visited);
        }
        // 无论有没有遍历过
        p_edge = p_edge->NextArc;
    }
}

void DFS(AdjGraph* G, int v){
    printf("深度优先遍历: ");
    int DFS_visited[MAXV] = {0};
    dfs(G, v, DFS_visited);
}

/* 5. BFS--广度优先搜索
 * */



void BFS(AdjGraph* G, int v){
    printf("广度优先遍历: ");

    // 顶点标记数组，初始化
    int BFS_visited[MAXV] = {0};
    BFS_visited[v] = 1;
    printf("%d:[%d]  ", v, G->AdjList[v].info);

    // 初始化一个队列
    CrQueue* queue = InitQueue_cr();
    Push_CrQueue(queue, v);

    // 循环
    while (!IsEmpty_cq(queue)){
        int vex_index;
        Pop_CrQueue(queue, &vex_index);
        ArcNode *p_edge = G->AdjList[vex_index].first_arc;
        // 对于当前顶点的链表进行遍历
        while(p_edge){
            int next_vex_index = p_edge->adj_vex;
            if (BFS_visited[next_vex_index] == 0){
                printf("%d:[%d]  ", next_vex_index, G->AdjList[next_vex_index].info);
                // 已访问标记，入队
                BFS_visited[next_vex_index] = 1;
                Push_CrQueue(queue, next_vex_index);
            }
            p_edge = p_edge->NextArc;
        }
    }
    printf("\n");
}

/* ----------------- 图的常见算法 -----------------------  */

/* 1. 寻找图中的一条简单路径
 * Path存路径，d指示路径长度
 * 初始调用需要传入d=-1
 * */
void _FindPath(AdjGraph* G, int a, int b, int Path[MAXV], int d, int visited[MAXV]){
    visited[a] = 1;
    d++; Path[d] = a;

    // 递归出口
    if (a == b){
        printf("简单路径为：");
        for (int i=0; i<=d; i++)
            printf("%d  ",Path[i]);
        printf("\n");
        return;
    }

    // DFS递归
    ArcNode *p_edge = G->AdjList[a].first_arc;
    while(p_edge){
        int next_vex = p_edge->adj_vex;
        if (visited[next_vex] == 0)
            _FindPath(G, next_vex, b, Path, d, visited);
        p_edge = p_edge->NextArc;
    }
}

void FindPath(AdjGraph* G, int a, int b){
    int Path[MAXV] = {0}, d = -1, visited[MAXV] = {0};
    _FindPath(G, a, b, Path, d, visited);
}

/* 2. 寻找所有图中的简单路径
 * Path存路径，d指示路径长度
 * 初始调用需要传入d=-1
 * */
void _FindAllPath(AdjGraph* G, int a, int b, int Path[MAXV], int d, int visited[MAXV]){
    visited[a] = 1;
    d++; Path[d] = a;

    // 递归出口
    if (a == b){
        printf("简单路径为：");
        for (int i=0; i<=d; i++)
            printf("%d  ",Path[i]);
        printf("\n");
        visited[a] = 0;
        return;
    }

    // DFS递归
    ArcNode *p_edge = G->AdjList[a].first_arc;
    while(p_edge){
        int next_vex = p_edge->adj_vex;
        if (visited[next_vex] == 0)
            _FindAllPath(G, next_vex, b, Path, d, visited);
        p_edge = p_edge->NextArc;
    }

    // 回溯，让现在这点变得可用
    visited[a] = 0;
}

void FindAllPath(AdjGraph* G, int a, int b){
    int Path[MAXV] = {0}, d = -1, visited[MAXV] = {0};
    _FindAllPath(G, a, b, Path, d, visited);
}

/* 3. 寻找所有图中的经过某点的环路 TODO
 * Path存路径，d指示路径长度
 * 初始调用需要传入d=-1
 * */
void _FindAllPath_cir(AdjGraph* G, int a, int b, int Path[MAXV], int d, int visited[MAXV]){
    visited[a] = 1;
    d++; Path[d] = a;

    // DFS递归
    ArcNode *p_edge = G->AdjList[a].first_arc;
    while(p_edge){
        int next_vex = p_edge->adj_vex;
        if (next_vex == b){
            printf("环路为：");
            for (int i=0; i<=d; i++)
                printf("%d  ",Path[i]);
            printf("%d \n ", b);
        }
        if (visited[next_vex] == 0)
            _FindAllPath_cir(G, next_vex, b, Path, d, visited);
        p_edge = p_edge->NextArc;
    }

    // 回溯，让现在这点变得可用
    visited[a] = 0;
}

void FindAllPath_cir(AdjGraph* G, int a){
    int Path[MAXV] = {0}, d = -1, visited[MAXV] = {0};
    _FindAllPath_cir(G, a, a, Path, d, visited);
}

/* 4.1 最小生成树--kruskal算法
 * 以边的视角
 * */
typedef struct {
    int u;
    int v;
    int weight;
} Edge;

void BubbleSort(Edge R[], int n){
    int i, j; Edge temp;
    for (i=0;i<n-1;i++){
        for (j=n-1;j>i;j--)
            if (R[j].weight < R[j-1].weight){
                temp=R[j];
                R[j]=R[j-1];
                R[j-1]=temp;
            }
    }
}

void Kruskal(MatGraph* G){
    printf("\n最小生成树--kruskal：\n");
    int V_set[MAXV];    // 并查集，相当于对每个点分类，以此避免成环
    // 并查集初始化
    int n = G->n;
    for (int i=0; i<n; i++){
        V_set[i] = i;
    }

    Edge E[MAXE];       // 边列表
    // 建立边列表（数组）
    int k = 0;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (G->edges[i][j] && G->edges[i][j] != INF){
                E[k].u = i; E[k].v = j; E[k].weight = G->edges[i][j];
                k++;
            }
        }
    }
    // 边列表排序
    BubbleSort(E, 2 * G->e);    // 这里用两倍e TODO:可以改进

    // 选边
    k = 1;      // 表示当前构造的是第几条边
    int j = 0;  // 遍历边的集合
    while (k < n){      // 选择的边小于点数时
        int u1 = E[j].u;    int v1 = E[j].v;
        int sn1 = V_set[u1];    int sn2 = V_set[v1];
        if (sn1 != sn2){
            // 输出生成树的边
            printf(" (%d，%d):%d\n", u1, v1, E[j].weight);
            k++;
            // 并查集更新
            for (int i=0; i<n; i++){
                if (V_set[i] == sn2)
                    V_set[i] = sn1;
            }
        }
        j++;
    }
};

/* 4.2 最小生成树--Prim算法
 * 以点的视角
 * */
void _Prim(MatGraph* G, int v){
    printf("\n最小生成树--Prim：\n");
    int LowList[MAXV];      // 记录与“已选集”的距离，为 0 代表已经在已选集中
    int CloseList[MAXV];    // 记录LowList距离是这一点与已选集的哪一点相连得到的
    // 初始化两个List
    for (int i=0; i<G->n; i++){
        LowList[i] = G->edges[v][i];
        CloseList[i] = v;
    }
    // 选点加入
    for (int i=1; i < G->n; i++) {
        printf("low-list: ");
        for (int m=0; m<G->n; m++){
            printf("%d ", LowList[m]);
        }
        printf("\t");
        // 挑选距离最近的点
        int min = INF, add_index;
        for (int j=0; j<G->n; j++){
            if (LowList[j] && LowList[j] < min){
                min = LowList[j];
                add_index = j;
            }
        }
        // 把选择的点置0
        LowList[add_index] = 0;
        // 输出
        printf("(%d, %d), weight:%d\n", CloseList[add_index], add_index, min);
        // 更新
        for (int m=0; m<G->n; m++){
            if (LowList[m] && G->edges[add_index][m] < LowList[m]){
                LowList[m] = G->edges[add_index][m];
                CloseList[m] = add_index;
            }
        }
    }
}

void Prim(MatGraph* G){
    _Prim(G, 0);
}

/* 5.1 狄杰斯特拉算法
 * 单源最短路径
 * 只允许权值>=0的权值出现
 * */
void Dijkstra(MatGraph* G, int v){
    int dist[MAXV];     // 距离数组
    int path[MAXV];     // 路径
    int IsIn[MAXV];     // 是否在“已选集”中
    int n = G->n;
    // 初始化三个数组
    for (int i=0; i<n; i++){
        dist[i] = G->edges[v][i];           // 有边 / 无边为INF / 自己到自己为0
        IsIn[i] = i == v ? True : False;
        path[i] = v;
    }
    // 循环n-1次，处理剩余的点
    for (int i=0; i<n-1; i++){
        // 找到dist中最小的点
        int min_dst = INF;  int new_idx;
        for (int j=0; j<n; j++){
            if (!IsIn[j] && dist[j] <= min_dst){
                min_dst = dist[j];
                new_idx = j;
            }
        }
        // 把最小的点加入集合
        IsIn[new_idx] = True;
        // 更新dist与path
        for (int j=0; j<n; j++){
            if (!IsIn[j]) {     // 处理非集合的点
                if (dist[new_idx]+G->edges[new_idx][j] < dist[j]){
                    dist[j] = dist[new_idx]+G->edges[new_idx][j];
                    path[j] = new_idx;
                }
            }
        }
    }
    // 输出最短路径
    printf("\nDijkstra--最短路径距离：\ndist");
    for (int i=0; i<n; i++){
        printf(" (%d) %d ", i, dist[i]);
    }
    printf("\nPath");
    for (int i=0; i<n; i++){
        printf(" (%d) %d ", i, path[i]);
    }
}

/* 5.2 Bellman-Ford算法
 * 解决负数权重的图
 * 存在负数环，则返回false
 * */
void BellmanFord(MatGraph* G, int v){
    int dist[MAXV];     // 距离数组
    int path[MAXV];     // 路径
    int n = G->n;
    // 初始化
    for (int i=0; i<n; i++){
        if (i == v)
            dist[i] = 0;
        else
            dist[i] = INF;
        path[i] = -1;
    }
    // 进行n-1遍历边
    for (int i=1; i<n; i++) {
        // 双循环遍历边
        for (int j=0; j<n; j++){
            for (int k=0; k<n; k++){
                if (dist[j] + G->edges[j][k] < dist[k]){
                    dist[k] = dist[j] + G->edges[j][k];
                    path[k] = j;
                }
            }
        }
    }
    // 再遍历一次边，看是否存在负数环
    int flag = False;
    for (int j=0; j<n; j++){
        for (int k=0; k<n; k++){
            if (dist[j] + G->edges[j][k] < dist[k]){
                dist[k] = dist[j] + G->edges[j][k];
                path[k] = j;
                flag = True;
            }
        }
    }
    // 判断，输出
    if (flag)
        printf("\n无最短路径\n");
    else{
        printf("\nbellman--最短路径距离：\ndist");
        for (int i=0; i<n; i++){
            printf(" (%d) %d ", i, dist[i]);
        }
        printf("\nPath");
        for (int i=0; i<n; i++){
            printf(" (%d) %d ", i, path[i]);
        }
    }
}

/* 5.3 Floyd算法
 * 多源最短路径问题
 * 权值大于0
 * */
void Floyd(MatGraph* G){
    int A[MAXV][MAXV];
    int Path[MAXV][MAXV];
    int n = G->n;
    // 初始化
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            A[i][j] = G->edges[i][j];
            if (i == j || G->edges[i][j] == INF)    // 自己到自己 or i -> j没有边
                Path[i][j] = -1;
            else
                Path[i][j] = i;
        }
    }
    // 三重循环
    for (int k=0; k<n; k++){            // 遍历中继节点
        for (int i=0; i<n; i++) {       // 起点
            for (int j=0; j<n; j++){    // 终点
                if (A[i][k] + A[k][j] < A[i][j]){
                    A[i][j] = A[i][k] + A[k][j];
                    Path[i][j] = Path[k][j];
                }
            }
        }
    }
    // 输出
    printf("\nFloyd--最短路径距离：\n");
    for (int m=0; m<n; m++){
        printf("源点【%d】:",m);
        printf("\ndist");
        for (int i=0; i<n; i++){
            printf(" (%d) %d ", i, A[m][i]);
        }
        printf("\nPath");
        for (int i=0; i<n; i++){
            printf(" (%d) %d ", i, Path[m][i]);
        }
        printf("\n");
    }
}






