#include<stdio.h>
#include<stdlib.h>
struct NODE
{
    char bracket;
    struct NODE*next;
};
struct NODE *create()
{
    struct NODE *head = (struct NODE *)malloc(sizeof(struct NODE));
    head->next = NULL;
    head->bracket = '0';
    return head;
}
void push_char(struct NODE*top,char letter)//·µ»ØÐÂµÄÕ»¶¥
{
        if(letter=='('||letter==')'||letter=='['||letter==']')
        {
            struct NODE*node=(struct NODE *)malloc(sizeof(struct NODE));
            node->next=NULL;
            node->bracket=letter;
            if(top->next==NULL)
            {
                top->next=node;
            }
            else
            {
                struct NODE*temp=top->next;
                top->next=node;
                node->next=temp;
            }
        }
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
    struct NODE*top=create(),*temp ;
    char letter,temp1,temp2;
    for(;letter!='\n';)
    {
        letter=getchar();
        push_char(top,letter);
        for(;;)
        {
            if(top->next!=NULL)
            {
                if(top->next->next!=NULL)
                {
                    temp1=top->next->bracket;
                    temp2=top->next->next->bracket;
                    if((temp1==')'&&temp2=='(')||(temp1==']'&&temp2=='['))
                    {
                        temp=top->next;
                        top->next=top->next->next->next;
                        temp->next->next=NULL;
                        destory(temp);
                    }
                    else
                    break;
                }
                else
                break;
            }
            else
            break;
        }
    }
    if(top->next==NULL)
    printf("yes\n");
    else
    printf("no\n");
    system("pause");
    return 0;
}