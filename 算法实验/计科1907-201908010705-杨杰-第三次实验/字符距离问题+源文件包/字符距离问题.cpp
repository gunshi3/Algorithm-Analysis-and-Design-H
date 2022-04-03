#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <windows.h>
using namespace std;
string a, b;
int dp[1000][1000];
int dist(int i, int j)
//返回a中第i个字符 b中第j个字符的acsii值之差
{
    return abs(a[i - 1] - b[j - 1]);
}
void fun(int len1, int len2, int k)
{
    for (int i = 0; i <= len2; ++i) //有一个字符串是空的
        dp[0][i] = k * i;
    for (int i = 0; i <= len1; ++i)
        dp[i][0] = k * i;
    for (int i = 1; i <= len1; ++i) //递归式
        for (int j = 1; j <= len2; ++j)
            dp[i][j] = min(dp[i - 1][j - 1] + dist(i, j), min(dp[i - 1][j] + k, dp[i][j - 1] + k));
}
int main()
{
    ifstream infile("zifujuli_in.txt", ios::in);
    ofstream outfile("zifujuli_out.txt", ios::out);
    infile >> a >> b; //输入两个字符串
    int k;
    infile >> k;
    infile.close();
    int len1 = a.size();
    int len2 = b.size();
    double time = 0;
    LARGE_INTEGER nFreq, nBeginTime, nEndTime;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime); //开始计时
    fun(len1, len2, k);
    QueryPerformanceCounter(&nEndTime);                                                //停止计时
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //计算程序执行时间单位为s
    outfile << dp[len1][len2] << endl;
    outfile << "程序耗时" << time * 1000 << "ms" << endl;
    outfile.close();
    return 0;
}