<<<<<<< HEAD
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





int main()
{
	Node* root = NULL;
	//int a[] = { 16,9,5,3,52,35,61 };
	int a[] = { 10, 40, 30, 60, 90, 70, 20, 50, 80,65,66,45,77,99,82,23,55,88,33,47 };
	RBTree_Build(&root, a, sizeof(a) / sizeof(a[0]));
	rbtree_print(root, root->key, 0);
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

=======
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





int main()
{
	Node* root = NULL;
	//int a[] = { 16,9,5,3,52,35,61 };
	int a[] = { 10, 40, 30, 60, 90, 70, 20, 50, 80,65,66,45,77,99,82,23,55,88,33,47 };
	RBTree_Build(&root, a, sizeof(a) / sizeof(a[0]));
	rbtree_print(root, root->key, 0);
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

>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
