#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct NODE
{
    int data;
    struct NODE *next;
};
struct NODE *create()
{
    struct NODE *head = (struct NODE *)malloc(sizeof(struct NODE));
    head->next = NULL;
    head->data = 0;
    return head;
}
void insert(struct NODE *head, int num) //插入
{
    int a, b;
    struct NODE *p = head, *temp;
    struct NODE *node = (struct NODE *)malloc(sizeof(struct NODE));
    node->data = num;
    node->next = NULL;
    for (;; p = p->next)
    {
        if (p->next == NULL) //空表
        {
            p->next = node;
            break;
        }
        else if (num <= p->next->data) //
        {
            temp = p->next;
            p->next = node;
            node->next = temp;
            break;
        }
    }
    head->data++;
}
void delete_new(struct NODE *head, int num) //删除指定元素
{
    struct NODE *p = head, *temp;
    for (; p->next != NULL;)
    {
        if (p->next->data == num)
        {
            temp = p->next;
            p->next = p->next->next;
            free(temp);
            head->data--;
        }
        else
        {
            p = p->next;
        }
    }
}
void revert(struct NODE *head) //逆转
{
    struct NODE *p = head, *another, *temp1, *temp2;
    another = NULL;
    for (int i = 1; i <= head->data; i++)
    {
        temp1 = p->next;
        p->next = p->next->next;
        temp1->next = NULL;
        temp2 = another;
        another = temp1;
        another->next = temp2;
    }
    p->next = another;
}
void dump(struct NODE *head) //打印
{
    struct NODE *p = head;
    printf("{ ");
    for (; p->next != NULL; p = p->next)
    {
        printf("%d ", p->next->data);
    }
    printf("}\n");
}
void verify(int n) //检验是否顺序
{
    if (n % 2 == 0)
        printf("VERIFY: OK\n");
    else
        printf("VERIFY: ERROR\n");
}
int count(struct NODE *head) //计数
{
    printf("COUNT: %d\n", head->data);
}
void sum(struct NODE *head) //求和
{
    struct NODE *p = head;
    int sumx = 0;
    for (; p->next != NULL; p = p->next)
    {
        sumx += p->next->data;
    }
    printf("SUM; %d\n", sumx);
}
void destory(struct NODE *head)
{
    struct NODE *temp;
    for (; head != NULL;)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}
int main()
{
    int num;
    int times = 0;
    char s[10];
    struct NODE *head;
    for (;;)
    {
        scanf("%s", &s);
        if (strcmp(s, "create") == 0)
        {
            head = create();
        }
        else if (strcmp(s, "insert") == 0)
        {
            scanf("%d", &num);
            insert(head, num);
        }
        else if (strcmp(s, "delete") == 0)
        {
            scanf("%d", &num);
            delete_new(head, num);
        }
        else if (strcmp(s, "revert") == 0)
        {
            revert(head);
            times++;
        }
        else if (strcmp(s, "dump") == 0)
        {
            dump(head);
        }
        else if (strcmp(s, "verify") == 0)
        {
            verify(times);
        }
        else if (strcmp(s, "count") == 0)
        {
            count(head);
        }
        else if (strcmp(s, "sum") == 0)
        {
            sum(head);
        }
        else if (strcmp(s, "destroy") == 0)
        {
            destory(head);
        }
        else if (strcmp(s, "bye") == 0)
        {
            system("pause");
            return 0;
        }
        else
        {
            printf("Bad command\n");
        }
    }
}