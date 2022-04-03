//LIS
#include <iostream>
#include <fstream>
#include <windows.h>
#define MAX 9999
using namespace std;

int array[MAX];
int A[MAX];
int B[MAX];
int n;
ifstream infile("LIS_in.txt", ios::in);
ofstream outfile("LIS_out.txt", ios::out);

int BinSearch(int len, int w) //�޸ĵĶ��ֲ����㷨����������Ԫ����Ҫ�����λ��
{
    int left = 0, right = len - 1;
    int mid;
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (B[mid] > w)
            right = mid - 1;
        else if (B[mid] < w)
            left = mid + 1;
        else //�ҵ��˸�Ԫ�أ���ֱ�ӷ���
            return mid;
    }
    return left; //����B�в����ڸ�Ԫ�أ��򷵻ظ�Ԫ��Ӧ�ò����λ��
}

int LIS() //��������������еĳ���,����B�����Ԫ��,array[]ѭ����һ���,B�ĳ���len��Ϊ����
{
    int len = 1; //���ڱ�ʾB�����е�Ԫ�ظ���
    B[0] = array[0];
    int i, pos = 0;
    for (i = 1; i < n; ++i)
    {
        pos = BinSearch(len, array[i]); //���ֲ�����Ҫ�����λ��
        B[pos] = array[i];
        if (pos == len)
            len++;
    }
    return len;
}

int main()
{
    infile >> n;
    for (int i = 0; i < n; i++)
    {
        infile >> array[i];
    }
    infile.close();
    double time = 0;
    LARGE_INTEGER nFreq, nBeginTime, nEndTime;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime); //��ʼ��ʱ
    int len = LIS();
    QueryPerformanceCounter(&nEndTime);                                                //ֹͣ��ʱ
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //�������ִ��ʱ�䵥λΪs
    outfile << "LIS: " << len << "\n";
    int j = 0;
    B[len] = MAX;
    for (int i = 0; i < n; i++) //����
    {
        if (array[i] >= B[j] && array[i] <= B[j + 1])
        {
            outfile << array[i] << " ";
            j++;
            if (j == len)
                break;
        }
    }
    outfile << "\n�����ʱ" << time * 1000 << "ms" << endl;
    outfile.close();
    return 0;
}