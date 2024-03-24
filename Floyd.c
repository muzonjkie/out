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
void Floyd(graph*g);




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
Floyd(&g); 
return 0;	
}


//---------------难死鼠鼠啦！ 

void GraphCreat(graph*g,int edge[][7]){				//测试一		
	int i,j;	
for(i=1;i<=g->v;i++){
	printf("请输入顶点编号\n"); 
	scanf("%s",g->nodename[i]); 
for(j=1;j<=g->v;j++){					
	g->edges[i][j]=edge[i-1][j-1];	}		
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

void Floyd(graph*g){		 			
	int i,j,k;
	int dist[8][8],path[8][8];			//从一开始储存 
for(i=1;i<=g->v;i++){									
    for(j=1;j<=g->v;j++){			
	dist[i][j]=g->edges[i][j];			//初始化权值路径表；节点前驱表 
	path[i][j]=j;		}				//初始每点前驱皆为自身 
}		

for(k=1;k<=g->v;k++){					//加入节点k作为中转时 
	for(i=1;i<=g->v;i++){				//起始点编号 
		for(j=1;j<=g->v;j++){			//终点编号 
if(dist[i][j]>(dist[i][k]+dist[k][j])){	//如果加入中转点后有更短的路径可以到达终点 
   dist[i][j]=dist[i][k]+dist[k][j];	//那么以此节点为中转 
   path[i][j]=path[i][k];		}		//此节点为终点的一个前驱（再加入更多的中转点可能还有） 
}
}
}
for(i=1;i<=g->v;i++){
	for(j=1;j<=g->v;j++){				//只需输出以某点出发的权值；对于无向图来说 
	if(i!=j){
	printf("%s->%s的权值:%-6d",g->nodename[i],g->nodename[j],dist[i][j]);
	k=path[i][j];						//获得这个终点的前驱 
	printf("path:%s",g->nodename[i]);	//起始点编号i
	while(k!=j){						/*因为初始时设置前驱为自身；每次加入中转点都可能改变;
										如果不为自身，说明存在中转点*/
		printf("->%s",g->nodename[k]);	//输出该中转点 
		k=path[k][j];	}				//获得中转点的前驱；直到其为j 
	printf("->%s\n",g->nodename[j]);		//终点编号
}
}
printf("\n");
}
}
