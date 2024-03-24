<<<<<<< HEAD
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include <time.h>
#define maxsize 10


typedef struct {
	int key;
	int flag;
}elem; 
typedef struct{
	elem*base;
	int length;
	int MOD;
}hashtable;
 
void hashcreat(hashtable*hash,int list[]);

int main(){
	hashtable hash;
	int list[maxsize]={21,41,77,25,26,39,11,14,6,6};
	int i; 
//	int list[maxsize];
//	srand((int)time(0));
//	for(i=0;i<maxsize;i++){
//		list[i]=rand()%100+1;	}
hashcreat(&hash,list);	
for(i=0;i<hash.length;i++){
	printf("哈希表数据第%d位置数据%d\n",i,hash.base[i].key);
}	
	return 0;
}



void hashcreat(hashtable*hash,int list[])		
{
	int i,j,k;
	int b[maxsize];			//存放冲突增量函数 
	printf("请输入表的长度\n");
	scanf("%d",&hash->length);
	hash->base=(elem*)malloc(hash->length*sizeof(elem));			//数组从一开始用，标示第一次失败 
	printf("请输入MOD的值\n");
	scanf("%d",&hash->MOD);
	j=1;
for(i=1;i<maxsize-1;i+=2){							//平方探测 
	b[i]=j*j;
	b[i+1]=-b[i];
	j++;	}
for(i=0;i<hash->length;i++){	
	hash->base[i].key=0;					//关键字 
	hash->base[i].flag=0;		}			//标记着某元素是否逻辑上删除 
		
		
for(i=0;i<maxsize;i++){
if(hash->base[list[i]%hash->MOD].flag==0){			//若空位置 
	hash->base[list[i]%hash->MOD].key=list[i];
	hash->base[list[i]%hash->MOD].flag=1;	}	
else {	
	for(k=1;k<=maxsize;k++){
	if(hash->base[(list[i]%hash->MOD+b[k])%hash->length].flag==0){	/*含义为在原本应在的位置基础上 
	再加增量序列模表长	*/
	hash->base[(list[i]%hash->MOD+b[k])%hash->length].key=list[i];
	hash->base[(list[i]%hash->MOD+b[k])%hash->length].flag=1;
	break;		} 				
}
}						
}		
}


=======
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include <time.h>
#define maxsize 10


typedef struct {
	int key;
	int flag;
}elem; 
typedef struct{
	elem*base;
	int length;
	int MOD;
}hashtable;
 
void hashcreat(hashtable*hash,int list[]);

int main(){
	hashtable hash;
	int list[maxsize]={21,41,77,25,26,39,11,14,6,6};
	int i; 
//	int list[maxsize];
//	srand((int)time(0));
//	for(i=0;i<maxsize;i++){
//		list[i]=rand()%100+1;	}
hashcreat(&hash,list);	
for(i=0;i<hash.length;i++){
	printf("哈希表数据第%d位置数据%d\n",i,hash.base[i].key);
}	
	return 0;
}



void hashcreat(hashtable*hash,int list[])		
{
	int i,j,k;
	int b[maxsize];			//存放冲突增量函数 
	printf("请输入表的长度\n");
	scanf("%d",&hash->length);
	hash->base=(elem*)malloc(hash->length*sizeof(elem));			//数组从一开始用，标示第一次失败 
	printf("请输入MOD的值\n");
	scanf("%d",&hash->MOD);
	j=1;
for(i=1;i<maxsize-1;i+=2){							//平方探测 
	b[i]=j*j;
	b[i+1]=-b[i];
	j++;	}
for(i=0;i<hash->length;i++){	
	hash->base[i].key=0;					//关键字 
	hash->base[i].flag=0;		}			//标记着某元素是否逻辑上删除 
		
		
for(i=0;i<maxsize;i++){
if(hash->base[list[i]%hash->MOD].flag==0){			//若空位置 
	hash->base[list[i]%hash->MOD].key=list[i];
	hash->base[list[i]%hash->MOD].flag=1;	}	
else {	
	for(k=1;k<=maxsize;k++){
	if(hash->base[(list[i]%hash->MOD+b[k])%hash->length].flag==0){	/*含义为在原本应在的位置基础上 
	再加增量序列模表长	*/
	hash->base[(list[i]%hash->MOD+b[k])%hash->length].key=list[i];
	hash->base[(list[i]%hash->MOD+b[k])%hash->length].flag=1;
	break;		} 				
}
}						
}		
}


>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
