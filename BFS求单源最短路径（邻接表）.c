<<<<<<< HEAD
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define maxsize 20
#define INF 32767

typedef struct ArcNode{
	int adjvex;				//����ڵ��� 
	struct ArcNode*nextarc;		
}ArcNode;					//�߽ڵ� 

typedef struct {
	char nodename[maxsize];		//��Ŷ�����Ϣ 
	ArcNode*firstarc;					
}VNode,AdjList[maxsize];		//����ڵ� 

typedef struct {
	AdjList adjlist;			//�������� 
	int v,e;					//������������ 
}graph;

void GraphCreat(graph* g, int edge[7][7]);
void BFS(graph* g);
int main() {
	graph g;
	g.v = 7, g.e = 10;
	int edge[7][7] ={{0,1,1,0,0,0,0},			//�������� 
					 {1,0,0,1,1,0,0},			//�����ʾ��·������ 
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
		printf("�����붥������\n");
		scanf("%s", g->adjlist[i].nodename);
		int count=1;							//���Ƶ�һ���� 
		for (j = 1; j <= g->v; j++) {			//��Ų��ã�ϰ�ߡ�����  
			ArcNode*p;
			ArcNode*s=(ArcNode*)malloc(sizeof(ArcNode));	//������ڵ㣬����·��������ͷ� 
			s->adjvex=j;
			s->nextarc=NULL;
			if(edge[i - 1][j - 1]&&count){		//ע�������Ǵ��㿪ʼ�� 				
				g->adjlist[i].firstarc=s;		//�����õ�һ����	
				p=s;
				count--;			}			//��һ�� 
			else if(edge[i - 1][j - 1]){			
				p->nextarc=s;				
				p=s;			}
			else free(s);						//������ͷ� 
}
}
}




void BFS(graph* g) 
{
	int i, j,n;
	ArcNode*p;
	int visit[maxsize];
	int d[maxsize], path[maxsize];			//��¼·�����ȣ���¼�ڵ�ǰ�� 
	int queue[maxsize], front = 0, rear = 0;
	for (i = 1; i <= g->v; i++) {
		d[i] = INF;						//��ʼΪ����� 
		visit[i] = false;				//��ǻ�û�з��� 
		path[i] = -1;					//��û��ǰ���ڵ� 
}
	printf("�����������\n");
	scanf("%d", &n);					
	visit[n] = true;						//����n�ڵ� 
	d[n] = 0;								//��ʼ��·������Ϊ�� 
	path[n] = -1; 							//��ǰ�� 
	queue[rear] = n;						//n�ڵ���� 
	rear = (rear + 1) % maxsize;
	printf("���������������");
	while (front != rear) {						//���в�������� 
		n = queue[front];						//���ӣ�Ȼ����ʣ� 
		front = (front + 1) % maxsize;
		p=g->adjlist[n].firstarc;
		printf(" %s", g->adjlist[n].nodename);
		while(p){								//�����б߽ڵ� 
			if (visit[p->adjvex]==false) {		//�ҵ����ٽ����һ�δ���� 			
				queue[rear] = p->adjvex;		//�ҵ����ٽ�����ӣ���������һ��n��ֵ��
				rear = (rear + 1) % maxsize;		 
				visit[p->adjvex] = true;					//��Ǵ˽ڵ��Ѿ����ʣ��ҵ��� 
				path[p->adjvex] = n;						//��� 
				d[p->adjvex] = d[n] + 1;}					//·�����ȼ�һ 
			p=p->nextarc;									
		}
	}
	printf("\n");
	for (j = 1; j <= g->v; j++) {
		if (path[j] != -1) {						//�ڵ�һ��ǰ�����Ӷ���ʼ 
			printf("%s��ǰ���ڵ�%s  ·������%d\n", g->adjlist[j].nodename, g->adjlist[path[j]].nodename, d[j]);
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
	int adjvex;				//����ڵ��� 
	struct ArcNode*nextarc;		
}ArcNode;					//�߽ڵ� 

typedef struct {
	char nodename[maxsize];		//��Ŷ�����Ϣ 
	ArcNode*firstarc;					
}VNode,AdjList[maxsize];		//����ڵ� 

typedef struct {
	AdjList adjlist;			//�������� 
	int v,e;					//������������ 
}graph;

void GraphCreat(graph* g, int edge[7][7]);
void BFS(graph* g);
int main() {
	graph g;
	g.v = 7, g.e = 10;
	int edge[7][7] ={{0,1,1,0,0,0,0},			//�������� 
					 {1,0,0,1,1,0,0},			//�����ʾ��·������ 
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
		printf("�����붥������\n");
		scanf("%s", g->adjlist[i].nodename);
		int count=1;							//���Ƶ�һ���� 
		for (j = 1; j <= g->v; j++) {			//��Ų��ã�ϰ�ߡ�����  
			ArcNode*p;
			ArcNode*s=(ArcNode*)malloc(sizeof(ArcNode));	//������ڵ㣬����·��������ͷ� 
			s->adjvex=j;
			s->nextarc=NULL;
			if(edge[i - 1][j - 1]&&count){		//ע�������Ǵ��㿪ʼ�� 				
				g->adjlist[i].firstarc=s;		//�����õ�һ����	
				p=s;
				count--;			}			//��һ�� 
			else if(edge[i - 1][j - 1]){			
				p->nextarc=s;				
				p=s;			}
			else free(s);						//������ͷ� 
}
}
}




void BFS(graph* g) 
{
	int i, j,n;
	ArcNode*p;
	int visit[maxsize];
	int d[maxsize], path[maxsize];			//��¼·�����ȣ���¼�ڵ�ǰ�� 
	int queue[maxsize], front = 0, rear = 0;
	for (i = 1; i <= g->v; i++) {
		d[i] = INF;						//��ʼΪ����� 
		visit[i] = false;				//��ǻ�û�з��� 
		path[i] = -1;					//��û��ǰ���ڵ� 
}
	printf("�����������\n");
	scanf("%d", &n);					
	visit[n] = true;						//����n�ڵ� 
	d[n] = 0;								//��ʼ��·������Ϊ�� 
	path[n] = -1; 							//��ǰ�� 
	queue[rear] = n;						//n�ڵ���� 
	rear = (rear + 1) % maxsize;
	printf("���������������");
	while (front != rear) {						//���в�������� 
		n = queue[front];						//���ӣ�Ȼ����ʣ� 
		front = (front + 1) % maxsize;
		p=g->adjlist[n].firstarc;
		printf(" %s", g->adjlist[n].nodename);
		while(p){								//�����б߽ڵ� 
			if (visit[p->adjvex]==false) {		//�ҵ����ٽ����һ�δ���� 			
				queue[rear] = p->adjvex;		//�ҵ����ٽ�����ӣ���������һ��n��ֵ��
				rear = (rear + 1) % maxsize;		 
				visit[p->adjvex] = true;					//��Ǵ˽ڵ��Ѿ����ʣ��ҵ��� 
				path[p->adjvex] = n;						//��� 
				d[p->adjvex] = d[n] + 1;}					//·�����ȼ�һ 
			p=p->nextarc;									
		}
	}
	printf("\n");
	for (j = 1; j <= g->v; j++) {
		if (path[j] != -1) {						//�ڵ�һ��ǰ�����Ӷ���ʼ 
			printf("%s��ǰ���ڵ�%s  ·������%d\n", g->adjlist[j].nodename, g->adjlist[path[j]].nodename, d[j]);
		}
	}
}


>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
