#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define maxsize 20
#define INF 32767

typedef struct {
	int edges[maxsize][maxsize]; 		//邻接矩阵，存放权值，为INF表示没有路径到达 
	char nodename[maxsize][maxsize];		//存放顶点信息 
	int v, e;					//顶点数，边数 
}graph;						//图的结构体 



void GraphCreat(graph* g, int edge[][7]);
void PrintfWeight(graph* g);
void BFS(graph* g);
int main() {
	graph g;
	g.v = 7, g.e = 10;
	int edge[7][7] ={{0,1,1,0,0,0,0},			//测试数据 
					 {1,0,0,1,1,0,0},			//以零表示无路径到达 
					 {1,0,0,1,0,0,1},
					 {0,1,1,0,1,1,1},
					 {1,0,0,1,0,1,0},
					 {0,0,0,1,1,0,0},
					 {0,0,1,1,0,0,0}};

	GraphCreat(&g, edge);
	PrintfWeight(&g);
	BFS(&g);
	return 0;
}


void GraphCreat(graph* g, int edge[][7]) {
	int i, j;
	for (i = 1; i <= g->v; i++) {
		printf("请输入顶点编号\n");
		scanf("%s", g->nodename[i]);
		for (j = 1; j <= g->v; j++) {			//零号不用，习惯。不懂  
			g->edges[i][j] = edge[i - 1][j - 1];
		}		//注意数组是从零开始的 
	}
}


void PrintfWeight(graph* g) {			//检查输入数据是否正确可用 
	int i, j;
	for (i = 1; i <= g->v; i++) {		//不大于顶点数，同上 
		for (j = 1; j <= g->v; j++) {
			if (i != j) {
				printf("%s->%s的权值:%-7d", g->nodename[i], g->nodename[j], g->edges[i][j]);
				if (j == g->v) printf("\n");
			}			//成方阵显示 
		}
	}
}


void BFS(graph* g) 
{
	int i, j, k, n;
	int visit[maxsize];
	int d[maxsize], path[maxsize];			//记录路径长度；记录节点前驱 
	int queue[maxsize], front = 0, rear = 0;
	for (i = 1; i <= g->v; i++) {
		d[i] = INF;						//初始为无穷大 
		visit[i] = false;				//标记还没有访问 
		path[i] = -1;					//还没有前驱节点 
}
	printf("请输入起始点编号\n");
	scanf("%d", &n);					
	visit[n] = true;						//加入n节点 
	d[n] = 0;								//起始点路径长度为零 
	path[n] = -1; 							//无前驱 
	queue[rear] = n;						//n节点入队 
	rear = (rear + 1) % maxsize;
	printf("广度优先搜索次序：");
	while (front != rear) {						//队列不空则进行 
		n = queue[front];						//出队，然后访问； 
		front = (front + 1) % maxsize;
		printf(" %s", g->nodename[n]);
		for (k = 1; k <= g->v; k++) {
			if (g->edges[n][k] != 0 && visit[k] != true) {	//找到其临近点且还未访问 			
				queue[rear] = k;
				rear = (rear + 1) % maxsize;		//找到的临近点入队；（会是下一个n的值） 
				visit[k] = true;					//标记此节点已经访问（找到） 
				path[k] = n;						//标记 
				d[k] = d[n] + 1;					//路径长度加一 
			}						
		}
	}
	printf("\n");
	for (j = 1; j<= g->v; j++) {
		if (path[j] != -1) {						//节点一无前驱；从二开始 
			printf("%s的前驱节点%s  路径长度%d\n", g->nodename[j], g->nodename[path[j]], d[j]);
		}
	}
}


