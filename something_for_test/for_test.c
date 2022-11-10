#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
//层序遍历二叉树
typedef struct TreeNode//树节点
{
	struct TreeNode* left,* right;
	char data;
}TreeNode, * pTreeNode;

typedef struct QueueNode//队列节点
{
	pTreeNode data;
	QueueNode* next;
}QueueNode, * pQueueNode;

typedef struct Queue//队列
{
	pQueueNode front,rear;
}Queue, * pQueue;

void createTree(pTreeNode& t)//创建树,&引用已经定义的t
{
	char ch;
	scanf_s("%c",&ch,sizeof(ch));
	if (ch == '*')//如果输入*则为空
	{
		t = NULL;
	}
	else
	{
		t = new TreeNode;
		t->data = ch;
		createTree(t->left);//递归
		createTree(t->right);
	}
}

pQueue initQ(pQueue pq)//建立只有头结点的队列
{
	pq->front = (pQueueNode)malloc(sizeof(QueueNode));
	if (pq->front==NULL)//判断内存分配是否成功
	{
		printf("内存分配不成功！");
	}
	else
	{
		pq->front->next = NULL;//队列的front和rear的next初始化为空
		pq->rear = pq->front;
		return pq;
	}
}

void enqueue(pQueue pq, pTreeNode t)//把二叉树的数据取出放入队列
{
	pQueueNode pNew = new QueueNode;
	pNew->data = t;//二叉树的数据存入队列
	pNew->next = NULL;
	pq->rear->next = pNew;//尾插法建立连接
	pq->rear = pNew;//rear更新
}

pTreeNode dequeue(pQueue pq)//出队：删除队列第一个元素
{
	pQueueNode pTemp= (pQueueNode)malloc(sizeof(QueueNode));
	pTemp = pq->front->next;
	if (pTemp->next == NULL)//只剩下1个节点（不含队列空的头结点）
	{
		pq->rear = pq->front;
	}
	else{
		pq->front->next = pTemp->next;//front+1（从指向第1个非空节点改为指向第2个节点）
	}
	pTreeNode x;
	x= pTemp->data;//x为队列第一个元素的data
	free(pTemp);
	return x;
}

void LevelOrderBiTree(pTreeNode t)//层序输出
{
	pQueue pq= (pQueue)malloc(sizeof(Queue));
	pq = initQ(pq);
	enqueue(pq,t);//取出二叉树的根节点，子节点存入队列
	while (pq->rear != pq->front)//当队列不为空
	{
		pTreeNode x = dequeue(pq);//x用于输出队列弹出元素的数据
		printf("%c", x->data);
		if (x->left!=NULL)
		{
			enqueue(pq, x->left);//递归左节点
		}
		if (x->right!=NULL)
		{
			enqueue(pq, x->right);//递归右节点
		}
	}
}
int main() 
{
	pTreeNode t;
	printf("请输入二叉树数据:");
	createTree(t); 
	printf("层序遍历如下:");
	LevelOrderBiTree(t);
    system("pause");
	return 0;
}