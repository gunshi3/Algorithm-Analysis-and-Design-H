//回溯法实现01背包
#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdio.h>
using namespace std;
#define MAX 2000
int n;                  //物品数量
int c = 500;            //背包容量
double v[MAX];          //各个物品的价值
double w[MAX];          //各个物品的重量
int cw = 0;             //当前背包重量
int cp = 0;             //当前背包中物品价值
int bestp = 0;          //当前最优价值
double perp[MAX];       //单位物品价值排序后
double order[MAX];      //物品编号
int put[MAX] = {0};     //设置是否装入
int bestway[MAX] = {0}; //回溯最优路径

void swap(double *a, double *b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}

//按单位价值排序
void knapsack()
{
    int i, j;
    for (i = 1; i <= n; i++)
        perp[i] = v[i] / w[i];
    for (i = 1; i <= n - 1; i++)
    {
        for (j = i + 1; j <= n; j++)
            if (perp[i] < perp[j]) //冒泡排序perp[],order[],sortv[],sortw[]
            {
                swap(&perp[i], &perp[j]);
                swap(&order[i], &order[j]);
                swap(&v[i], &v[j]);
                swap(&w[i], &w[j]);
            }
    }
}

//计算上界函数
int bound(int i)
{
    int leftw = c - cw;
    int b = cp;
    while (i <= n && w[i] <= leftw)
    {
        leftw -= w[i];
        b += v[i];
        i++;
    }
    if (i <= n)
        b += v[i] / w[i] * leftw;
    return b;
}

//回溯函数
void backtrack(int i)
{
    if (i > n)
    {
        bestp = cp;
        for (int i = 1; i <= n; i++)
            bestway[i] = put[i];
        return;
    }
    if (cw + w[i] <= c)
    {
        cw += w[i];
        cp += v[i];
        put[i] = 1;
        backtrack(i + 1);
        cw -= w[i];
        cp -= v[i];
        put[i] = 0;
    }
    if (bound(i + 1) > bestp) //符合条件搜索右子树
        backtrack(i + 1);
}

int main()
{
    int i;
    ifstream infile("01beibao_in.txt", ios::in);
    ofstream outfile("01beibao_out.txt", ios::out);
    infile >> n;
    for (i = 1; i <= n; i++)
    {
        infile >> w[i] >> v[i];
        order[i] = i;
    }
    infile.close();
    double time = 0;
    LARGE_INTEGER nFreq, nBeginTime, nEndTime;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime); //开始计时
    knapsack();
    backtrack(1);
    QueryPerformanceCounter(&nEndTime);                                                //停止计时
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //计算程序执行时间单位为s
    outfile << "最大价值为：" << bestp << "\n";
    outfile << "需要装入的物品是：\n";
    for (i = 1; i <= n; i++)
    {
        if (bestway[i] == 1)
            outfile << order[i] << " " << w[i] << " " << v[i] << endl;
    }
    outfile << "程序耗时" << time * 1000 << "ms" << endl;
    outfile.close();
    return 0;
}