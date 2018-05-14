#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/***********************************************
该文件为动态规划方法示例
以切钢条得到最大利润为例

************************************************/
#define INT_MIN (-1)
#define KIND_SIZE 10
/** 每种长度的出售价格 */
//int price[]={0,1,5,8,9,10,17,17,20,24,30};
int price[]={0,1,2,3,5,3,2,1,1,2,2};

int dealMaxProfit(int n , int maxProfit[], int devidePos[]);
/**
 * 得到最大的利润
 * @param  n 钢条长度
 * @return   最大利润
 */
int getMaxProfit(int n, int devidePos[])
{   
    if( n < 0 || n > KIND_SIZE)
        return 0;
    int maxProfit[KIND_SIZE];//记录每个长度下的最大利润是多少
    for (int i = 0; i <=  KIND_SIZE ; ++i)
    {
        maxProfit[i] = INT_MIN;  
        devidePos[i] = i;
    }
    maxProfit[0] = 0;
    dealMaxProfit(n , maxProfit, devidePos);
    return maxProfit[n];
}

/**
 * 将每个长度对应的比n小的钢条最大利润都保存在maxProfit里面
 * @param n         钢条长度
 * @param maxProfit 保存最大利润的数组
 * @return          返回长度为n的最大利润
 */
int dealMaxProfit(int n , int maxProfit[], int devidePos[])
{
    int max = INT_MIN;
    int pos = n;
    
    if( n == 0)
        return 0;
    /** 表示之前已经算过了 */
    if(maxProfit[n]!= INT_MIN)
        return maxProfit[n];
    /** 没有算过那么就算一遍 */
    /*
    for (int i = 1; i < n+1; ++i)
    {
        int temp = price[i]+dealMaxProfit(n-i, maxProfit, devidePos);
        if(max < temp)
        {
            max = temp;
            pos = i;
        }
    }
    */
    for(int i = n; i >= (n+1)/2; i--)
    {
        int temp = price[i] + dealMaxProfit(n - i, maxProfit,devidePos);
        if(max < temp)
        {
            max = temp;
            pos = i;
        }
    }
    maxProfit[n] = max;
    devidePos[n] = pos;
    return max;
}

void printCutSolution(int n , int devidePos[])
{
    if(n < 0 || n > KIND_SIZE)
        return ;
    if( n == devidePos[n])
    {
        printf("%s\n", "not devide" );
        return;
    }
    printf("%d steel bar devide into %d and %d \n", n , n - devidePos[n] , devidePos[n] );
    printCutSolution(n - devidePos[n] , devidePos);
}

int main(int argc, char const *argv[])
{
    int meter = 11;
    int priceMax;
    int devidePos[KIND_SIZE + 1];
    
    if(argc >= 2)
    {
        meter = strtoul(argv[1], NULL, 10);
        if(meter > KIND_SIZE)  meter = KIND_SIZE;
    }
    
    priceMax = getMaxProfit(meter, devidePos);

    printf("max price:%d\r\n", priceMax);
    printCutSolution(meter, devidePos);
    return 0;
}

