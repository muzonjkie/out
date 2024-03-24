<<<<<<< HEAD
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


void GraphCreat(graph*g,int edge[][7]);
void PrintfWeight(graph*g);
void DFS(graph* g);

int main(){
	graph g;
g.v=7,g.e=10;

int edge[7][7]= {{0,1,1,0,0,0,0},			//测试数据 
			  {1,0,0,1,1,0,0},			//以零表示无路径到达 
			  {1,0,0,1,0,0,1},
			  {0,1,1,0,1,1,1},
			  {1,0,0,1,0,1,0},
			  {0,0,0,1,1,0,0},
			  {0,0,1,1,0,0,0}};

	GraphCreat(&g,edge);
	PrintfWeight(&g);

	DFS(&g);
	return 0;
}


void GraphCreat(graph* g, int edge[7][7]) {
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


/*可实现拓扑排序；可实现简单路径（如求u->v，传入u，若能有path[v]！=-1，则存在）；
假如对有向图求是否有环，可以这么判断:如果这点之前访问过了，但是现在又有路径可以到达，则有环。
对无向图的话，暂时没有思路。 
*/
void DFS(graph*g){
	int path[maxsize];			//记录路径长度；记录节点前驱 
	int i,j,k,n;
	int w=0,array[maxsize];                 //存防逆拓扑排序 
	int visit[maxsize];	
	int stack[maxsize],top=-1;		
	for(i=1;i<=g->v;i++){
		visit[i]=false;					//标记还没有访问 
		path[i]=-1;	}					//还没有前驱节点 
	printf("请输入起点编号\n"); 
	scanf("%d",&n);
visit[n]=true;						//加入n节点 
path[n]=-1; 							//无前驱 
stack[++top]=n;
	printf("深度优先搜索次序：");
	printf(" %s", g->nodename[n]);
while(top!=-1){						//栈不空则进行 
    keep:
for(k=1;k<=g->v;k++){
	if(g->edges[n][k]!=0&&visit[k]==false){		//找到其临近点且还未访问 	
	stack[++top]=k;									//找到的临近点入栈 
	visit[k]=true;								//标记此节点已经访问（找到） 
	path[k]=n;									//标记 
	printf(" %s", g->nodename[k]);
	n=k;										//以该找到的节点作为起点 
	goto keep;		}							//再找它旁边没访问过的 
}												//直到此点再也找不到能到的点 
	n=stack[top--];									//出栈，再找从此点出发是否还能到达未访问过的
	array[w++]=n;							// 存放拓扑排序 
}
	printf("\n");
	for (j = 1; j <= g->v; j++) {
		if (path[j] != -1) {						//节点一无前驱；从二开始 
			printf("%s的前驱节点%s\n", g->nodename[j], g->nodename[path[j]]);
		}
	}
	for(w=0;w<g->v;w++) printf("%s",g->nodename[array[w]]);   //为一个拓扑排序
}


=======
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


void GraphCreat(graph*g,int edge[][7]);
void PrintfWeight(graph*g);
void DFS(graph* g);

int main(){
	graph g;
g.v=7,g.e=10;

int edge[7][7]= {{0,1,1,0,0,0,0},			//测试数据 
			  {1,0,0,1,1,0,0},			//以零表示无路径到达 
			  {1,0,0,1,0,0,1},
			  {0,1,1,0,1,1,1},
			  {1,0,0,1,0,1,0},
			  {0,0,0,1,1,0,0},
			  {0,0,1,1,0,0,0}};

	GraphCreat(&g,edge);
	PrintfWeight(&g);

	DFS(&g);
	return 0;
}


void GraphCreat(graph* g, int edge[7][7]) {
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


/*可实现拓扑排序；可实现简单路径（如求u->v，传入u，若能有path[v]！=-1，则存在）；
假如对有向图求是否有环，可以这么判断:如果这点之前访问过了，但是现在又有路径可以到达，则有环。
对无向图的话，暂时没有思路。 
*/
void DFS(graph*g){
	int path[maxsize];			//记录路径长度；记录节点前驱 
	int i,j,k,n;
	int w=0,array[maxsize];                 //存防逆拓扑排序 
	int visit[maxsize];	
	int stack[maxsize],top=-1;		
	for(i=1;i<=g->v;i++){
		visit[i]=false;					//标记还没有访问 
		path[i]=-1;	}					//还没有前驱节点 
	printf("请输入起点编号\n"); 
	scanf("%d",&n);
visit[n]=true;						//加入n节点 
path[n]=-1; 							//无前驱 
stack[++top]=n;
	printf("深度优先搜索次序：");
	printf(" %s", g->nodename[n]);
while(top!=-1){						//栈不空则进行 
    keep:
for(k=1;k<=g->v;k++){
	if(g->edges[n][k]!=0&&visit[k]==false){		//找到其临近点且还未访问 	
	stack[++top]=k;									//找到的临近点入栈 
	visit[k]=true;								//标记此节点已经访问（找到） 
	path[k]=n;									//标记 
	printf(" %s", g->nodename[k]);
	n=k;										//以该找到的节点作为起点 
	goto keep;		}							//再找它旁边没访问过的 
}												//直到此点再也找不到能到的点 
	n=stack[top--];									//出栈，再找从此点出发是否还能到达未访问过的
	array[w++]=n;							// 存放拓扑排序 
}
	printf("\n");
	for (j = 1; j <= g->v; j++) {
		if (path[j] != -1) {						//节点一无前驱；从二开始 
			printf("%s的前驱节点%s\n", g->nodename[j], g->nodename[path[j]]);
		}
	}
	for(w=0;w<g->v;w++) printf("%s",g->nodename[array[w]]);   //为一个拓扑排序
}


>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
