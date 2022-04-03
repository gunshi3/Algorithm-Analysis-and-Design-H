//���ݷ�ʵ��01����
#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdio.h>
using namespace std;
#define MAX 2000
int n;                  //��Ʒ����
int c = 500;            //��������
double v[MAX];          //������Ʒ�ļ�ֵ
double w[MAX];          //������Ʒ������
int cw = 0;             //��ǰ��������
int cp = 0;             //��ǰ��������Ʒ��ֵ
int bestp = 0;          //��ǰ���ż�ֵ
double perp[MAX];       //��λ��Ʒ��ֵ�����
double order[MAX];      //��Ʒ���
int put[MAX] = {0};     //�����Ƿ�װ��
int bestway[MAX] = {0}; //��������·��

void swap(double *a, double *b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}

//����λ��ֵ����
void knapsack()
{
    int i, j;
    for (i = 1; i <= n; i++)
        perp[i] = v[i] / w[i];
    for (i = 1; i <= n - 1; i++)
    {
        for (j = i + 1; j <= n; j++)
            if (perp[i] < perp[j]) //ð������perp[],order[],sortv[],sortw[]
            {
                swap(&perp[i], &perp[j]);
                swap(&order[i], &order[j]);
                swap(&v[i], &v[j]);
                swap(&w[i], &w[j]);
            }
    }
}

//�����Ͻ纯��
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

//���ݺ���
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
    if (bound(i + 1) > bestp) //������������������
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
    QueryPerformanceCounter(&nBeginTime); //��ʼ��ʱ
    knapsack();
    backtrack(1);
    QueryPerformanceCounter(&nEndTime);                                                //ֹͣ��ʱ
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //�������ִ��ʱ�䵥λΪs
    outfile << "����ֵΪ��" << bestp << "\n";
    outfile << "��Ҫװ�����Ʒ�ǣ�\n";
    for (i = 1; i <= n; i++)
    {
        if (bestway[i] == 1)
            outfile << order[i] << " " << w[i] << " " << v[i] << endl;
    }
    outfile << "�����ʱ" << time * 1000 << "ms" << endl;
    outfile.close();
    return 0;
}