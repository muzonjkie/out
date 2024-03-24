#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define maxsize 20

typedef struct{
	int s,d;								//点s到点d
	int weight;									//此边权值 
}edge;										//以边作为结构体 

								
int Findparent(int i,int parent[]);
int Edgecreat(edge e[]);
void Kruscal(edge e[],char nodename[][8],int parent[],int n);

int main()
{
	int n;
	int parent[maxsize];			//存放集合根节点 
	char nodename[][8]={"v","v1","v2","v3","v4","v5","v6","v7"};		//定义每个集合的名字,零弃置不用 
	edge e[maxsize];
	n=Edgecreat(e);
	Kruscal(e,nodename,parent,n);	
return 0;
}


int Edgecreat(edge e[]){			//建立边集合 
	int i;
	int v;
	printf("请输入边数\n");
	scanf("%d",&v);
for(i=1;i<=v;i++){
	printf("请输入顶点和边的信息;格式为:点号,点号,权值\n");
	scanf("%d,%d,%d",&e[i].s,&e[i].d,&e[i].weight);	
}
return v;
}



int Findparent(int i,int parent[])							//找到其代表，即该集合的根节点 
{					
if(i==parent[i])	return i;	
return parent[i]=Findparent(parent[i],parent);		//寻找途中顺便把新加入节点全都指向一个根节点，即变胖 
}


void Kruscal(edge e[],char nodename[][8],int parent[],int n)
{
	int i,j,x,y,sumweight=0;
	for(i=1;i<=n;i++) 	parent[i]=i;		//初始化每个节点的代表为自身 
	for(i=2;i<=n;i++){						//插入排序从小到大；从第二个开始对比前面那个 
		if(e[i].weight<e[i-1].weight){
			e[0]=e[i];						//e[0]原先不存有此图的有效数据，这里用来暂存 
			for(j=i-1;e[0].weight<e[j].weight;--j)
				e[j+1]=e[j];						//挪位置 
				e[j+1]=e[0];
		}
	}
	for(i=1;i<=n;i++){
		x=Findparent(e[i].s,parent);
		y=Findparent(e[i].d,parent);
		if(x!=y){							//找到各自集合的根节点是否是同一个 
		parent[x]=y;						//合并两个集合 
		printf("%s连接到%s  权值为%d\n",nodename[e[i].s],nodename[e[i].d],e[i].weight);
		sumweight+=e[i].weight;	 
		}
	}
	printf("总权值为%d\n",sumweight);
}


