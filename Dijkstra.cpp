#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE  1
#define FALSE 0
#define MAX_SIZE 10
#define INFINITY 999

typedef int PathMatrix[MAX_SIZE][MAX_SIZE];
typedef int ShortPathTable[MAX_SIZE];

typedef struct {
	int arcs[MAX_SIZE][MAX_SIZE]; // 邻接矩阵 
	int vexnum;                   // 顶点个数 
} MGraph;

// 创建邻接矩阵的图
void CreateMGraph(MGraph &G) {
    printf("请输入节点个数："); 
    scanf("%d", &G.vexnum);
    int x; 
    printf("请输入G的邻接矩阵(0表示不连通):\n");
    for (int i = 0; i < G.vexnum; ++i) {
		for (int j = 0; j < G.vexnum; ++j) {
			scanf("%d", &x);
			if (x == 0) G.arcs[i][j] = INFINITY;
			else G.arcs[i][j] = x;
    	}
    }
}

/**
 * @brief Dijkstra 求单源最短路径
 * 
 * @param G  邻接矩阵
 * @param v0 出发顶点
 * @param P  路径矩阵
 * @param D  最短路径
 */
void ShortestPath_DIJ(MGraph G, int v0, PathMatrix &P, ShortPathTable &D) {
	int v, w, i, min = 0;
	int final[MAX_SIZE];
	
	for (v = 0; v < G.vexnum; ++v) {
		final[v] = FALSE;
		D[v] = G.arcs[v0][v];
		// 设空路径
		for (w = 0; w < G.vexnum; ++w) P[v][w] = FALSE; 
		if (D[v] < INFINITY) {
			P[v][v0] = TRUE;
			P[v][v] = TRUE;
		} 
	}
	
	D[v0] = 0;
	final[v0] = TRUE; // 初始化,v0的顶点属于S集
	
	// 开始主循环,每次求得v0到某个顶点的最短路径,并加v到S集
	for (i = 1; i < G.vexnum; ++i) {
		min = INFINITY;
		for (w = 0; w < G.vexnum; ++w) {
			if (!final[w]) { // w顶点在V-S中 
				if (D[w] < min) { // w顶点离顶点更近 
					v = w;
					min = D[w];
				}
			}
		}
		final[v] = TRUE;
		for (w = 0; w < G.vexnum; ++w) {
			if (!final[w] && (min + G.arcs[v][w] < D[w])) { 
				// 修改D[w]和P[w],w ∈ V-S 
				D[w] = min + G.arcs[v][w];
				// 把一行整体赋值
				memcpy(P[w], P[v], sizeof(P[w][0]) * G.vexnum);
				P[w][w] = TRUE; 
			}
		}
	} 
} 

/**
 * @brief 打印路径矩阵
 * 
 * @param P 路径矩阵
 * @param G 邻接矩阵 
 */
void ShowPathMatrix(PathMatrix P, MGraph G) {
	puts("PathTable");
    for (int i = 0; i < G.vexnum; ++i) {
    	printf("  ");
    	for (int j = 0; j < G.vexnum; ++j) {
    		printf("%d ", P[i][j]);
		}
		putchar('\n');
	}
}

/**
 * @brief 打印最短路径表
 
 * @param D 最短路径表
 * @param G 邻接矩阵 MGraph 
 */
void ShowShortPathTable(ShortPathTable D, MGraph G) {
	puts("dist");
	for (int i = 0; i < G.vexnum; ++i) {
    	printf("  [%d] = (int) %d\n", i, D[i]);
	}
}

/*
	Input:
	5
	0   10  0   30  100
	0   0   50  0   0
	0   0   0   0   10
	0   0   20  0   60
	0   0   0   0   0
*/

int main() {
    
    MGraph G;         // 邻接矩阵
    int v0 = 0;       // 出发顶点
    PathMatrix P;     // 路径矩阵
    ShortPathTable D; // 最短路径表
    
	// 创建邻接矩阵
    CreateMGraph(G);  

	// Dijkstra 
    ShortestPath_DIJ(G, v0, P, D) ;

	// 打印最短路径
	ShowShortPathTable(D, G); 
	
    return 0;
} 

