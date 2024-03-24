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
void Prim(graph*g);



//-------����ķ�����������ͼ����-------- 

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
	Prim(&g);
return 0;	
}

//---------------������������ 

void GraphCreat(graph*g,int edge[][7]){		//���Զ�	
	int i,j;	
for(i=1;i<=g->v;i++){
	printf("�����붥����\n"); 				//�����Ŷ����ţ���Щ���Ǵ����ֵĿ��� 
	scanf("%s",g->nodename[i]); 
for(j=1;j<=g->v;j++){					
	g->edges[i][j]=edge[i-1][j-1];	}			//ע�������Ǵ��㿪ʼ�� 
}
}



void PrintfWeight(graph*g)				//������������Ƿ���ȷ���� 
{			
	int i,j;		
for(i=1;i<=g->v;i++){					//�����ڶ�������ͬ�� 
	for(j=1;j<=g->v;j++){	
	if(i!=j){	
	printf("%s->%s��Ȩֵ:%-7d",g->nodename[i],g->nodename[j],g->edges[i][j]);			
	if(j==g->v) printf("\n");	}			//�ɷ�����ʾ 
}
}
}

void Prim(graph*g)				//������С������ 
{			
	int lowcost[maxsize];		//���ĳһ���㵽�������Ȩֵ 
	int i,j,h,n,k,min=INF;		//ѭ������ 
	int path[maxsize];			//������ʾlowcost�����Ӧλ��Ȩֵ�������ĸ������
	int sumweight=0;			//�ۼ�Ȩֵ 
printf("�����봴����С����������ʼ�����\n"); 
scanf("%d",&n);
	for(i=1;i<=g->v;i++){				//��ĳһ���㵽�����������Ȩֵ�������δ��� 
	lowcost[i]=g->edges[n][i];
	path[i]=n;			}				//��ʱlowcost�����Ȩֵ������n�Ŷ���� 
for(h=1;h<g->v;h++){					//�Ѽ���һ�����㣬��һ��ѭ�� 
	min=INF;							//�ǳ���Ҫ�������������� 
for(i=1;i<=g->v;i++){					//ע����������forѭ���Ĳ��� 
	if(lowcost[i]<min&&lowcost[i]!=0){	//�ҳ��������СȨֵ����Ϊ�����������Ȩֵ 
	min=lowcost[i];
	k=i;	}							//��������ĸ��������� 
}
	sumweight=sumweight+lowcost[k];				//Ȩֵ���� 
	printf("%s���ӵ�%s,ȨֵΪ%d\n",g->nodename[path[k]],g->nodename[k],lowcost[k]);
			/*path[k]�����lowcostĳ��Ԫ��Ȩֵ�������ĸ�
			����ĵ���Ķ���Ȩֵ��Ϣ����k��ͨ���Ķ����� */ 
	lowcost[k]=0;		//�Ѽ���Ķ���Ȩֵ���Ϊ�㣬��ʾ�Ѽ����� 
for(j=1;j<=g->v;j++){
	if(lowcost[j]>g->edges[k][j]&&lowcost[j]!=0){	/*�ҳ���С��Ȩֵ���滻lowcost��ӦȨֵ��
	������������ѭ������ */
	lowcost[j]=g->edges[k][j];	/*�ҳ��¼���ڵ��Ȩֵ����������ӷ�Χ��
	��С�ڶ�ӦlowcostȨֵ���滻 */
	path[j]=k;		}						//���Ȩֵ�����Ķ��� 
}
}
printf("�ۼ�Ȩֵ%d\n",sumweight);
}
