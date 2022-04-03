//动态规划法实现01背包
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
using namespace std;
int m[2000][50000];
void beibao(vector<int> w, vector<int> v, int n, int c) //计算最优值
{
    int j = 0;
    for (j = 0; j < w[n]; j++)
        m[n][j] = 0;
    for (j = w[n]; j <= c; j++)
        m[n][j] = v[n];
    for (int i = n - 1; i >= 1; i--)
    {
        for (j = 0; j < w[i]; j++)
            m[i][j] = m[i + 1][j];
        for (j = w[i]; j <= c; j++)
        {
            if (m[i + 1][j] > m[i + 1][j - w[i]] + v[i])
                m[i][j] = m[i + 1][j];
            else
                m[i][j] = m[i + 1][j - w[i]] + v[i];
        }
    }
    m[0][c] = m[1][c];
    if (c >= w[0])
        if (m[1][c - w[0]] + v[0] > m[1][c])
            m[0][c] = m[1][c - w[0]] + v[0];
}
void beibao_back(vector<int> w, int x[], int n, int c) //回溯
{
    for (int i = 0; i < n; i++)
    {
        if (m[i][c] == m[i + 1][c])
            x[i] = 0;
        else
        {
            x[i] = 1;
            c -= w[i];
        }
    }
    if (c >= w[n])
        x[n] = 1;
    else
        x[n] = 0;
}
int main()
{
    int c = 2000;
    int a, b;
    vector<int> w, v;
    ifstream infile("01beibao_in.txt", ios::in);
    while (infile >> a >> b)
    {
        w.push_back(a);
        v.push_back(b);
    }
    int n = w.size() - 1;
    ofstream outfile("01beibao_out.txt", ios::out);
    double time = 0;
    LARGE_INTEGER nFreq, nBeginTime, nEndTime;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime); //开始计时
    beibao(w, v, n, c);
    for (int i = n; i >= 0; i--)
    {
        for (int j = 0; j <= c; j++)
            outfile << m[i][j] << ' ';
        outfile << endl;
    }
    outfile << m[0][c] << endl;
    int x[n + 1];
    beibao_back(w, x, n, c);
    for (int i = 0; i <= n; i++)
        outfile << x[i] << ' ';
    outfile << endl;
    QueryPerformanceCounter(&nEndTime);                                                //停止计时
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //计算程序执行时间单位为s
    outfile << "程序耗时" << time * 1000 << "ms" << endl;
    infile.close();
    outfile.close();
    return 0;
}