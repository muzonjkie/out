#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define N 30
#define M 2*N-1						//n个叶子节点，哈夫曼树最多有2n-1个节点 
#define MAX 9999
//参考自CSDN大佬  素锦流年  -------------------------------- 真的牛犇！！！！！！ 
typedef struct {
	char nodename;				//节点名称
	int weight;				//存放权值 
	int parent;
	int lchild,rchild;
}HTnode;		

void HTnodeCreat(HTnode ht[],int weight[],int n,char nodename[]);
void Select(HTnode ht[],int n,int*s1,int*s2);
void HuffmanCode(HTnode ht[],int n,char nodename[]);


int main(){
HTnode ht[M+1];		
int i,weight[6]={2,3,4,7,8,9};			//存放权值 
char nodename[6]={'f','e','d','c','b','a'};			//节点名称
HTnodeCreat(ht,weight,6,nodename);							 	
HuffmanCode(ht,6,nodename);
return 0;
} 


void HTnodeCreat(HTnode ht[],int weight[],int n,char nodename[]){
	int i;
	for(i=1;i<=n;i++){
		ht[i].nodename=nodename[i-1];
		ht[i].weight=weight[i-1];		//对节点初始化，不用0处，因为会与其他数组产生逻辑错误；无法区分谁是谁的谁 
		ht[i].parent=0;
		ht[i].lchild=ht[i].rchild=0;		
	}
	int m=2*n-1;					//最大节点数 
	for(i=n+1;i<=m;i++){			//后续存放由叶子节点合成的新节点 
		ht[i].weight=0;
		ht[i].parent=0;
		ht[i].lchild=ht[i].rchild=0;		
	}
int s1=0,s2=0;
for(i=n+1;i<=m;i++){
	Select(ht,i-1,&s1,&s2);				//用指针返回两个有效值 
	ht[i].weight=ht[s1].weight+ht[s2].weight;
	ht[i].lchild=s1;				//s1较小作为左孩子 
	ht[i].rchild=s2;				
	ht[s1].parent=i;				//从叶子结点挑选出来组成新节点 
	ht[s2].parent=i;
}
for(i=1;i<=10;i++){
	printf("父母%d\n",ht[i].parent);
}	
}

void Select(HTnode ht[],int n,int*s1,int*s2){
	int i,min1=MAX,min2=MAX;					//初始为极大值 
	*s1=0,*s2=0;								//每次进入此函数都要初始化为零 
for(i=1;i<=n;i++){								//从所有节点中选出最小的两个 
	if(ht[i].parent==0){						//父节点为零则说明还没有加入树中 
		if(ht[i].weight<min1){
			min2=min1;								//min1为选出的最小那个，min2比它稍大 
			*s2=*s1;	//s1记录是哪个节点取得最小值，此处若找到比min1还小的值就把原来min1的编号给s2 
			min1=ht[i].weight;
			*s1=i;	}			//然后再把找到的节点编号赋给s1 
else if(ht[i].weight<min2){				//若找到了min1的值后续则在此处寻找min2的值；为剩余的里面寻找 
		min2=ht[i].weight;
		*s2=i;	}
	}
}
}

void HuffmanCode(HTnode ht[],int n,char nodename[]){
	char*code=(char*)malloc(n*sizeof(char));			//申请指针指向的数组空间 
	int i,j;
	for(i=1;i<=n;i++){								//以叶子节点开始编码，追溯其父母节点逐层往上 
		int start=n-1,c=i,p=ht[i].parent;			//树的最大高度不超过n 
	while(p!=0){							//直到其不存在父节点；即到达根节点 
		--start;							
		if(ht[p].lchild==c)					//定左边为0; 
		code[start]='0';
		else
		code[start]='1';
		c=p;
		p=ht[p].parent;
}
	printf("%c的编码:",nodename[i-1]);
	for(j=0;j<n;j++){							//树的高度是不确定的 
		if(code[j]=='0'||code[j]=='1')		//只有编了码的数组才输出 
		printf("%c",code[j]);	}
printf("\n");
memset(code,-1,n);					//将此数组全部元素置为-1，才能保证下一趟正确的输出 
}
}










//--------------封装为一个函数------------------- 


//void HTnodeCreat(HTnode ht[],int weight[],int n,char nodename[]){
//	int i,j;
//	for(i=1;i<=n;i++){
//		ht[i].nodename=nodename[i-1];
//		ht[i].weight=weight[i-1];		//对节点初始化，不用0处，因为会与其他数组产生逻辑错误；无法区分谁是谁的谁 
//		ht[i].parent=0;
//		ht[i].lchild=ht[i].rchild=0;		
//	}
//	int m=2*n-1;					//最大节点数 
//	for(i=n+1;i<=m;i++){			//后续存放由叶子节点合成的新节点 
//		ht[i].weight=0;
//		ht[i].parent=0;
//		ht[i].lchild=ht[i].rchild=0;		
//	}
//int s1,s2,min1,min2;
//for(i=n+1;i<=m;i++){
//	min1=MAX,min2=MAX;					//初始为极大值 
//	s1=s2=0;
//	for(j=1;j<=i-1;j++){								//从所有节点中选出最小的两个 
//	if(ht[j].parent==0){						//父节点为零则说明还没有加入树中 
//		if(ht[j].weight<min1){
//			min2=min1;								//min1为选出的最小那个，min2比它稍大 
//			s2=s1;  	//s1记录是哪个节点取得最小值，此处若找到比min1还小的值就把原来min1的编号给s2 
//			min1=ht[j].weight;
//			s1=j;	}			//然后再把找到的节点编号赋给s1 
//        else if(ht[j].weight<min2){				//若找到了min1的值后续则在此处寻找min2的值；为剩余的里面寻找 
//		min2=ht[j].weight;
//		s2=j;	}
//	}
//}
//	ht[i].weight=ht[s1].weight+ht[s2].weight;
//	ht[i].lchild=s1;				//s1较小作为左孩子 
//	ht[i].rchild=s2;				
//	ht[s1].parent=i;				//从叶子结点挑选出来组成新节点 
//	ht[s2].parent=i;
//}
//for(i=1;i<=2*n-2;i++){
//	printf("父母%d\n",ht[i].parent);
//}	
//	char*code=(char*)malloc(n*sizeof(char));			//申请指针指向的数组空间 
//	for(i=1;i<=n;i++){								//以叶子节点开始编码，追溯其父母节点逐层往上 
//		int start=n-1,c=i,p=ht[i].parent;			//树的最大高度不超过n 
//	while(p!=0){							//直到其不存在父节点；即到达根节点 
//		--start;							
//		if(ht[p].lchild==c)					//定左边为0; 
//		code[start]='0';
//		else
//		code[start]='1';
//		c=p;
//		p=ht[p].parent;
//}
//	printf("%c的编码:",ht[i].nodename);
//	for(j=0;j<n;j++){							//树的高度是不确定的 
//		if(code[j]=='0'||code[j]=='1')		//只有编了码的数组才输出 
//		printf("%c",code[j]);	}
//printf("\n");
//memset(code,-1,n);					//将此数组全部元素置为-1，才能保证下一趟正确的输出 
//}
//}



