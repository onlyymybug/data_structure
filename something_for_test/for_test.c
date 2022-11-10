#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
//�������������
typedef struct TreeNode//���ڵ�
{
	struct TreeNode* left,* right;
	char data;
}TreeNode, * pTreeNode;

typedef struct QueueNode//���нڵ�
{
	pTreeNode data;
	QueueNode* next;
}QueueNode, * pQueueNode;

typedef struct Queue//����
{
	pQueueNode front,rear;
}Queue, * pQueue;

void createTree(pTreeNode& t)//������,&�����Ѿ������t
{
	char ch;
	scanf_s("%c",&ch,sizeof(ch));
	if (ch == '*')//�������*��Ϊ��
	{
		t = NULL;
	}
	else
	{
		t = new TreeNode;
		t->data = ch;
		createTree(t->left);//�ݹ�
		createTree(t->right);
	}
}

pQueue initQ(pQueue pq)//����ֻ��ͷ���Ķ���
{
	pq->front = (pQueueNode)malloc(sizeof(QueueNode));
	if (pq->front==NULL)//�ж��ڴ�����Ƿ�ɹ�
	{
		printf("�ڴ���䲻�ɹ���");
	}
	else
	{
		pq->front->next = NULL;//���е�front��rear��next��ʼ��Ϊ��
		pq->rear = pq->front;
		return pq;
	}
}

void enqueue(pQueue pq, pTreeNode t)//�Ѷ�����������ȡ���������
{
	pQueueNode pNew = new QueueNode;
	pNew->data = t;//�����������ݴ������
	pNew->next = NULL;
	pq->rear->next = pNew;//β�巨��������
	pq->rear = pNew;//rear����
}

pTreeNode dequeue(pQueue pq)//���ӣ�ɾ�����е�һ��Ԫ��
{
	pQueueNode pTemp= (pQueueNode)malloc(sizeof(QueueNode));
	pTemp = pq->front->next;
	if (pTemp->next == NULL)//ֻʣ��1���ڵ㣨�������пյ�ͷ��㣩
	{
		pq->rear = pq->front;
	}
	else{
		pq->front->next = pTemp->next;//front+1����ָ���1���ǿսڵ��Ϊָ���2���ڵ㣩
	}
	pTreeNode x;
	x= pTemp->data;//xΪ���е�һ��Ԫ�ص�data
	free(pTemp);
	return x;
}

void LevelOrderBiTree(pTreeNode t)//�������
{
	pQueue pq= (pQueue)malloc(sizeof(Queue));
	pq = initQ(pq);
	enqueue(pq,t);//ȡ���������ĸ��ڵ㣬�ӽڵ�������
	while (pq->rear != pq->front)//�����в�Ϊ��
	{
		pTreeNode x = dequeue(pq);//x����������е���Ԫ�ص�����
		printf("%c", x->data);
		if (x->left!=NULL)
		{
			enqueue(pq, x->left);//�ݹ���ڵ�
		}
		if (x->right!=NULL)
		{
			enqueue(pq, x->right);//�ݹ��ҽڵ�
		}
	}
}
int main() 
{
	pTreeNode t;
	printf("���������������:");
	createTree(t); 
	printf("�����������:");
	LevelOrderBiTree(t);
    system("pause");
	return 0;
}