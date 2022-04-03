//贪心法实现背包问题
#include <iostream>
#include <fstream>
#include <windows.h>
#include <algorithm>
#include <vector>
using namespace std;
struct Thing
{
    float w;
    float v;
    float vperw;
};
bool cmp(Thing l, Thing r)
{
    return l.vperw > r.vperw;
}
void bbsort(vector<float> &w, vector<float> &v, int n) //将物品按单位效益降序排列
{
    Thing T[n];
    for (int i = 0; i < n; i++)
    {
        T[i].w = w[i];
        T[i].v = v[i];
        T[i].vperw = v[i] / w[i];
    }
    sort(T, T + n, cmp);
    for (int i = 0; i < n; i++)
    {
        v[i] = T[i].v;
        w[i] = T[i].w;
    }
}
void beibao(vector<float> &w, vector<float> &v, int n, float c, float *x) //构造最优解
{
    bbsort(w, v, n);
    int i;
    for (i = 0; i < n; i++)
    {
        if (c < w[i])
            break;
        x[i] = 1;
        c -= w[i];
    }
    if (i < n)
        x[i] = c / w[i];
}
int main()
{
    float c = 100000; //背包容量
    float a, b;
    vector<float> w, v;
    ifstream infile("beibao_in_l.txt", ios::in);
    while (infile >> a >> b)
    {
        w.push_back(a);
        v.push_back(b);
    }
    int n = v.size();
    float x[n];
    memset(x, 0, sizeof(float) * n); //x[]数组初始化为0
    ofstream outfile("beibao_out_l.txt", ios::out);
    double time = 0;
    LARGE_INTEGER nFreq, nBeginTime, nEndTime;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime); //开始计时
    beibao(w, v, n, c, x);
    float sum = 0;
    for (int i = 0; i < n; i++) //计算最优值
    {
        sum += x[i] * v[i];
    }
    outfile << sum << endl;
    for (int i = 0; i < n; i++)
    {
        outfile << x[i] << ' ';
        if (i != 0 && i % 20 == 0)
            outfile << endl;
    }
    outfile << endl;
    QueryPerformanceCounter(&nEndTime);                                                //停止计时
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //计算程序执行时间单位为s
    outfile << "程序耗时" << time * 1000 << "ms" << endl;
    infile.close();
    outfile.close();
    return 0;
}