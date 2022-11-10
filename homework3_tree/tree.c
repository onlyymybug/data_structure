#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 100
#define MAX_LENGTH 1024

typedef struct node
{
    char data;
    struct node*left;
    struct node*right;
}node;

typedef struct queue
{
    node data[MAX_LENGTH];
    int front,rear;
}queue;

queue*creat_queue()
{
    queue*q;
    q=(queue*)malloc(sizeof(queue));
    q->front=0;
    q->rear=0;
    return q;
}

int queue_is_empty(queue*q)
{
    return q->front==q->rear;
}

void enqueue(queue*q,node*n)
{
    if ((q->rear + 1) % MAX_LENGTH == q->front)
    {
        printf("Overflow\n");
        exit(1);
    }
    q->data[q->rear++] = *n;
    q->rear %= MAX_LENGTH;

}

node*dequeue(queue *q)
{
    node*n;
    if (q->front == q->rear) 
    {
        printf("Underflow\n");
        exit(1);
    }
    *n = q->data[q->front++];
    q->front %= MAX_LENGTH;
    return n;
}

int max(int a,int b)
{
    if(a>b)
        return a;
    else
        return b;
}

node*creat_node(char c)//新建节点
{
    node*node1=(node*)malloc(sizeof(node));
    node1->left=NULL;
    node1->data=c;
    node1->right=NULL;
    return node1;
}

node*creat_tree(char*level_order,char*in_order,int length)//返回根节点
{
    char subroot=*level_order;
    node*root=creat_node(subroot);
    if(in_order[0]!=subroot)
    {
        int i=0,m=0;
        for(;in_order[i]!=subroot&&i<length;i++);
        int new_length=i;
        char new_level_order[new_length],new_in_order[new_length];
        for(i=0;i<new_length;new_in_order[i]=in_order[i],i++);
        for(i=0;i<length;i++)
        {
            for(int j=0;j<new_length;j++)
            {
                if(level_order[i]==new_in_order[j])
                {
                    new_level_order[m]=new_in_order[j];
                    m++;
                    break;
                }
            }
        }
        root->left=creat_tree(new_level_order,new_in_order,new_length);
    }
    if(in_order[length-1]!=subroot)
    {
        int i=0,m=0;
        for(;in_order[i]!=subroot&&i<length;i++);
        int new_length=length-1-i;
        char new_level_order[new_length],new_in_order[new_length];
        for(i=0;i<new_length;new_in_order[i]=in_order[i+length-new_length],i++);
        for(i=0;i<length;i++)
        {
            for(int j=0;j<new_length;j++)
            {
                if(level_order[i]==new_in_order[j])
                {
                    new_level_order[m]=new_in_order[j];
                    m++;
                    break;
                }
            }
        }
        root->right=creat_tree(new_level_order,new_in_order,new_length);
    }
    return root;
}

char*pre_order(node*root,char*order)
{
    if(root!=NULL)
    {
        *order=root->data;
        order++;
        order=pre_order(root->left,order);
        order=pre_order(root->right,order);
    }
    return order;
}

char*in_order(node*root,char*order)
{
    if(root!=NULL)
    {
        order=in_order(root->left,order);
        *order=root->data;
        order++;
        order=in_order(root->right,order);
    }
    return order;
}

char*post_order(node*root,char*order)
{
    if(root!=NULL)
    {
        order=post_order(root->left,order);
        order=post_order(root->right,order);
        *order=root->data;
        order++;
    }
    return order;
}

char*level_order(node*root,char*order)
{
    queue*q=creat_queue();
    enqueue(q,root);
    for(;queue_is_empty(q)==0;)
    {
        root=dequeue(q);
        *order=root->data;
        order++;
        if(root->left!=NULL)
            enqueue(q,root->left);
        if(root->right!=NULL)
            enqueue(q,root->right);
    }
}

void print_tree(char*order,int length)//打印任意序列
{
    length--;
    for(int i=0;i<length;i++)
    {
        printf("%c",order[i]);
    }
    printf("%c\n",order[length]);
}

char*print_form(node*root,char*order,int num,char*mark)
{
    if(root!=NULL)
    {
        for(int i=0;i<=num;i++,printf("\t"));
        printf("%c(%s)\n",root->data,mark);
        *order=root->data;
        order++;
        num++;
        order=print_form(root->left,order,num,"left");
        order=print_form(root->right,order,num,"right");
    }
    return order;
}

void print_all(node*root,char*order,int length)
{
    pre_order(root,order);
    printf("pre order:");
    print_tree(order,length);
    in_order(root,order);
    printf("middle order:");
    print_tree(order,length);
    post_order(root,order);
    printf("post order:");
    print_tree(order,length);
    level_order(root,order);
    printf("level order:");
    print_tree(order,length);
    pre_order(root,order);
    printf("all tree:\n");
    print_form(root,order,0,"root");
}

int height(node*root,int h)
{
    if(root->left!=NULL)
    {
        if(root->right==NULL)
            h=1+height(root->left,h);
        else
            h=1+max(height(root->left,h),height(root->right,h));
    }
    else
    {
        if(root->right!=NULL)
            h=1+height(root->right,h);
    }
    return h;
}

node*copy(node*root)
{
    char order[MAX_SIZE],level[MAX_SIZE],in[MAX_SIZE];
    level_order(root,order);
    strcpy(level,order);
    in_order(root,order);
    strcpy(in,order);
    int length=strlen(level);
    return creat_tree(level,in,length);
}

void*exchange(node*root)
{
    node*temp=root->right;
    root->right=root->left;
    root->left=temp;
    if(root->left!=NULL)
        exchange(root->left);
    if(root->right!=NULL)
        exchange(root->right);
}

int proof(node*root,int x)
{
    if(root!=NULL)
    {
        if(x==0)
            return 0;
        else
        {
            if(root->left!=NULL)
            {
                x=root->data < root->left->data;
                if(x==0)
                    return 0;
                else
                    x=proof(root->left,x);
            }
            else if(root->right!=NULL)
            {
                x=root->data < root->right->data;
                if(x==0)
                    return 0;
                else
                    x=proof(root->left,x);
            }
            else 
                return 1;
        }
    }
    else
        return 1;
}

void destory_tree(node*root)
{
    if(root->left!=NULL)
    {
        destory_tree(root->left);
        root->left=NULL;
    }
    else if(root->right!=NULL)
    {
        destory_tree(root->right);
        root->right=NULL;
    }
    else
    {
        free(root);
        root=NULL;
    }
}

char*cut_E(node*root,char*order)
{
    if(root!=NULL)
    {
        *order=root->data;
        order++;
        if(root->left!=NULL&&root->left->data=='E')
        {
            destory_tree(root->left);
            root->left=NULL;
        }
        else if(root->right!=NULL&&root->right->data=='E')
        {
            destory_tree(root->right);
            root->right=NULL;
        }
        else
        {
            order=cut_E(root->left,order);
            order=cut_E(root->right,order);
        }
    }
    return order;
}

int main()
{
    char level_order[MAX_SIZE];
    char in_order[MAX_SIZE];
    char order[MAX_SIZE];
    scanf("%s",level_order);
    scanf("%s",in_order);
    int  length=strlen(level_order);
    node*root=creat_tree(level_order,in_order,length);
    print_all(root,order,length);
    printf("height: %d\n",height(root,1));
    if(proof(root,1)==1)
        printf("The root have such a property.\n");
    else
        printf("The root don't have such a property.\n");
    node*root1=copy(root);
    exchange(root1);
    printf("\nAfter copy and exchange:\n");
    print_all(root1,order,length);
    cut_E(root,order);
    pre_order(root,order);
    length=strlen(order);
    printf("\nAfter cut E:\n");
    print_all(root,order,length);
    destory_tree(root);
    destory_tree(root1);
    printf("\nThe tree root and root1 have been destroyed\n");
    system("pause");
    return 0;
}