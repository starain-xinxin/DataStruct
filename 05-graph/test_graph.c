/*
* Created by mac on 2024/6/24.
* 图的测试代码
*/

#include "Graph.h"

int main(){
//    int A[MAXV][MAXV] = {
//            {INF, 3, 1, 8},
//            {3, INF, 1, 4},
//            {1, 1, INF, 0},
//            {8, 4, 0, INF}
//    };
    int A[MAXV][MAXV] = {
            {0, 3, 1, 8},
            {3, 0, 1, 4},
            {1, 1, 0, INF},
            {8, 4, INF, 0}
    };
    AdjGraph *G = CreateAdj(A, 4);
    DispAdj(G);
    DFS(G, 0);
    BFS(G, 0);

    // 1. 找一条简单路径
    FindPath(G, 0, 3);

    // 2. 找所有简单路径
    printf("\n");
    FindAllPath(G, 0, 3);

    // 3. 找所有经过0点的环路
    printf("\n");
    FindAllPath_cir(G, 0);

    // 4. 找最小生成树
    MatGraph *H = CreateMat(A, 4);
    DispMat(H);
    printf("边的数量：%d", H->e);
    Kruskal(H);
    Prim(H);

    Dijkstra(H, 0);

    BellmanFord(H, 0);

    Floyd(H);


    DestroyAdj(G);
}