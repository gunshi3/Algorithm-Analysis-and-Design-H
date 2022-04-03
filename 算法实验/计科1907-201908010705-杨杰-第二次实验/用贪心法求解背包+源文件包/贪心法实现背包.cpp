//̰�ķ�ʵ�ֱ�������
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
void bbsort(vector<float> &w, vector<float> &v, int n) //����Ʒ����λЧ�潵������
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
void beibao(vector<float> &w, vector<float> &v, int n, float c, float *x) //�������Ž�
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
    float c = 100000; //��������
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
    memset(x, 0, sizeof(float) * n); //x[]�����ʼ��Ϊ0
    ofstream outfile("beibao_out_l.txt", ios::out);
    double time = 0;
    LARGE_INTEGER nFreq, nBeginTime, nEndTime;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime); //��ʼ��ʱ
    beibao(w, v, n, c, x);
    float sum = 0;
    for (int i = 0; i < n; i++) //��������ֵ
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
    QueryPerformanceCounter(&nEndTime);                                                //ֹͣ��ʱ
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //�������ִ��ʱ�䵥λΪs
    outfile << "�����ʱ" << time * 1000 << "ms" << endl;
    infile.close();
    outfile.close();
    return 0;
}