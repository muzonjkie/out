#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define maxsize 20

typedef struct{
	int s,d;								//��s����d
	int weight;									//�˱�Ȩֵ 
}edge;										//�Ա���Ϊ�ṹ�� 

								
int Findparent(int i,int parent[]);
int Edgecreat(edge e[]);
void Kruscal(edge e[],char nodename[][8],int parent[],int n);

int main()
{
	int n;
	int parent[maxsize];			//��ż��ϸ��ڵ� 
	char nodename[][8]={"v","v1","v2","v3","v4","v5","v6","v7"};		//����ÿ�����ϵ�����,�����ò��� 
	edge e[maxsize];
	n=Edgecreat(e);
	Kruscal(e,nodename,parent,n);	
return 0;
}


int Edgecreat(edge e[]){			//�����߼��� 
	int i;
	int v;
	printf("���������\n");
	scanf("%d",&v);
for(i=1;i<=v;i++){
	printf("�����붥��ͱߵ���Ϣ;��ʽΪ:���,���,Ȩֵ\n");
	scanf("%d,%d,%d",&e[i].s,&e[i].d,&e[i].weight);	
}
return v;
}



int Findparent(int i,int parent[])							//�ҵ���������ü��ϵĸ��ڵ� 
{					
if(i==parent[i])	return i;	
return parent[i]=Findparent(parent[i],parent);		//Ѱ��;��˳����¼���ڵ�ȫ��ָ��һ�����ڵ㣬������ 
}


void Kruscal(edge e[],char nodename[][8],int parent[],int n)
{
	int i,j,x,y,sumweight=0;
	for(i=1;i<=n;i++) 	parent[i]=i;		//��ʼ��ÿ���ڵ�Ĵ���Ϊ���� 
	for(i=2;i<=n;i++){						//���������С���󣻴ӵڶ�����ʼ�Ա�ǰ���Ǹ� 
		if(e[i].weight<e[i-1].weight){
			e[0]=e[i];						//e[0]ԭ�Ȳ����д�ͼ����Ч���ݣ����������ݴ� 
			for(j=i-1;e[0].weight<e[j].weight;--j)
				e[j+1]=e[j];						//Ųλ�� 
				e[j+1]=e[0];
		}
	}
	for(i=1;i<=n;i++){
		x=Findparent(e[i].s,parent);
		y=Findparent(e[i].d,parent);
		if(x!=y){							//�ҵ����Լ��ϵĸ��ڵ��Ƿ���ͬһ�� 
		parent[x]=y;						//�ϲ��������� 
		printf("%s���ӵ�%s  ȨֵΪ%d\n",nodename[e[i].s],nodename[e[i].d],e[i].weight);
		sumweight+=e[i].weight;	 
		}
	}
	printf("��ȨֵΪ%d\n",sumweight);
}


