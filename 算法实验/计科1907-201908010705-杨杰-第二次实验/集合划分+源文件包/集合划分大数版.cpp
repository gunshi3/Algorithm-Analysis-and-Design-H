//���ϻ�������
#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <windows.h>
#define yunsuan(a, b, c) add(a, mul(b, c))
#define ll long long
using namespace std;
string A[1000][1000];
ll a[1000][1000];
ll fun(int n, int m) //��fun(n,m)��Сʱ���ô˺�������fun(n,m)��ֵ
{
    if (a[n][m] != -1)
        return a[n][m];
    else if (n < m)
        a[n][m] = 0;
    else if (m == 0)
        a[n][m] = 0;
    else if (m == n)
        a[n][m] = 1;
    else
        a[n][m] = fun(n - 1, m - 1) + m * fun(n - 1, m);
    return a[n][m];
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
string mul(string a, string b) //�������ַ�����Ӧ��ʮ����������ˣ�������һ���ַ���
{
    int l = a.length();
    int t = b.length();
    int aa[l] = {0}, bb[t] = {0};
    int c[l + t] = {0};
    int i, m;
    for (i = 0, m = l - 1; m >= 0; i++, m--)
        aa[i] = a[m] - '0';
    for (i = 0, m = t - 1; m >= 0; i++, m--)
        bb[i] = b[m] - '0';
    for (i = 0; i < l; i++)
        for (m = 0; m < t; m++)
            c[i + m] += aa[i] * bb[m];
    for (i = 0; i < l + t; i++) //�����ǰѳ���10�Ľ�λ
    {
        if (c[i] >= 10)
        {
            c[i + 1] = c[i + 1] + c[i] / 10;
            c[i] %= 10;
        }
    }
    string s = "";
    int k = 0;
    for (i = l + t - 1; i >= 0; i--) //��ǰ��0ȥ��
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
string big_num_fun(int n, int m) //��fun(n,m)����long long��Χʱ���ô˺�������fun(n,m)��ֵ
{
    if (A[n][m] != "")
        return A[n][m];
    else if (n < m)
        A[n][m] = "0";
    else if (m == 0)
        A[n][m] = "0";
    else if (m == n)
        A[n][m] = "1";
    else
        A[n][m] = yunsuan(big_num_fun(n - 1, m - 1), sstr(m), big_num_fun(n - 1, m));
    return A[n][m];
}
int main()
{
    memset(a, -1, sizeof(a));
    ifstream infile("jihehuafen_in.txt", ios::in);
    ofstream outfile("jihehuafen_out1.txt", ios::out);
    int x = 0;
    ll sum = 0;
    string big_num_sum = "0";
    bool flag = true;
    double time = 0;
    LARGE_INTEGER nFreq, nBeginTime, nEndTime;
    while (infile >> x)
    {
        QueryPerformanceFrequency(&nFreq);
        QueryPerformanceCounter(&nBeginTime); //��ʼ��ʱ
        if (x <= 25)
        {
            for (int i = 1; i <= x; i++)
                sum += fun(x, i);
            flag = true;
        }
        else
        {
            for (int i = 1; i <= x; i++)
                big_num_sum = add(big_num_sum, big_num_fun(x, i));
            flag = false;
        }
        QueryPerformanceCounter(&nEndTime);                                                //ֹͣ��ʱ
        time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //�������ִ��ʱ�䵥λΪs
        if (flag)
            outfile << x << "��Ԫ�صļ��Ͽ��Ի���Ϊ" << sum << "����ͬ�ķǿ��Ӽ��������ʱ" << time * 1000 << "ms" << endl;
        else
            outfile << x << "��Ԫ�صļ��Ͽ��Ի���Ϊ" << big_num_sum << "����ͬ�ķǿ��Ӽ��������ʱ" << time * 1000 << "ms" << endl;
        sum = 0;
        big_num_sum = "0";
    }
    infile.close();
    outfile.close();
    return 0;
}