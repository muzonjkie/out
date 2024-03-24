#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include <time.h>
#define maxsize 20


typedef struct elem{
	int key;
	struct	elem*next; 
}elem; 

typedef struct{
	elem* base[maxsize];
	int MOD;
}hashtable;

int a=8; 
int b=5,c;


void hashcreat(hashtable* hash,int list[],int num);

int main(){
	int i,MOD,count; 
	hashtable hash;
	int list[maxsize]={21,41,77,25,26,39,11,14,6,6};
//	srand((unsigned)time(0));
//for(i=0;i<maxsize;i++){
//	list[i]=rand()%100+1;	}			
	elem*p;
hashcreat(&hash,list,10);	
for(i=0;i<hash.MOD;i++){
	count=1;
	p=hash.base[i];
	while(p){
	printf("哈希表数据第%d位置第%d个数据%d\n",i,count,p->key);
	count++;	
	p=p->next;		}
}	
	return 0;
}



void hashcreat(hashtable* hash,int list[],int num)			//拉链法hash表 
{
	printf("请输入表的长度,即MOD的值\n");
	scanf("%d",&hash->MOD);
	int i; 
	for(i=0;i<hash->MOD;i++){		
	hash->base[i]=NULL;	}			//否则出错 
	elem *p,*temp;		
for(i=0;i<num;i++){
	p=(elem*)calloc(1,sizeof(elem));
	p->key=list[i];
if(hash->base[p->key%hash->MOD]==NULL){		 
	hash->base[p->key%hash->MOD]=p;		}	
else {	
	temp=hash->base[p->key%hash->MOD];
	hash->base[p->key%hash->MOD]=p;	
	p->next=temp;			} 				
}
}							


