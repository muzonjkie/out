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

void GraphCreat(graph*g,int edge[][7]);					//函数声明 
void PrintfWeight(graph*g);
void Prim(graph*g);



//-------普里姆用来解决无向图问题-------- 

int main()
{
	graph g;
	g.v=7,g.e=10;				// 创建的图的顶点数，边数。依题目而定 			
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

//---------------难死鼠鼠啦！ 

void GraphCreat(graph*g,int edge[][7]){		//测试二	
	int i,j;	
for(i=1;i<=g->v;i++){
	printf("请输入顶点编号\n"); 				//这个存放顶点编号，有些不是纯数字的可用 
	scanf("%s",g->nodename[i]); 
for(j=1;j<=g->v;j++){					
	g->edges[i][j]=edge[i-1][j-1];	}			//注意数组是从零开始的 
}
}



void PrintfWeight(graph*g)				//检查输入数据是否正确可用 
{			
	int i,j;		
for(i=1;i<=g->v;i++){					//不大于顶点数，同上 
	for(j=1;j<=g->v;j++){	
	if(i!=j){	
	printf("%s->%s的权值:%-7d",g->nodename[i],g->nodename[j],g->edges[i][j]);			
	if(j==g->v) printf("\n");	}			//成方阵显示 
}
}
}

void Prim(graph*g)				//创建最小生成树 
{			
	int lowcost[maxsize];		//存放某一顶点到其它点的权值 
	int i,j,h,n,k,min=INF;		//循环控制 
	int path[maxsize];			//用来表示lowcost里面对应位置权值是属于哪个顶点的
	int sumweight=0;			//累计权值 
printf("请输入创建最小生成树的起始点序号\n"); 
scanf("%d",&n);
	for(i=1;i<=g->v;i++){				//将某一顶点到达其他顶点的权值数据依次存入 
	lowcost[i]=g->edges[n][i];
	path[i]=n;			}				//此时lowcost里面的权值是属于n号顶点的 
for(h=1;h<g->v;h++){					//已加入一个顶点，少一次循环 
	min=INF;							//非常重要！！！否则会出错！ 
for(i=1;i<=g->v;i++){					//注意上下两个for循环的差异 
	if(lowcost[i]<min&&lowcost[i]!=0){	//找出非零的最小权值，零为自身到达自身的权值 
	min=lowcost[i];
	k=i;	}							//标记是往哪个顶点连的 
}
	sumweight=sumweight+lowcost[k];				//权值加上 
	printf("%s连接到%s,权值为%d\n",g->nodename[path[k]],g->nodename[k],lowcost[k]);
			/*path[k]存放着lowcost某单元的权值是属于哪个
			顶点的到别的顶点权值信息；而k是通往的顶点编号 */ 
	lowcost[k]=0;		//把加入的顶点权值标记为零，表示已加入树 
for(j=1;j<=g->v;j++){
	if(lowcost[j]>g->edges[k][j]&&lowcost[j]!=0){	/*找出较小的权值，替换lowcost对应权值；
	后面条件减少循环次数 */
	lowcost[j]=g->edges[k][j];	/*找出新加入节点的权值，扩大可连接范围。
	若小于对应lowcost权值，替换 */
	path[j]=k;		}						//标记权值归属的顶点 
}
}
printf("累计权值%d\n",sumweight);
}
