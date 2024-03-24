<<<<<<< HEAD
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>



#define RED      0    // 红色节点
#define BLACK    1    // 黑色节点
#define rb_is_red(r)  ((r)->color==RED)
 

typedef struct RBTreeNode {
	unsigned char color;        // 颜色(RED 或 BLACK)
	int    key;                    // 关键字(键值)
	struct RBTreeNode* left;    // 左孩子
	struct RBTreeNode* right;    // 右孩子
	struct RBTreeNode* parent;    // 父结点
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




static void RBTree_Build(Node** root, int a[], int n)				//建立红黑树
{
	int i;	
	for (i = 0; i < n; i++) {
		Node* newNode=NULL;
		newNode = (Node*)calloc(1, sizeof(Node));			//calloc会把申请空间所有字节置为0
		newNode->key = a[i];
		if (newNode) {					//空间申请成功则
			RBTree_Insert(root, &newNode);
			if (newNode)				//有效插入红黑树才考虑旋转调整
				RBTree_Rotate(root, newNode);
		}
	}

}




static void RBTree_Insert(Node** root, Node** newNode)
{
	if (NULL == *root){							//初始为空让新节点作为根节点
		*root = *newNode;
		(*newNode)->color = BLACK;					//根节点为黑色
	}
	else {
		Node* p = *root, * q = NULL;
		while (NULL != p) {
			if ((*newNode)->key == p->key) {		//途中若发现有相等的元素则去除此节点，清除之前申请的空间 
				printf("存在相等的值！\n");
				free(*newNode);
				*newNode = NULL;
				return;
			}											
			q = p;													
			if ((*newNode)->key < p->key)			//任有一个成立则寻找其插入位置 
				p = p->left;						//小往左 
			else
				p = p->right;						//大往右 
		}											//则已经找到待插入位置的父节点 
		(*newNode)->parent = q;						//此时q指向新节点的父节点
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
	while (newNode->parent &&(newNode->parent->color == RED) ) {		//其父节点存在且为红色，须调整
		parent = newNode->parent;										//获取父节点
		gparent = newNode->parent->parent;								//获取爷节点
		if (gparent&&(parent == gparent->left)) {						//爷节点存在且父节点为其左孩子
			uncle = gparent->right;										//其叔叔节点
			if (uncle && uncle->color == RED) {							//叔节点存在且为红色
				parent->color = BLACK;
				uncle->color = BLACK;
				gparent->color = RED;					
				newNode = gparent;				//则叔父染黑，爷节点成为新节点
				continue;						//再进入while循环
			}									//以下叔节点不存在或者存在但为黑色
			else if (newNode == parent->right) {		//新节点为父节点右孩子，需要调整两次，此括号调整一部分（LR型）
				gparent->left = newNode;
				newNode->parent = gparent;
				parent->right = newNode->left;			
				if(newNode->left)
				newNode->left->parent = parent;			//这里注意父子指向是相互的，不能父指向子而子未指向父
				newNode->left = parent;
				parent->parent = newNode;				//以上调换父子角色
				temp = parent;							//往下换指向位置以便于与下一部分代码衔接
				parent = newNode;
				newNode = temp;
			}											//调整剩余部分。如果是左孩子，只需进行以下操作调整（LL型）
				parent->parent = gparent->parent;
				if (gparent->parent) {					//若曾祖父节点存在
					if(gparent->parent->left==gparent)	//确定爷节点是曾祖父节点的左孩子还是右孩子
						gparent->parent->left = parent;
					else
						gparent->parent->right = parent;
				}					
				gparent->parent = parent;
				gparent->left = parent->right;
				if(parent->right)						//若兄弟存在
				parent->right->parent = gparent;		//注意父子指向是相互的
				parent->right = gparent;				//以上让父节点与爷节点角色互换
				parent->color = BLACK;
				gparent->color = RED;			
		}
		else if(gparent){								//爷节点存在且父节点为其右孩子
			uncle = gparent->left;
			if (uncle && uncle->color == RED) {			//叔节点存在且为红色
				parent->color = BLACK;
				uncle->color = BLACK;
				gparent->color = RED;
				newNode = gparent;						//则叔父染黑，爷节点成为新节点
				continue;								//再进入while循环
			}											//以下叔节点不存在或者存在但为黑色
			else if (newNode == parent->left) {			//新节点为父节点左孩子，需要调整两次，此括号调整一部分（RL型）
				gparent->right = newNode;
				newNode->parent = gparent;
				parent->left = newNode->right;
				if(newNode->right)
				newNode->right->parent = parent;		//这里注意父子指向是相互的，不能父指向子而子未指向父
				newNode->right = parent;
				parent->parent = newNode;				//以上调换父子角色
				temp = parent;							//往下换指向位置以便于与下一部分代码衔接
				parent = newNode;
				newNode = temp;
			}											//调整剩余部分。如果是左孩子，只需进行以下操作调整（RR型）
				parent->parent = gparent->parent;
				if (gparent->parent) {					//若曾祖父节点存在
					if (gparent->parent->left == gparent)		//确定爷节点是曾祖父节点的左孩子还是右孩子
						gparent->parent->left = parent;
					else
						gparent->parent->right = parent;
				}
				gparent->parent = parent;
				gparent->right = parent->left;
				if(parent->left)							//若兄弟存在
				parent->left->parent = gparent;				//注意父子指向是相互的
				parent->left = gparent;						//以上让父节点与爷节点角色互换
				parent->color = BLACK;
				gparent->color = RED;
		}
	}
	while (newNode) {
		*root= newNode;
		newNode = newNode->parent;
	}						//调整后根节点可能发生变化，此循环找回根节点
	if (NULL == (*root)->parent)				
		(*root)->color = BLACK;			//将根节点染黑
}




static void rbtree_print(Node* node, int  key, int direction)				//前序遍历打印
{
	if (NULL != node)
	{
		if (0 == direction)    // node是根节点
			printf("%2d(%s) is root\n", node->key, rb_is_red(node) ? "R" : "B");
		else                // node是分支节点
			printf("%2d(%s) is %2d's %6s child\n", node->key, rb_is_red(node) ? "R" : "B", key, direction == 1 ? "right" : "left");

		rbtree_print(node->left, node->key, -1);		//-1给予判断是左孩子
		rbtree_print(node->right, node->key, 1);	
	}
}

=======
#include<stdio.h>						
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>



#define RED      0    // 红色节点
#define BLACK    1    // 黑色节点
#define rb_is_red(r)  ((r)->color==RED)
 

typedef struct RBTreeNode {
	unsigned char color;        // 颜色(RED 或 BLACK)
	int    key;                    // 关键字(键值)
	struct RBTreeNode* left;    // 左孩子
	struct RBTreeNode* right;    // 右孩子
	struct RBTreeNode* parent;    // 父结点
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




static void RBTree_Build(Node** root, int a[], int n)				//建立红黑树
{
	int i;	
	for (i = 0; i < n; i++) {
		Node* newNode=NULL;
		newNode = (Node*)calloc(1, sizeof(Node));			//calloc会把申请空间所有字节置为0
		newNode->key = a[i];
		if (newNode) {					//空间申请成功则
			RBTree_Insert(root, &newNode);
			if (newNode)				//有效插入红黑树才考虑旋转调整
				RBTree_Rotate(root, newNode);
		}
	}

}




static void RBTree_Insert(Node** root, Node** newNode)
{
	if (NULL == *root){							//初始为空让新节点作为根节点
		*root = *newNode;
		(*newNode)->color = BLACK;					//根节点为黑色
	}
	else {
		Node* p = *root, * q = NULL;
		while (NULL != p) {
			if ((*newNode)->key == p->key) {		//途中若发现有相等的元素则去除此节点，清除之前申请的空间 
				printf("存在相等的值！\n");
				free(*newNode);
				*newNode = NULL;
				return;
			}											
			q = p;													
			if ((*newNode)->key < p->key)			//任有一个成立则寻找其插入位置 
				p = p->left;						//小往左 
			else
				p = p->right;						//大往右 
		}											//则已经找到待插入位置的父节点 
		(*newNode)->parent = q;						//此时q指向新节点的父节点
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
	while (newNode->parent &&(newNode->parent->color == RED) ) {		//其父节点存在且为红色，须调整
		parent = newNode->parent;										//获取父节点
		gparent = newNode->parent->parent;								//获取爷节点
		if (gparent&&(parent == gparent->left)) {						//爷节点存在且父节点为其左孩子
			uncle = gparent->right;										//其叔叔节点
			if (uncle && uncle->color == RED) {							//叔节点存在且为红色
				parent->color = BLACK;
				uncle->color = BLACK;
				gparent->color = RED;					
				newNode = gparent;				//则叔父染黑，爷节点成为新节点
				continue;						//再进入while循环
			}									//以下叔节点不存在或者存在但为黑色
			else if (newNode == parent->right) {		//新节点为父节点右孩子，需要调整两次，此括号调整一部分（LR型）
				gparent->left = newNode;
				newNode->parent = gparent;
				parent->right = newNode->left;			
				if(newNode->left)
				newNode->left->parent = parent;			//这里注意父子指向是相互的，不能父指向子而子未指向父
				newNode->left = parent;
				parent->parent = newNode;				//以上调换父子角色
				temp = parent;							//往下换指向位置以便于与下一部分代码衔接
				parent = newNode;
				newNode = temp;
			}											//调整剩余部分。如果是左孩子，只需进行以下操作调整（LL型）
				parent->parent = gparent->parent;
				if (gparent->parent) {					//若曾祖父节点存在
					if(gparent->parent->left==gparent)	//确定爷节点是曾祖父节点的左孩子还是右孩子
						gparent->parent->left = parent;
					else
						gparent->parent->right = parent;
				}					
				gparent->parent = parent;
				gparent->left = parent->right;
				if(parent->right)						//若兄弟存在
				parent->right->parent = gparent;		//注意父子指向是相互的
				parent->right = gparent;				//以上让父节点与爷节点角色互换
				parent->color = BLACK;
				gparent->color = RED;			
		}
		else if(gparent){								//爷节点存在且父节点为其右孩子
			uncle = gparent->left;
			if (uncle && uncle->color == RED) {			//叔节点存在且为红色
				parent->color = BLACK;
				uncle->color = BLACK;
				gparent->color = RED;
				newNode = gparent;						//则叔父染黑，爷节点成为新节点
				continue;								//再进入while循环
			}											//以下叔节点不存在或者存在但为黑色
			else if (newNode == parent->left) {			//新节点为父节点左孩子，需要调整两次，此括号调整一部分（RL型）
				gparent->right = newNode;
				newNode->parent = gparent;
				parent->left = newNode->right;
				if(newNode->right)
				newNode->right->parent = parent;		//这里注意父子指向是相互的，不能父指向子而子未指向父
				newNode->right = parent;
				parent->parent = newNode;				//以上调换父子角色
				temp = parent;							//往下换指向位置以便于与下一部分代码衔接
				parent = newNode;
				newNode = temp;
			}											//调整剩余部分。如果是左孩子，只需进行以下操作调整（RR型）
				parent->parent = gparent->parent;
				if (gparent->parent) {					//若曾祖父节点存在
					if (gparent->parent->left == gparent)		//确定爷节点是曾祖父节点的左孩子还是右孩子
						gparent->parent->left = parent;
					else
						gparent->parent->right = parent;
				}
				gparent->parent = parent;
				gparent->right = parent->left;
				if(parent->left)							//若兄弟存在
				parent->left->parent = gparent;				//注意父子指向是相互的
				parent->left = gparent;						//以上让父节点与爷节点角色互换
				parent->color = BLACK;
				gparent->color = RED;
		}
	}
	while (newNode) {
		*root= newNode;
		newNode = newNode->parent;
	}						//调整后根节点可能发生变化，此循环找回根节点
	if (NULL == (*root)->parent)				
		(*root)->color = BLACK;			//将根节点染黑
}




static void rbtree_print(Node* node, int  key, int direction)				//前序遍历打印
{
	if (NULL != node)
	{
		if (0 == direction)    // node是根节点
			printf("%2d(%s) is root\n", node->key, rb_is_red(node) ? "R" : "B");
		else                // node是分支节点
			printf("%2d(%s) is %2d's %6s child\n", node->key, rb_is_red(node) ? "R" : "B", key, direction == 1 ? "right" : "left");

		rbtree_print(node->left, node->key, -1);		//-1给予判断是左孩子
		rbtree_print(node->right, node->key, 1);	
	}
}

>>>>>>> 7edc0a04ff39d0dd7f2435bd378bcebed8945e78
