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
	printf("��ϣ�����ݵ�%dλ������%d\n",i,hash.base[i].key);
}	
	return 0;
}



void hashcreat(hashtable*hash,int list[])		
{
	int i,j,k;
	int b[maxsize];			//��ų�ͻ�������� 
	printf("�������ĳ���\n");
	scanf("%d",&hash->length);
	hash->base=(elem*)malloc(hash->length*sizeof(elem));			//�����һ��ʼ�ã���ʾ��һ��ʧ�� 
	printf("������MOD��ֵ\n");
	scanf("%d",&hash->MOD);
	j=1;
for(i=1;i<maxsize-1;i+=2){							//ƽ��̽�� 
	b[i]=j*j;
	b[i+1]=-b[i];
	j++;	}
for(i=0;i<hash->length;i++){	
	hash->base[i].key=0;					//�ؼ��� 
	hash->base[i].flag=0;		}			//�����ĳԪ���Ƿ��߼���ɾ�� 
		
		
for(i=0;i<maxsize;i++){
if(hash->base[list[i]%hash->MOD].flag==0){			//����λ�� 
	hash->base[list[i]%hash->MOD].key=list[i];
	hash->base[list[i]%hash->MOD].flag=1;	}	
else {	
	for(k=1;k<=maxsize;k++){
	if(hash->base[(list[i]%hash->MOD+b[k])%hash->length].flag==0){	/*����Ϊ��ԭ��Ӧ�ڵ�λ�û����� 
	�ټ���������ģ��	*/
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
	printf("��ϣ�����ݵ�%dλ������%d\n",i,hash.base[i].key);
}	
	return 0;
}



void hashcreat(hashtable*hash,int list[])		
{
	int i,j,k;
	int b[maxsize];			//��ų�ͻ�������� 
	printf("�������ĳ���\n");
	scanf("%d",&hash->length);
	hash->base=(elem*)malloc(hash->length*sizeof(elem));			//�����һ��ʼ�ã���ʾ��һ��ʧ�� 
	printf("������MOD��ֵ\n");
	scanf("%d",&hash->MOD);
	j=1;
for(i=1;i<maxsize-1;i+=2){							//ƽ��̽�� 
	b[i]=j*j;
	b[i+1]=-b[i];
	j++;	}
for(i=0;i<hash->length;i++){	
	hash->base[i].key=0;					//�ؼ��� 
	hash->base[i].flag=0;		}			//�����ĳԪ���Ƿ��߼���ɾ�� 
		
		
for(i=0;i<maxsize;i++){
if(hash->base[list[i]%hash->MOD].flag==0){			//����λ�� 
	hash->base[list[i]%hash->MOD].key=list[i];
	hash->base[list[i]%hash->MOD].flag=1;	}	
else {	
	for(k=1;k<=maxsize;k++){
	if(hash->base[(list[i]%hash->MOD+b[k])%hash->length].flag==0){	/*����Ϊ��ԭ��Ӧ�ڵ�λ�û����� 
	�ټ���������ģ��	*/
	hash->base[(list[i]%hash->MOD+b[k])%hash->length].key=list[i];
	hash->base[(list[i]%hash->MOD+b[k])%hash->length].flag=1;
	break;		} 				
}
}						
}		
}


>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
