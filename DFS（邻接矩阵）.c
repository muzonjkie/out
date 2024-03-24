<<<<<<< HEAD
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


void GraphCreat(graph*g,int edge[][7]);
void PrintfWeight(graph*g);
void DFS(graph* g);

int main(){
	graph g;
g.v=7,g.e=10;

int edge[7][7]= {{0,1,1,0,0,0,0},			//�������� 
			  {1,0,0,1,1,0,0},			//�����ʾ��·������ 
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


/*��ʵ���������򣻿�ʵ�ּ�·��������u->v������u��������path[v]��=-1������ڣ���
���������ͼ���Ƿ��л���������ô�ж�:������֮ǰ���ʹ��ˣ�������������·�����Ե�����л���
������ͼ�Ļ�����ʱû��˼·�� 
*/
void DFS(graph*g){
	int path[maxsize];			//��¼·�����ȣ���¼�ڵ�ǰ�� 
	int i,j,k,n;
	int w=0,array[maxsize];                 //������������� 
	int visit[maxsize];	
	int stack[maxsize],top=-1;		
	for(i=1;i<=g->v;i++){
		visit[i]=false;					//��ǻ�û�з��� 
		path[i]=-1;	}					//��û��ǰ���ڵ� 
	printf("�����������\n"); 
	scanf("%d",&n);
visit[n]=true;						//����n�ڵ� 
path[n]=-1; 							//��ǰ�� 
stack[++top]=n;
	printf("���������������");
	printf(" %s", g->nodename[n]);
while(top!=-1){						//ջ��������� 
    keep:
for(k=1;k<=g->v;k++){
	if(g->edges[n][k]!=0&&visit[k]==false){		//�ҵ����ٽ����һ�δ���� 	
	stack[++top]=k;									//�ҵ����ٽ�����ջ 
	visit[k]=true;								//��Ǵ˽ڵ��Ѿ����ʣ��ҵ��� 
	path[k]=n;									//��� 
	printf(" %s", g->nodename[k]);
	n=k;										//�Ը��ҵ��Ľڵ���Ϊ��� 
	goto keep;		}							//�������Ա�û���ʹ��� 
}												//ֱ���˵���Ҳ�Ҳ����ܵ��ĵ� 
	n=stack[top--];									//��ջ�����ҴӴ˵�����Ƿ��ܵ���δ���ʹ���
	array[w++]=n;							// ����������� 
}
	printf("\n");
	for (j = 1; j <= g->v; j++) {
		if (path[j] != -1) {						//�ڵ�һ��ǰ�����Ӷ���ʼ 
			printf("%s��ǰ���ڵ�%s\n", g->nodename[j], g->nodename[path[j]]);
		}
	}
	for(w=0;w<g->v;w++) printf("%s",g->nodename[array[w]]);   //Ϊһ����������
}


=======
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


void GraphCreat(graph*g,int edge[][7]);
void PrintfWeight(graph*g);
void DFS(graph* g);

int main(){
	graph g;
g.v=7,g.e=10;

int edge[7][7]= {{0,1,1,0,0,0,0},			//�������� 
			  {1,0,0,1,1,0,0},			//�����ʾ��·������ 
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


/*��ʵ���������򣻿�ʵ�ּ�·��������u->v������u��������path[v]��=-1������ڣ���
���������ͼ���Ƿ��л���������ô�ж�:������֮ǰ���ʹ��ˣ�������������·�����Ե�����л���
������ͼ�Ļ�����ʱû��˼·�� 
*/
void DFS(graph*g){
	int path[maxsize];			//��¼·�����ȣ���¼�ڵ�ǰ�� 
	int i,j,k,n;
	int w=0,array[maxsize];                 //������������� 
	int visit[maxsize];	
	int stack[maxsize],top=-1;		
	for(i=1;i<=g->v;i++){
		visit[i]=false;					//��ǻ�û�з��� 
		path[i]=-1;	}					//��û��ǰ���ڵ� 
	printf("�����������\n"); 
	scanf("%d",&n);
visit[n]=true;						//����n�ڵ� 
path[n]=-1; 							//��ǰ�� 
stack[++top]=n;
	printf("���������������");
	printf(" %s", g->nodename[n]);
while(top!=-1){						//ջ��������� 
    keep:
for(k=1;k<=g->v;k++){
	if(g->edges[n][k]!=0&&visit[k]==false){		//�ҵ����ٽ����һ�δ���� 	
	stack[++top]=k;									//�ҵ����ٽ�����ջ 
	visit[k]=true;								//��Ǵ˽ڵ��Ѿ����ʣ��ҵ��� 
	path[k]=n;									//��� 
	printf(" %s", g->nodename[k]);
	n=k;										//�Ը��ҵ��Ľڵ���Ϊ��� 
	goto keep;		}							//�������Ա�û���ʹ��� 
}												//ֱ���˵���Ҳ�Ҳ����ܵ��ĵ� 
	n=stack[top--];									//��ջ�����ҴӴ˵�����Ƿ��ܵ���δ���ʹ���
	array[w++]=n;							// ����������� 
}
	printf("\n");
	for (j = 1; j <= g->v; j++) {
		if (path[j] != -1) {						//�ڵ�һ��ǰ�����Ӷ���ʼ 
			printf("%s��ǰ���ڵ�%s\n", g->nodename[j], g->nodename[path[j]]);
		}
	}
	for(w=0;w<g->v;w++) printf("%s",g->nodename[array[w]]);   //Ϊһ����������
}


>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
