#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define N 30
#define M 2*N-1						//n��Ҷ�ӽڵ㣬�������������2n-1���ڵ� 
#define MAX 9999
//�ο���CSDN����  �ؽ�����  -------------------------------- ���ţ�ģ����������� 
typedef struct {
	char nodename;				//�ڵ�����
	int weight;				//���Ȩֵ 
	int parent;
	int lchild,rchild;
}HTnode;		

void HTnodeCreat(HTnode ht[],int weight[],int n,char nodename[]);
void Select(HTnode ht[],int n,int*s1,int*s2);
void HuffmanCode(HTnode ht[],int n,char nodename[]);


int main(){
HTnode ht[M+1];		
int i,weight[6]={2,3,4,7,8,9};			//���Ȩֵ 
char nodename[6]={'f','e','d','c','b','a'};			//�ڵ�����
HTnodeCreat(ht,weight,6,nodename);							 	
HuffmanCode(ht,6,nodename);
return 0;
} 


void HTnodeCreat(HTnode ht[],int weight[],int n,char nodename[]){
	int i;
	for(i=1;i<=n;i++){
		ht[i].nodename=nodename[i-1];
		ht[i].weight=weight[i-1];		//�Խڵ��ʼ��������0������Ϊ����������������߼������޷�����˭��˭��˭ 
		ht[i].parent=0;
		ht[i].lchild=ht[i].rchild=0;		
	}
	int m=2*n-1;					//���ڵ��� 
	for(i=n+1;i<=m;i++){			//���������Ҷ�ӽڵ�ϳɵ��½ڵ� 
		ht[i].weight=0;
		ht[i].parent=0;
		ht[i].lchild=ht[i].rchild=0;		
	}
int s1=0,s2=0;
for(i=n+1;i<=m;i++){
	Select(ht,i-1,&s1,&s2);				//��ָ�뷵��������Чֵ 
	ht[i].weight=ht[s1].weight+ht[s2].weight;
	ht[i].lchild=s1;				//s1��С��Ϊ���� 
	ht[i].rchild=s2;				
	ht[s1].parent=i;				//��Ҷ�ӽ����ѡ��������½ڵ� 
	ht[s2].parent=i;
}
for(i=1;i<=10;i++){
	printf("��ĸ%d\n",ht[i].parent);
}	
}

void Select(HTnode ht[],int n,int*s1,int*s2){
	int i,min1=MAX,min2=MAX;					//��ʼΪ����ֵ 
	*s1=0,*s2=0;								//ÿ�ν���˺�����Ҫ��ʼ��Ϊ�� 
for(i=1;i<=n;i++){								//�����нڵ���ѡ����С������ 
	if(ht[i].parent==0){						//���ڵ�Ϊ����˵����û�м������� 
		if(ht[i].weight<min1){
			min2=min1;								//min1Ϊѡ������С�Ǹ���min2�����Դ� 
			*s2=*s1;	//s1��¼���ĸ��ڵ�ȡ����Сֵ���˴����ҵ���min1��С��ֵ�Ͱ�ԭ��min1�ı�Ÿ�s2 
			min1=ht[i].weight;
			*s1=i;	}			//Ȼ���ٰ��ҵ��Ľڵ��Ÿ���s1 
else if(ht[i].weight<min2){				//���ҵ���min1��ֵ�������ڴ˴�Ѱ��min2��ֵ��Ϊʣ�������Ѱ�� 
		min2=ht[i].weight;
		*s2=i;	}
	}
}
}

void HuffmanCode(HTnode ht[],int n,char nodename[]){
	char*code=(char*)malloc(n*sizeof(char));			//����ָ��ָ�������ռ� 
	int i,j;
	for(i=1;i<=n;i++){								//��Ҷ�ӽڵ㿪ʼ���룬׷���丸ĸ�ڵ�������� 
		int start=n-1,c=i,p=ht[i].parent;			//�������߶Ȳ�����n 
	while(p!=0){							//ֱ���䲻���ڸ��ڵ㣻��������ڵ� 
		--start;							
		if(ht[p].lchild==c)					//�����Ϊ0; 
		code[start]='0';
		else
		code[start]='1';
		c=p;
		p=ht[p].parent;
}
	printf("%c�ı���:",nodename[i-1]);
	for(j=0;j<n;j++){							//���ĸ߶��ǲ�ȷ���� 
		if(code[j]=='0'||code[j]=='1')		//ֻ�б�������������� 
		printf("%c",code[j]);	}
printf("\n");
memset(code,-1,n);					//��������ȫ��Ԫ����Ϊ-1�����ܱ�֤��һ����ȷ����� 
}
}










//--------------��װΪһ������------------------- 


//void HTnodeCreat(HTnode ht[],int weight[],int n,char nodename[]){
//	int i,j;
//	for(i=1;i<=n;i++){
//		ht[i].nodename=nodename[i-1];
//		ht[i].weight=weight[i-1];		//�Խڵ��ʼ��������0������Ϊ����������������߼������޷�����˭��˭��˭ 
//		ht[i].parent=0;
//		ht[i].lchild=ht[i].rchild=0;		
//	}
//	int m=2*n-1;					//���ڵ��� 
//	for(i=n+1;i<=m;i++){			//���������Ҷ�ӽڵ�ϳɵ��½ڵ� 
//		ht[i].weight=0;
//		ht[i].parent=0;
//		ht[i].lchild=ht[i].rchild=0;		
//	}
//int s1,s2,min1,min2;
//for(i=n+1;i<=m;i++){
//	min1=MAX,min2=MAX;					//��ʼΪ����ֵ 
//	s1=s2=0;
//	for(j=1;j<=i-1;j++){								//�����нڵ���ѡ����С������ 
//	if(ht[j].parent==0){						//���ڵ�Ϊ����˵����û�м������� 
//		if(ht[j].weight<min1){
//			min2=min1;								//min1Ϊѡ������С�Ǹ���min2�����Դ� 
//			s2=s1;  	//s1��¼���ĸ��ڵ�ȡ����Сֵ���˴����ҵ���min1��С��ֵ�Ͱ�ԭ��min1�ı�Ÿ�s2 
//			min1=ht[j].weight;
//			s1=j;	}			//Ȼ���ٰ��ҵ��Ľڵ��Ÿ���s1 
//        else if(ht[j].weight<min2){				//���ҵ���min1��ֵ�������ڴ˴�Ѱ��min2��ֵ��Ϊʣ�������Ѱ�� 
//		min2=ht[j].weight;
//		s2=j;	}
//	}
//}
//	ht[i].weight=ht[s1].weight+ht[s2].weight;
//	ht[i].lchild=s1;				//s1��С��Ϊ���� 
//	ht[i].rchild=s2;				
//	ht[s1].parent=i;				//��Ҷ�ӽ����ѡ��������½ڵ� 
//	ht[s2].parent=i;
//}
//for(i=1;i<=2*n-2;i++){
//	printf("��ĸ%d\n",ht[i].parent);
//}	
//	char*code=(char*)malloc(n*sizeof(char));			//����ָ��ָ�������ռ� 
//	for(i=1;i<=n;i++){								//��Ҷ�ӽڵ㿪ʼ���룬׷���丸ĸ�ڵ�������� 
//		int start=n-1,c=i,p=ht[i].parent;			//�������߶Ȳ�����n 
//	while(p!=0){							//ֱ���䲻���ڸ��ڵ㣻��������ڵ� 
//		--start;							
//		if(ht[p].lchild==c)					//�����Ϊ0; 
//		code[start]='0';
//		else
//		code[start]='1';
//		c=p;
//		p=ht[p].parent;
//}
//	printf("%c�ı���:",ht[i].nodename);
//	for(j=0;j<n;j++){							//���ĸ߶��ǲ�ȷ���� 
//		if(code[j]=='0'||code[j]=='1')		//ֻ�б�������������� 
//		printf("%c",code[j]);	}
//printf("\n");
//memset(code,-1,n);					//��������ȫ��Ԫ����Ϊ-1�����ܱ�֤��һ����ȷ����� 
//}
//}



