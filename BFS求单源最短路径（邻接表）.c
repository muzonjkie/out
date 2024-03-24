<<<<<<< HEAD
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define maxsize 20
#define INF 32767

typedef struct ArcNode{
	int adjvex;				//到达节点编号 
	struct ArcNode*nextarc;		
}ArcNode;					//边节点 

typedef struct {
	char nodename[maxsize];		//存放顶点信息 
	ArcNode*firstarc;					
}VNode,AdjList[maxsize];		//顶点节点 

typedef struct {
	AdjList adjlist;			//顶点数组 
	int v,e;					//顶点数，边数 
}graph;

void GraphCreat(graph* g, int edge[7][7]);
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

	BFS(&g);
	return 0;
}


void GraphCreat(graph* g, int edge[7][7]) {
	int i, j;
	for (i = 1; i <= g->v; i++) {
		printf("请输入顶点名称\n");
		scanf("%s", g->adjlist[i].nodename);
		int count=1;							//控制第一条边 
		for (j = 1; j <= g->v; j++) {			//零号不用，习惯。不懂  
			ArcNode*p;
			ArcNode*s=(ArcNode*)malloc(sizeof(ArcNode));	//先制造节点，若无路径到达，再释放 
			s->adjvex=j;
			s->nextarc=NULL;
			if(edge[i - 1][j - 1]&&count){		//注意数组是从零开始的 				
				g->adjlist[i].firstarc=s;		//优先置第一条边	
				p=s;
				count--;			}			//仅一次 
			else if(edge[i - 1][j - 1]){			
				p->nextarc=s;				
				p=s;			}
			else free(s);						//不到达，释放 
}
}
}




void BFS(graph* g) 
{
	int i, j,n;
	ArcNode*p;
	int visit[maxsize];
	int d[maxsize], path[maxsize];			//记录路径长度；记录节点前驱 
	int queue[maxsize], front = 0, rear = 0;
	for (i = 1; i <= g->v; i++) {
		d[i] = INF;						//初始为无穷大 
		visit[i] = false;				//标记还没有访问 
		path[i] = -1;					//还没有前驱节点 
}
	printf("请输入起点编号\n");
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
		p=g->adjlist[n].firstarc;
		printf(" %s", g->adjlist[n].nodename);
		while(p){								//若还有边节点 
			if (visit[p->adjvex]==false) {		//找到其临近点且还未访问 			
				queue[rear] = p->adjvex;		//找到的临近点入队；（会是下一个n的值）
				rear = (rear + 1) % maxsize;		 
				visit[p->adjvex] = true;					//标记此节点已经访问（找到） 
				path[p->adjvex] = n;						//标记 
				d[p->adjvex] = d[n] + 1;}					//路径长度加一 
			p=p->nextarc;									
		}
	}
	printf("\n");
	for (j = 1; j <= g->v; j++) {
		if (path[j] != -1) {						//节点一无前驱；从二开始 
			printf("%s的前驱节点%s  路径长度%d\n", g->adjlist[j].nodename, g->adjlist[path[j]].nodename, d[j]);
		}
	}
}


=======
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define maxsize 20
#define INF 32767

typedef struct ArcNode{
	int adjvex;				//到达节点编号 
	struct ArcNode*nextarc;		
}ArcNode;					//边节点 

typedef struct {
	char nodename[maxsize];		//存放顶点信息 
	ArcNode*firstarc;					
}VNode,AdjList[maxsize];		//顶点节点 

typedef struct {
	AdjList adjlist;			//顶点数组 
	int v,e;					//顶点数，边数 
}graph;

void GraphCreat(graph* g, int edge[7][7]);
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

	BFS(&g);
	return 0;
}


void GraphCreat(graph* g, int edge[7][7]) {
	int i, j;
	for (i = 1; i <= g->v; i++) {
		printf("请输入顶点名称\n");
		scanf("%s", g->adjlist[i].nodename);
		int count=1;							//控制第一条边 
		for (j = 1; j <= g->v; j++) {			//零号不用，习惯。不懂  
			ArcNode*p;
			ArcNode*s=(ArcNode*)malloc(sizeof(ArcNode));	//先制造节点，若无路径到达，再释放 
			s->adjvex=j;
			s->nextarc=NULL;
			if(edge[i - 1][j - 1]&&count){		//注意数组是从零开始的 				
				g->adjlist[i].firstarc=s;		//优先置第一条边	
				p=s;
				count--;			}			//仅一次 
			else if(edge[i - 1][j - 1]){			
				p->nextarc=s;				
				p=s;			}
			else free(s);						//不到达，释放 
}
}
}




void BFS(graph* g) 
{
	int i, j,n;
	ArcNode*p;
	int visit[maxsize];
	int d[maxsize], path[maxsize];			//记录路径长度；记录节点前驱 
	int queue[maxsize], front = 0, rear = 0;
	for (i = 1; i <= g->v; i++) {
		d[i] = INF;						//初始为无穷大 
		visit[i] = false;				//标记还没有访问 
		path[i] = -1;					//还没有前驱节点 
}
	printf("请输入起点编号\n");
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
		p=g->adjlist[n].firstarc;
		printf(" %s", g->adjlist[n].nodename);
		while(p){								//若还有边节点 
			if (visit[p->adjvex]==false) {		//找到其临近点且还未访问 			
				queue[rear] = p->adjvex;		//找到的临近点入队；（会是下一个n的值）
				rear = (rear + 1) % maxsize;		 
				visit[p->adjvex] = true;					//标记此节点已经访问（找到） 
				path[p->adjvex] = n;						//标记 
				d[p->adjvex] = d[n] + 1;}					//路径长度加一 
			p=p->nextarc;									
		}
	}
	printf("\n");
	for (j = 1; j <= g->v; j++) {
		if (path[j] != -1) {						//节点一无前驱；从二开始 
			printf("%s的前驱节点%s  路径长度%d\n", g->adjlist[j].nodename, g->adjlist[path[j]].nodename, d[j]);
		}
	}
}


>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
