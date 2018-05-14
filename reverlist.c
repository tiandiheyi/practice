#include <unistd.h>
#include <stdio.h>
#include <string.h>

struct list
{
    struct list *next;
    int data;
};

struct list head = {NULL, 0};

struct list listArray[] = 
{
    {NULL, 1},
    {NULL, 2},
    {NULL, 3},
    {NULL, 4},
    {NULL, 5},
    {NULL, 6},
    {NULL, 7},
    {NULL, 8},
    {NULL, 9},
};

void showList(struct list *head)
{
    struct list *cur;
    if(NULL == head)
    {
        printf("NULL LIST\r\n");
        return ;
    }

    for(cur = head->next; cur != NULL; cur = cur->next)
    {
        printf("%d ", cur->data);
    }
    printf("\r\n");

    return ;
}
    
void listAdd(struct list *new, struct list *now)
{
    if(NULL == new || NULL == now)
    {
        printf("err\r\n");
        return ;
    }

    new->next = now->next;
    now->next = new;

    return ;
}

void revertList(struct list *head)
{
    struct list *pre,*cur;
    struct list *tmp;

    pre = NULL;
    for(cur = head->next; cur != NULL; )
    {
        tmp = cur->next;
        cur->next = pre;
        pre = cur;

        cur = tmp;
    }
    head->next = pre;

    return ;
}
int main(int argc, char *argv[])
{
    int i;

    for(i = 0; i < sizeof(listArray)/sizeof(struct list); i++)
    {
        listAdd(&listArray[i], &head);
    }

    printf("inital list as fellow:");
    showList(&head);

    revertList(&head);

    printf("revert list,result:");
    showList(&head);
}
