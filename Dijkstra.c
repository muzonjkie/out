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
void Dijkstra(graph*g);

		


int main()
{
	graph g;
	g.v=7,g.e=10;				// 创建的图的顶点数，边数。依题目而定 			
int edge[7][7]={{0,50 ,60 ,INF,INF,INF,INF},			//测试用 
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

void GraphCreat(graph*g,int edge[][7]){		//测试一		
	int i,j;	
for(i=1;i<=g->v;i++){
	printf("请输入顶点编号\n");     			//这个存放顶点编号，有些不是纯数字的可用
	scanf("%s",g->nodename[i]); 
for(j=1;j<=g->v;j++){					
	g->edges[i][j]=edge[i-1][j-1];	}			//注意数组是从零开始的 
}
}







void PrintfWeight(graph*g){			//检查输入数据是否正确可用 
	int i,j;		
for(i=1;i<=g->v;i++){						//不大于顶点数，同上 
	for(j=1;j<=g->v;j++){	
	if(i!=j){	
	printf("%s->%s的权值:%-7d",g->nodename[i],g->nodename[j],g->edges[i][j]);			
	if(j==g->v) printf("\n");	}			//成方阵显示 
}
}
}


void Dijkstra(graph*g){			
	int dist[maxsize],final[maxsize];		//记录路径长度；记录是否已加入路径 
	int i,j,h,n,k,min=INF;	
	int path[maxsize];						//前驱节点信息 
printf("请输入创建最小单源路径的起始点序号\n"); 
scanf("%d",&n);
	for(i=1;i<=g->v;i++){					
	dist[i]=g->edges[n][i];				//存放某一顶点到其它点的路径长度 
	path[i]=n;							//此时lowcost里面的权值是属于n号顶点的 
	final[i]=false;			}			//初始化为全部没有加入路径 
	final[n]=true;						//n加入路径
	path[n]=-1;							//n无前驱 
for(h=1;h<g->v;h++){					//已加入一个顶点，少一次循环 		
	min=INF;							//非常重要！！！否则会出错！
for(i=1;i<=g->v;i++){					//注意上下两个for循环的差异	
	if(dist[i]<min&&final[i]!=true){	//找出最短路径且还没有加入路径 
	min=dist[i];
	k=i;	}						//标记加入的顶点是哪个 
}
final[k]=true;						//标记已加入路径 
printf("%s连接到%s,路径长度为%d\n",g->nodename[path[k]],g->nodename[k],dist[k]);
			/*path[k]是存放着这个顶点的路径是从哪个
			顶点接上来的,即前驱；而k是通往的顶点编号*/			
for(j=1;j<=g->v;j++){
	if(dist[j]>(g->edges[k][j]+dist[k])&&final[j]!=true){//看看加入k节点后有没有更短的路可以到达 
	dist[j]=dist[k]+g->edges[k][j];		/*找出新加入节点的邻近点，扩大可连接范围。
	若小于对应dist[j]权值，替换 */
	path[j]=k;	}						//标记更短路径是通过j达成的 
}
}
}
