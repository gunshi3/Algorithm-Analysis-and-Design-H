//回溯法解工作分配
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
#define N 1000
int cost[N][N];   // 表示第i个人完成第j件工作需要的费用
int isC[N] = {0}; // 用于记录第n个工作是否完成，0表示未完成
int n;
int scost; // 表示总费用

void Backstrack(int i, int c) // i表示从第i个人开始 ，c表示当前需要的总费用
{
    if (c > scost)
    {
        // cout << "剪枝\n";
        return;
    }
    if (i == n + 1) // 当最后一个人也分配好工作后判断总费用
    {
        if (c < scost)
            scost = c;
        return;
    }
    for (int j = 1; j <= n; j++)
    {
        if (isC[j] == 0) // 判断第j个工作是否已经完成，类似剪枝函数
        {
            isC[j] = 1;
            // cout << "第" << i << "个人完成第" << j << "个工作\n";
            Backstrack(i + 1, c + cost[i][j]);
            isC[j] = 0; // 回溯法
            // cout << "第" << j << "个工作未完成\n";
        }
    }
}

int main()
{
    ifstream infile("gongzuofenpei_in.txt", ios::in);
    ofstream outfile("gongzuofenpei_out.txt", ios::out);
    double time = 0;
    LARGE_INTEGER nFreq, nBeginTime, nEndTime;
    infile >> n;
    outfile << n << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            infile >> cost[i][j];
            outfile << cost[i][j] << " ";
        }
        outfile << endl;
    }
    infile.close();
    scost = N; // 给总费用设置一个很大的值
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime); //开始计时
    Backstrack(1, 0);
    QueryPerformanceCounter(&nEndTime);                                                //停止计时
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //计算程序执行时间单位为s
    outfile << "程序耗时" << time * 1000 << "ms" << endl;
    outfile << "最小总费用为" << scost;
    outfile.close();
    return 0;
}