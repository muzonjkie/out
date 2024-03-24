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


void GraphCreat(graph*g,int edge[][7]);					//�������� 
void PrintfWeight(graph*g);
void Floyd(graph*g);




int main()
{
	graph g;
	g.v=7,g.e=10;				// ������ͼ�Ķ�����������������Ŀ���� 			
int edge[7][7]={{0,50 ,60 ,INF,INF,INF,INF},
			  {50 ,0  ,INF,65 ,40 ,INF,INF},
			  {60 ,INF,0  ,52 ,INF,INF,45},
			  {INF,65 ,52 ,0  ,50 ,30 ,42},
			  {INF,40 ,INF,50 ,0  ,70 ,INF},
			  {INF,INF,INF,30 ,70 ,0  ,INF},
			  {INF,INF,45 ,42 ,INF,INF,0}};
GraphCreat(&g,edge); 
PrintfWeight(&g);
printf("\n");
Floyd(&g); 
return 0;	
}


//---------------������������ 

void GraphCreat(graph*g,int edge[][7]){				//����һ		
	int i,j;	
for(i=1;i<=g->v;i++){
	printf("�����붥����\n"); 
	scanf("%s",g->nodename[i]); 
for(j=1;j<=g->v;j++){					
	g->edges[i][j]=edge[i-1][j-1];	}		
}
}





void PrintfWeight(graph*g){			//������������Ƿ���ȷ���� 
	int i,j;		
for(i=1;i<=g->v;i++){						//�����ڶ�������ͬ�� 
	for(j=1;j<=g->v;j++){	
	if(i!=j){	
	printf("%s->%s��Ȩֵ:%-7d",g->nodename[i],g->nodename[j],g->edges[i][j]);			
	if(j==g->v) printf("\n");	}			//�ɷ�����ʾ 
}
}
}

void Floyd(graph*g){		 			
	int i,j,k;
	int dist[8][8],path[8][8];			//��һ��ʼ���� 
for(i=1;i<=g->v;i++){									
    for(j=1;j<=g->v;j++){			
	dist[i][j]=g->edges[i][j];			//��ʼ��Ȩֵ·�����ڵ�ǰ���� 
	path[i][j]=j;		}				//��ʼÿ��ǰ����Ϊ���� 
}		

for(k=1;k<=g->v;k++){					//����ڵ�k��Ϊ��תʱ 
	for(i=1;i<=g->v;i++){				//��ʼ���� 
		for(j=1;j<=g->v;j++){			//�յ��� 
if(dist[i][j]>(dist[i][k]+dist[k][j])){	//���������ת����и��̵�·�����Ե����յ� 
   dist[i][j]=dist[i][k]+dist[k][j];	//��ô�Դ˽ڵ�Ϊ��ת 
   path[i][j]=path[i][k];		}		//�˽ڵ�Ϊ�յ��һ��ǰ�����ټ���������ת����ܻ��У� 
}
}
}
for(i=1;i<=g->v;i++){
	for(j=1;j<=g->v;j++){				//ֻ�������ĳ�������Ȩֵ����������ͼ��˵ 
	if(i!=j){
	printf("%s->%s��Ȩֵ:%-6d",g->nodename[i],g->nodename[j],dist[i][j]);
	k=path[i][j];						//�������յ��ǰ�� 
	printf("path:%s",g->nodename[i]);	//��ʼ����i
	while(k!=j){						/*��Ϊ��ʼʱ����ǰ��Ϊ����ÿ�μ�����ת�㶼���ܸı�;
										�����Ϊ����˵��������ת��*/
		printf("->%s",g->nodename[k]);	//�������ת�� 
		k=path[k][j];	}				//�����ת���ǰ����ֱ����Ϊj 
	printf("->%s\n",g->nodename[j]);		//�յ���
}
}
printf("\n");
}
}
