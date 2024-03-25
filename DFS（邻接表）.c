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
void DFS(graph* g);
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

	DFS(&g);
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


/*��ʵ���������򣻿�ʵ�ּ�·��������u->v������u��������path[v]��=-1������ڣ���
���������ͼ���Ƿ��л���������ô�ж�:������֮ǰ���ʹ��ˣ�������������·�����Ե�����л���
������ͼ�Ļ�����ʱû��˼·�� 
*/


void DFS(graph* g) 
{
	int i, j,n;
	ArcNode*p;
	int visit[maxsize];
	int path[maxsize];			//��¼·�����ȣ���¼�ڵ�ǰ�� 
	int w=0,array[maxsize];                 //������������� 
	int stack[maxsize],top=-1;	
	for (i = 1; i <= g->v; i++) {
		visit[i] = false;				//��ǻ�û�з��� 
		path[i] = -1;					//��û��ǰ���ڵ� 
}			
	printf("�����������\n");
	scanf("%d", &n);		
	visit[n] = true;						//����n�ڵ� 
	path[n] = -1; 							//��ǰ�� 
	stack[++top]= n;						//n�ڵ���� 
	printf("���������������");
	printf(" %s", g->adjlist[n].nodename);
	while (top!=-1) {						//���в�������� 
		keep:
		p=g->adjlist[n].firstarc;
		while(p){								//�����б߽ڵ� 
			if (visit[p->adjvex]==false) {		//�ҵ����ٽ����һ�δ���� 			
				stack[++top] = p->adjvex;		//�ҵ����ٽ�����ӣ���������һ��n��ֵ��
				visit[p->adjvex] = true;					//��Ǵ˽ڵ��Ѿ����ʣ��ҵ��� 
				path[p->adjvex] = n;						//��� 
				printf(" %s", g->adjlist[p->adjvex].nodename);
				n=p->adjvex;
				goto keep;			}					//·�����ȼ�һ 
			p=p->nextarc;									
		}
		n=stack[top--];
		array[w++]=n;							// ����������� 
	}
	printf("\n");
	for (j = 1; j <= g->v; j++) {
		if (path[j] != -1) {						//�ڵ�һ��ǰ�����Ӷ���ʼ 
			printf("%s��ǰ���ڵ�%s\n", g->adjlist[j].nodename, g->adjlist[path[j]].nodename);
		}
	}
	for(w=0;w<g->v;w++) printf("%s",g->adjlist[array[w]].nodename);   //Ϊһ����������
}


