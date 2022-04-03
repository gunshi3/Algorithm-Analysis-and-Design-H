//���ݷ��⹤������
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
#define N 1000
int cost[N][N];   // ��ʾ��i������ɵ�j��������Ҫ�ķ���
int isC[N] = {0}; // ���ڼ�¼��n�������Ƿ���ɣ�0��ʾδ���
int n;
int scost; // ��ʾ�ܷ���

void Backstrack(int i, int c) // i��ʾ�ӵ�i���˿�ʼ ��c��ʾ��ǰ��Ҫ���ܷ���
{
    if (c > scost)
    {
        // cout << "��֦\n";
        return;
    }
    if (i == n + 1) // �����һ����Ҳ����ù������ж��ܷ���
    {
        if (c < scost)
            scost = c;
        return;
    }
    for (int j = 1; j <= n; j++)
    {
        if (isC[j] == 0) // �жϵ�j�������Ƿ��Ѿ���ɣ����Ƽ�֦����
        {
            isC[j] = 1;
            // cout << "��" << i << "������ɵ�" << j << "������\n";
            Backstrack(i + 1, c + cost[i][j]);
            isC[j] = 0; // ���ݷ�
            // cout << "��" << j << "������δ���\n";
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
    scost = N; // ���ܷ�������һ���ܴ��ֵ
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime); //��ʼ��ʱ
    Backstrack(1, 0);
    QueryPerformanceCounter(&nEndTime);                                                //ֹͣ��ʱ
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //�������ִ��ʱ�䵥λΪs
    outfile << "�����ʱ" << time * 1000 << "ms" << endl;
    outfile << "��С�ܷ���Ϊ" << scost;
    outfile.close();
    return 0;
}