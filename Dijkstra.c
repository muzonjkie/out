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
void Dijkstra(graph*g);

		


int main()
{
	graph g;
	g.v=7,g.e=10;				// ������ͼ�Ķ�����������������Ŀ���� 			
int edge[7][7]={{0,50 ,60 ,INF,INF,INF,INF},			//������ 
			  {50 ,0  ,INF,65 ,40 ,INF,INF},
			  {60 ,INF,0  ,52 ,INF,INF,45},
			  {INF,65 ,52 ,0  ,50 ,30 ,42},
			  {INF,40 ,INF,50 ,0  ,70 ,INF},
			  {INF,INF,INF,30 ,70 ,0  ,INF},
			  {INF,INF,45 ,42 ,INF,INF,0}};
GraphCreat(&g,edge); 
PrintfWeight(&g);
printf("\n");
Dijkstra(&g);
return 0;	
}

void GraphCreat(graph*g,int edge[][7]){		//����һ		
	int i,j;	
for(i=1;i<=g->v;i++){
	printf("�����붥����\n");     			//�����Ŷ����ţ���Щ���Ǵ����ֵĿ���
	scanf("%s",g->nodename[i]); 
for(j=1;j<=g->v;j++){					
	g->edges[i][j]=edge[i-1][j-1];	}			//ע�������Ǵ��㿪ʼ�� 
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


void Dijkstra(graph*g){			
	int dist[maxsize],final[maxsize];		//��¼·�����ȣ���¼�Ƿ��Ѽ���·�� 
	int i,j,h,n,k,min=INF;	
	int path[maxsize];						//ǰ���ڵ���Ϣ 
printf("�����봴����С��Դ·������ʼ�����\n"); 
scanf("%d",&n);
	for(i=1;i<=g->v;i++){					
	dist[i]=g->edges[n][i];				//���ĳһ���㵽�������·������ 
	path[i]=n;							//��ʱlowcost�����Ȩֵ������n�Ŷ���� 
	final[i]=false;			}			//��ʼ��Ϊȫ��û�м���·�� 
	final[n]=true;						//n����·��
	path[n]=-1;							//n��ǰ�� 
for(h=1;h<g->v;h++){					//�Ѽ���һ�����㣬��һ��ѭ�� 		
	min=INF;							//�ǳ���Ҫ��������������
for(i=1;i<=g->v;i++){					//ע����������forѭ���Ĳ���	
	if(dist[i]<min&&final[i]!=true){	//�ҳ����·���һ�û�м���·�� 
	min=dist[i];
	k=i;	}						//��Ǽ���Ķ������ĸ� 
}
final[k]=true;						//����Ѽ���·�� 
printf("%s���ӵ�%s,·������Ϊ%d\n",g->nodename[path[k]],g->nodename[k],dist[k]);
			/*path[k]�Ǵ������������·���Ǵ��ĸ�
			�����������,��ǰ������k��ͨ���Ķ�����*/			
for(j=1;j<=g->v;j++){
	if(dist[j]>(g->edges[k][j]+dist[k])&&final[j]!=true){//��������k�ڵ����û�и��̵�·���Ե��� 
	dist[j]=dist[k]+g->edges[k][j];		/*�ҳ��¼���ڵ���ڽ��㣬��������ӷ�Χ��
	��С�ڶ�Ӧdist[j]Ȩֵ���滻 */
	path[j]=k;	}						//��Ǹ���·����ͨ��j��ɵ� 
}
}
}
