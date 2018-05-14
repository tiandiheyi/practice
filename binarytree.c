#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************
*****************   list ************************
 ************************************************/
struct list
{
    struct list *next;
    void *data;
};

void listAddTail(struct list *head, void *element)
{
    struct list *p;
    struct list *new;
    
    if(NULL == head)
    {
        printf("list is null\r\n");
        return ;
    }

    p = head;
    while(p->next)
    {
        p = p->next;
    }

    new = (struct list *)malloc(sizeof(struct list));
    new->next = NULL;
    new->data = element;
    p->next = new;

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

/*****************************************************
******************************************************
                    binary tree
******************************************************
*****************************************************/

struct tree
{
    struct tree *left;
    struct tree *right;
    int data;
};

void creatBinaryTree(struct tree **node, int *srcArray, int start, int end)
{
    int m;

//    printf("enter,start:%d, end:%d", start, end);
    if(start <= end)
    {
        m = (start + end)/2;
        *node = (struct tree *)malloc(sizeof(struct tree));
        (*node)->data = srcArray[m];
        (*node)->left = NULL;
        (*node)->right = NULL;
//        printf(",m:%d\r\n", m);
//        printf("%d\r\n\r\n", srcArray[m]);

//        printf("left:");
        creatBinaryTree(&((*node)->left), srcArray, start, m - 1);
//        printf("right:");
        creatBinaryTree(&((*node)->right), srcArray, m + 1, end);
    }
//    printf("\r\nexit\r\n");

    return ;
}

/**
 * @brief 层次遍历二叉树，从左至右方式
 * @param[in] root- 二叉树根节点
 **/
void showBinaryTree(struct tree *root)
{
    struct list nodeHead = {NULL, 0};
    struct list childHead = {NULL, 0};
    struct list *node;
    struct tree *treeNode;

    //nodeHead.next = (struct list*)root;
    listAddTail(&nodeHead, (void *)root);
    for(node = nodeHead.next; node != NULL; )
    {
        treeNode = (struct tree *)node->data;
        printf("%d ", treeNode->data);

        if(treeNode->left)
            listAddTail(&childHead, (void *)treeNode->left);
        if(treeNode->right)
            listAddTail(&childHead, (void *)treeNode->right);

        if(node->next == NULL)
        {
            //del node
            node = childHead.next;
            childHead.next = NULL;
        }
        else
        {
            //del node
            node = node->next;
        }
    }
    printf("\r\nend\r\n");
}

int main(int argc, char *argv[])
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int b[] = {4, 8, 2, 5, 9, 1, 6, 10, 3, 11, 7, 12};
    struct tree *root1,*root2;

    creatBinaryTree(&root1, a, 0, sizeof(a)/sizeof(int) - 1);
    showBinaryTree(root1);

    creatBinaryTree(&root2, b, 0, sizeof(b)/sizeof(int) - 1);
    showBinaryTree(root2);
}

