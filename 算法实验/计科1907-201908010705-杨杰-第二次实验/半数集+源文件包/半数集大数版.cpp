//����������
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <string.h>
#define ll unsigned long long
using namespace std;
string A[25000];
ll a[25000];
ll set(int n) //��set(n)��Сʱ���ô˺�������set(n)��ֵ
{
    if (a[n] != 0)
        return a[n];
    else if (n == 1)
        a[n] = 1;
    else
    {
        for (int i = 1; i <= n / 2; i++)
            a[n] += set(i);
        a[n]++;
    }
    return a[n];
}
string sstr(int n) //������ת�ַ���
{
    string s = "";
    stringstream ss;
    ss << n;
    s = ss.str();
    return s;
}
string add(string a, string b) //�������ַ�����Ӧ��ʮ����������ӣ�������һ���ַ���
{
    int l = a.length();
    int t = b.length();
    int x = l > t ? (l + 1) : (t + 1);
    int aa[x - 1] = {0}, bb[x - 1] = {0};
    int c[x] = {0};
    int i, m;
    for (i = 0, m = l - 1; m >= 0; i++, m--)
        aa[i] = a[m] - '0';
    for (i = 0, m = t - 1; m >= 0; i++, m--)
        bb[i] = b[m] - '0';
    for (i = 0; i < x - 1; i++)
        c[i] = aa[i] + bb[i];
    for (i = 0; i < x; i++) //�����ǰѳ���10�Ľ�λ
    {
        if (c[i] >= 10)
        {
            c[i + 1] = c[i + 1] + c[i] / 10;
            c[i] %= 10;
        }
    }
    string s = "";
    int k = 0;
    for (i = x - 1; i >= 0; i--) //��ǰ��0ȥ��
    {
        if (c[i] == 0)
            continue;
        else
        {
            k = i;
            break;
        }
    }
    if (i == -1)
        s = "0";
    for (i = k; i >= 0; i--)
        s = s + sstr(c[i]);
    return s;
}
string big_num_set(int n) //��set(n)����unsigned long long��Χʱ���ô˺�������set(n)��ֵ
{
    if (A[n] != "")
        return A[n];
    else if (n == 1)
        A[n] = "1";
    else
    {
        for (int i = 1; i <= n / 2; i++)
            A[n] = add(big_num_set(i), A[n]);
        A[n] = add(A[n], "1");
    }
    return A[n];
}
int main()
{
    memset(a, 0, sizeof(a));
    ifstream infile("banshuji_in.txt", ios::in);
    ofstream outfile("banshuji_out1.txt", ios::out);
    double time = 0;
    LARGE_INTEGER nFreq, nBeginTime, nEndTime;
    int x;
    ll r = 0;
    string big_num_r = "0";
    bool flag = true;
    while (infile >> x)
    {
        QueryPerformanceFrequency(&nFreq);
        QueryPerformanceCounter(&nBeginTime); //��ʼ��ʱ
        if (x <= 15725)
        {
            r = set(x);
            flag = true;
        }
        else
        {
            big_num_r = big_num_set(x);
            flag = false;
        }
        QueryPerformanceCounter(&nEndTime);                                                //ֹͣ��ʱ
        time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //�������ִ��ʱ�䵥λΪs
        if (flag)
            outfile << "������set(" << x << ")�е�Ԫ�ظ���Ϊ" << r << ",�����ʱ" << time * 1000 << "ms" << endl;
        else
            outfile << "������set(" << x << ")�е�Ԫ�ظ���Ϊ" << big_num_r << ",�����ʱ" << time * 1000 << "ms" << endl;
    }
    infile.close();
    outfile.close();
    return 0;
}