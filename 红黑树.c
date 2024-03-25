//--------------------------Ͷ����------------ɾ����������------
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>



#define RED      0    // ��ɫ�ڵ�
#define BLACK    1    // ��ɫ�ڵ�
#define rb_is_red(r)  ((r)->color==RED)
 

typedef struct RBTreeNode {
	unsigned char color;        // ��ɫ(RED �� BLACK)
	int    key;                    // �ؼ���(��ֵ)
	struct RBTreeNode* left;    // ����
	struct RBTreeNode* right;    // �Һ���
	struct RBTreeNode* parent;    // �����
}Node;

static void RBTree_Build(Node** root, int a[], int n);
static void RBTree_Insert(Node** root, Node** newNode);
static void RBTree_Rotate(Node** root, Node* newNode);
static void rbtree_print(Node* node, int  key, int direction);
static void rbtree_Delete(Node** root);




int main()
{
	Node* root = NULL;
	//int a[] = { 16,9,5,3,52,35,61 };
	int a[] = { 10, 40, 30, 60, 90, 70, 20, 50, 80,65,66,45,77,99,82,23,55,88,33,47 };
	RBTree_Build(&root, a, sizeof(a) / sizeof(a[0]));
	rbtree_print(root, root->key, 0);
	rbtree_Delete(&root);
	return 0;
}




static void RBTree_Build(Node** root, int a[], int n)				//���������
{
	int i;	
	for (i = 0; i < n; i++) {
		Node* newNode=NULL;
		newNode = (Node*)calloc(1, sizeof(Node));			//calloc�������ռ������ֽ���Ϊ0
		newNode->key = a[i];
		if (newNode) {					//�ռ�����ɹ���
			RBTree_Insert(root, &newNode);
			if (newNode)				//��Ч���������ſ�����ת����
				RBTree_Rotate(root, newNode);
		}
	}

}




static void RBTree_Insert(Node** root, Node** newNode)
{
	if (NULL == *root){							//��ʼΪ�����½ڵ���Ϊ���ڵ�
		*root = *newNode;
		(*newNode)->color = BLACK;					//���ڵ�Ϊ��ɫ
	}
	else {
		Node* p = *root, * q = NULL;
		while (NULL != p) {
			if ((*newNode)->key == p->key) {		//;������������ȵ�Ԫ����ȥ���˽ڵ㣬���֮ǰ����Ŀռ� 
				printf("������ȵ�ֵ��\n");
				free(*newNode);
				*newNode = NULL;
				return;
			}											
			q = p;													
			if ((*newNode)->key < p->key)			//����һ��������Ѱ�������λ�� 
				p = p->left;						//С���� 
			else
				p = p->right;						//������ 
		}											//���Ѿ��ҵ�������λ�õĸ��ڵ� 
		(*newNode)->parent = q;						//��ʱqָ���½ڵ�ĸ��ڵ�
		if ((*newNode)->key < q->key)
			q->left = *newNode;
		else 	q->right = *newNode;
	}
}

static void RBTree_Rotate(Node** root, Node* newNode)
{
	Node* parent, * gparent;
	Node* temp = NULL;
	Node* uncle = NULL;
	while (newNode->parent &&(newNode->parent->color == RED) ) {		//�丸�ڵ������Ϊ��ɫ�������
		parent = newNode->parent;										//��ȡ���ڵ�
		gparent = newNode->parent->parent;								//��ȡү�ڵ�
		if (gparent&&(parent == gparent->left)) {						//ү�ڵ�����Ҹ��ڵ�Ϊ������
			uncle = gparent->right;										//������ڵ�
			if (uncle && uncle->color == RED) {							//��ڵ������Ϊ��ɫ
				parent->color = BLACK;
				uncle->color = BLACK;
				gparent->color = RED;					
				newNode = gparent;				//���常Ⱦ�ڣ�ү�ڵ��Ϊ�½ڵ�
				continue;						//�ٽ���whileѭ��
			}									//������ڵ㲻���ڻ��ߴ��ڵ�Ϊ��ɫ
			else if (newNode == parent->right) {		//�½ڵ�Ϊ���ڵ��Һ��ӣ���Ҫ�������Σ������ŵ���һ���֣�LR�ͣ�
				gparent->left = newNode;
				newNode->parent = gparent;
				parent->right = newNode->left;			
				if(newNode->left)
				newNode->left->parent = parent;			//����ע�⸸��ָ�����໥�ģ����ܸ�ָ���Ӷ���δָ��
				newNode->left = parent;
				parent->parent = newNode;				//���ϵ������ӽ�ɫ
				temp = parent;							//���»�ָ��λ���Ա�������һ���ִ����ν�
				parent = newNode;
				newNode = temp;
			}											//����ʣ�ಿ�֡���������ӣ�ֻ��������²���������LL�ͣ�
				parent->parent = gparent->parent;
				if (gparent->parent) {					//�����游�ڵ����
					if(gparent->parent->left==gparent)	//ȷ��ү�ڵ������游�ڵ�����ӻ����Һ���
						gparent->parent->left = parent;
					else
						gparent->parent->right = parent;
				}					
				gparent->parent = parent;
				gparent->left = parent->right;
				if(parent->right)						//���ֵܴ���
				parent->right->parent = gparent;		//ע�⸸��ָ�����໥��
				parent->right = gparent;				//�����ø��ڵ���ү�ڵ��ɫ����
				parent->color = BLACK;
				gparent->color = RED;			
		}
		else if(gparent){								//ү�ڵ�����Ҹ��ڵ�Ϊ���Һ���
			uncle = gparent->left;
			if (uncle && uncle->color == RED) {			//��ڵ������Ϊ��ɫ
				parent->color = BLACK;
				uncle->color = BLACK;
				gparent->color = RED;
				newNode = gparent;						//���常Ⱦ�ڣ�ү�ڵ��Ϊ�½ڵ�
				continue;								//�ٽ���whileѭ��
			}											//������ڵ㲻���ڻ��ߴ��ڵ�Ϊ��ɫ
			else if (newNode == parent->left) {			//�½ڵ�Ϊ���ڵ����ӣ���Ҫ�������Σ������ŵ���һ���֣�RL�ͣ�
				gparent->right = newNode;
				newNode->parent = gparent;
				parent->left = newNode->right;
				if(newNode->right)
				newNode->right->parent = parent;		//����ע�⸸��ָ�����໥�ģ����ܸ�ָ���Ӷ���δָ��
				newNode->right = parent;
				parent->parent = newNode;				//���ϵ������ӽ�ɫ
				temp = parent;							//���»�ָ��λ���Ա�������һ���ִ����ν�
				parent = newNode;
				newNode = temp;
			}											//����ʣ�ಿ�֡���������ӣ�ֻ��������²���������RR�ͣ�
				parent->parent = gparent->parent;
				if (gparent->parent) {					//�����游�ڵ����
					if (gparent->parent->left == gparent)		//ȷ��ү�ڵ������游�ڵ�����ӻ����Һ���
						gparent->parent->left = parent;
					else
						gparent->parent->right = parent;
				}
				gparent->parent = parent;
				gparent->right = parent->left;
				if(parent->left)							//���ֵܴ���
				parent->left->parent = gparent;				//ע�⸸��ָ�����໥��
				parent->left = gparent;						//�����ø��ڵ���ү�ڵ��ɫ����
				parent->color = BLACK;
				gparent->color = RED;
		}
	}
	while (newNode) {
		*root= newNode;
		newNode = newNode->parent;
	}						//��������ڵ���ܷ����仯����ѭ���һظ��ڵ�
	if (NULL == (*root)->parent)				
		(*root)->color = BLACK;			//�����ڵ�Ⱦ��
}




static void rbtree_print(Node* node, int  key, int direction)				//ǰ�������ӡ
{
	if (NULL != node)
	{
		if (0 == direction)    // node�Ǹ��ڵ�
			printf("%2d(%s) is root\n", node->key, rb_is_red(node) ? "R" : "B");
		else                // node�Ƿ�֧�ڵ�
			printf("%2d(%s) is %2d's %6s child\n", node->key, rb_is_red(node) ? "R" : "B", key, direction == 1 ? "right" : "left");

		rbtree_print(node->left, node->key, -1);		//-1�����ж�������
		rbtree_print(node->right, node->key, 1);	
	}
}




//-----------δ��֮��------------------
static void rbtree_Delete(Node** root)
{	
	int x;
	Node *p=*root,*q=NULL, *parent,*gparent,*node;
	while (printf("������Ҫɾ���Ĺؼ���"), scanf("%d", &x) != EOF) {
		while (x != p->key) {
			if (x < p->key)			//����һ��������Ѱ�������λ�� 
				p = p->left;						//С���� 
			else
				p = p->right;						//������ 
		}
		node = p;									//ָ��ǰӦɾ���ڵ�
		if (NULL == node)
			printf("���в����ڴ˹ؼ���");
		else {
			while (node){
				if ((node->left) && (node->right)) {
					p = p->left;					//�������������ҽڵ�
					while (NULL != p) {
						q = p;
						p = p->right;
					}				//��ʱqָ��ɾ���ڵ�����������ҽڵ�
					node->key = q->key;
					node = q;			//��nodeָ��������
				}							//����nodeֻ����һ���ӽڵ���߲������ӽڵ�
				parent = node->parent;
				gparent = node->parent->parent;
				if (RED == node->color) {			//����������洦��node��Ϊ�죬������ָ��ΪNULL������ֱ��ɾ
					if (node->parent->left == node)
						node->parent->left = NULL;
					else
						node->parent->right = NULL;
					free(node);
					node = NULL;					//�ɹ�ɾ�����˳�ѭ��
				}
				else {						//��ʱnodeΪ��ɫ�������ܴ��ڵĺ���Ϊ��ɫ�Ļ���Ҳ���ܲ������ӽڵ㣩
					if (node->left && node->left->color == RED) {
						node->key = node->left->key;
						free(node->left);
						node->left = NULL;
						node = NULL;			//�ɹ�ɾ�����˳�ѭ��
					}
					else if (node->right && node->right->color == RED) {
						node->key = node->right->key;
						free(node->right);
						node->right = NULL;
						node = NULL;			//�ɹ�ɾ�����˳�ѭ��
					}
					else {			//��ʱnode����ָ���Ϊ�ջ����ӽڵ�Ϊ��ɫ����nodeΪ��ɫ
						if (node == parent->left) {
							Node* other = parent->right;			//��Ȼ����
							if ( other->color == RED) {				//���ζ�
								free(node);
								if(node->left)
									parent->left = node->left;
								else
									parent->left = node->right;
								node = parent->left;
								other->parent = gparent;
								if (parent == gparent->left)
									gparent->left = other;
								else
									gparent->right = other;
								parent->right = other->left;
								if (other->left)
									other->left->parent = parent;
								parent->parent = other;
								other->left = parent;
								other->color = BLACK;
								parent->color = RED;
								other = parent->right;
							}				//����
							if ((!other->left || other->left->color==BLACK) &&
								(!other->right || other->right->color==BLACK)){//�����������ġ���ʱ��parent���Ǹ��ڵ���úڸ߲�һ��
								parent->color = BLACK;
								other->color = RED;
								node = parent;
							}
							else {					//���ٴ���һ���ӽڵ�
								if (other->left) {				//������
									other->left -> parent = other->parent;
									other -> parent->right = other->left;
									other->left = other->left->right;
									if (other->left->right)
										other->left->right->parent = other;
									other->parent = parent->right;
									parent->right->right = other;
									other->color = RED;
									parent->right->color = BLACK;
									other = parent->right;
								}
								other->parent = parent->parent;				//������
								if (parent == parent->parent->left)
									parent->parent->left = other;
								else
									parent->parent->right = other;
								parent->parent = other;
								parent->right = other->left;
								if (other->left)
									other->left->parent = parent;
								other->left = parent;
								other->color = parent->color;
								parent->color = BLACK;
								free(node);
								node = NULL;
							}
						}
						else {
							Node* other = parent->left;			//��Ȼ����
							if (other->color == RED) {
								free(node);
								parent->right = node->right;
								other->parent = gparent;
								if (parent == gparent->left)
									gparent->left = other;
								else
									gparent->right = other;
								parent->left = other->right;
								if (other->right)
									other->right->parent = parent;
								parent->parent = other;
								other->right = parent;
								other->color = BLACK;
								parent->color = RED;
								other = parent->left;
							}
							if (other->left == NULL && other->right == NULL) {
								parent->color = BLACK;
								other->color = RED;
								node = parent;
							}
							else {					//���ٴ���һ���ӽڵ�
								if (other->right) {
									other->right->parent = other->parent;
									other->parent->left = other->right;
									other->right = other->right->left;
									if (other->right->left)
										other->right->left->parent = other;
									other->parent = parent->left;
									parent->left->left = other;
									other->color = RED;
									parent->left->color = BLACK;
									other = parent->left;
								}
								other->parent = parent->parent;
								if (parent == parent->parent->left)
									parent->parent->left = other;
								else
									parent->parent->right = other;
								parent->parent = other;
								parent->left = other->right;
								if (other->right)
									other->right->parent = parent;
								other->right = parent;
								other->color = parent->color;
								parent->color = BLACK;
								free(node);
								node = NULL;
							}
						}
					}
				}
			}
		}
		rbtree_print(*root, (*root)->key, 0);
	}
}