#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdint.h>

#include "list.h"

int rawdata[][10] = 
{
    {1, 12, 23, 34, 45, 56, 67, 78, 89, 90},
    {2, 11, 24, 33, 44, 57, 66, 76, 83, 99},
    {5, 18, 26, 39, 42, 55, 69, 70, 80, 91},
    {10, 13, 22, 38, 43, 51, 68, 79, 89, 99},
    {8, 14, 25, 36, 49, 54, 67, 78, 82, 92},
    {9, 19, 27, 35, 47, 53, 65, 72, 88, 98},
//    {3, 17, 29, 31, 46, 59, 62, 74, 84, 94},
//    {7, 16, 28, 32, 48, 58, 64, 73, 85, 95},
};

/*
 * @breif 从line行col列中选出最小的前num个数字;每一行数字是从小到大排列
 */
int raceSourt(int *src, int line, int col, int *out, int num)
{
    int i, j;
    struct list_head *pos, *n;
    //记录每一行最小数字的行序号、列序号等信息
    struct lineRec
    {
        struct list_head node;
        int line;
        int col;
        int val;
    }*curLineRec, *linePos;
    int remain;     //剩余需要排序出的数字
    int cmpCnt;
    int min;
    int nodeCnt = line;
    LIST_HEAD(head);

    /* 取出每行首列，按大小排序 */
    for(i = 0; i < line; i++)
    {
        curLineRec = (struct lineRec *)malloc(sizeof(struct lineRec));
        curLineRec->col = 0;
        curLineRec->line = i;
        curLineRec->val = *(src+i*col);
        if(list_empty(&head))
        {
            list_add_tail(&curLineRec->node, &head);
        }
        else
        {
            list_for_each_entry(linePos, &head, node)
            {
                if(curLineRec->val < linePos->val)
                {
                    break;
                }
            }
            list_add_tail(&curLineRec->node, &linePos->node);
        }
    }
    
    /* 依次选出最小的数到第num小的数 */
    remain = num;
    for(i = 0; i < num; i++)
    {
        /* 避免对尾部数据做不必要的比较运算 */
        /* cmpCnt应该是链表节点数和剩余数目的最小值，当剩余数目小于节点数时，才有必要避免尾部计算 */
        //cmpCnt = (nodeCnt < remain)?nodeCnt:remain;
        cmpCnt = nodeCnt;
        
        /* 取出首节点数据，用作比较基准 */
        pos = head.next;
        curLineRec = list_entry(pos, struct lineRec, node);
        min = curLineRec->val;
        j = 1;
        /* 遍历前cmpCnt个节点,找出最小值 */
        list_for_each_safe(pos, n, head.next)
        {
            if(j >= cmpCnt)
            {
                break;
            }
            j++;
            
            curLineRec = list_entry(pos, struct lineRec, node);
            if(curLineRec->val < min)
            {
                min = curLineRec->val;
                //将该节点更新到首节点
                list_move(pos, &head);
            }
        }
        
        /* 取出最小的数，并更新 */
        curLineRec = (struct lineRec *)(head.next);
        out[i] = curLineRec->val;
        remain -= 1;
        /* 使用该行下一列数据替换当前节点 */
        curLineRec->col++;
        if(curLineRec->col >= col)
        {
            list_del(&curLineRec->node);
            free(curLineRec);
            nodeCnt--;
        }
        else
        {
            curLineRec->val = *(src + curLineRec->line*col + curLineRec->col);
        }
        
    }

    /* 释放链表 */
    list_for_each_safe(pos, n, &head)
    {
        list_del(pos);
        free(pos);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int i;
    int *buf = NULL;
    int cnt = 10;

    if(argc >= 2)
        cnt = strtoul(argv[1], NULL, 10);

    buf = malloc(sizeof(int)*cnt);
    memset(buf, 0, sizeof(int)*cnt);
    
    raceSourt(rawdata[0], sizeof(rawdata)/sizeof(rawdata[0]), sizeof(rawdata[0])/sizeof(rawdata[0][0]),
                buf, cnt);

    for(i = 0; i < cnt; i++)
    {
        printf("%02d ", buf[i]);
    }
    printf("\r\n");

    free(buf);
}

