#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define maxsize 20
#define INF 32767

typedef struct {
	int edges[maxsize][maxsize]; 		//�ڽӾ��󣬴��Ȩֵ��ΪINF��ʾû��·������ 
	char nodename[maxsize][maxsize];		//��Ŷ�����Ϣ 
	int v, e;					//������������ 
}graph;						//ͼ�Ľṹ�� 



void GraphCreat(graph* g, int edge[][7]);
void PrintfWeight(graph* g);
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
	PrintfWeight(&g);
	BFS(&g);
	return 0;
}


void GraphCreat(graph* g, int edge[][7]) {
	int i, j;
	for (i = 1; i <= g->v; i++) {
		printf("�����붥����\n");
		scanf("%s", g->nodename[i]);
		for (j = 1; j <= g->v; j++) {			//��Ų��ã�ϰ�ߡ�����  
			g->edges[i][j] = edge[i - 1][j - 1];
		}		//ע�������Ǵ��㿪ʼ�� 
	}
}


void PrintfWeight(graph* g) {			//������������Ƿ���ȷ���� 
	int i, j;
	for (i = 1; i <= g->v; i++) {		//�����ڶ�������ͬ�� 
		for (j = 1; j <= g->v; j++) {
			if (i != j) {
				printf("%s->%s��Ȩֵ:%-7d", g->nodename[i], g->nodename[j], g->edges[i][j]);
				if (j == g->v) printf("\n");
			}			//�ɷ�����ʾ 
		}
	}
}


void BFS(graph* g) 
{
	int i, j, k, n;
	int visit[maxsize];
	int d[maxsize], path[maxsize];			//��¼·�����ȣ���¼�ڵ�ǰ�� 
	int queue[maxsize], front = 0, rear = 0;
	for (i = 1; i <= g->v; i++) {
		d[i] = INF;						//��ʼΪ����� 
		visit[i] = false;				//��ǻ�û�з��� 
		path[i] = -1;					//��û��ǰ���ڵ� 
}
	printf("��������ʼ����\n");
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
		printf(" %s", g->nodename[n]);
		for (k = 1; k <= g->v; k++) {
			if (g->edges[n][k] != 0 && visit[k] != true) {	//�ҵ����ٽ����һ�δ���� 			
				queue[rear] = k;
				rear = (rear + 1) % maxsize;		//�ҵ����ٽ�����ӣ���������һ��n��ֵ�� 
				visit[k] = true;					//��Ǵ˽ڵ��Ѿ����ʣ��ҵ��� 
				path[k] = n;						//��� 
				d[k] = d[n] + 1;					//·�����ȼ�һ 
			}						
		}
	}
	printf("\n");
	for (j = 1; j<= g->v; j++) {
		if (path[j] != -1) {						//�ڵ�һ��ǰ�����Ӷ���ʼ 
			printf("%s��ǰ���ڵ�%s  ·������%d\n", g->nodename[j], g->nodename[path[j]], d[j]);
		}
	}
}


