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

int BinSearch(int len, int w) //修改的二分查找算法，返回数组元素需要插入的位置
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
        else //找到了该元素，则直接返回
            return mid;
    }
    return left; //数组B中不存在该元素，则返回该元素应该插入的位置
}

int LIS() //计算最长递增子序列的长度,计算B数组的元素,array[]循环完一遍后,B的长度len即为所求
{
    int len = 1; //用于标示B数组中的元素个数
    B[0] = array[0];
    int i, pos = 0;
    for (i = 1; i < n; ++i)
    {
        pos = BinSearch(len, array[i]); //二分查找需要插入的位置
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
    QueryPerformanceCounter(&nBeginTime); //开始计时
    int len = LIS();
    QueryPerformanceCounter(&nEndTime);                                                //停止计时
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //计算程序执行时间单位为s
    outfile << "LIS: " << len << "\n";
    int j = 0;
    B[len] = MAX;
    for (int i = 0; i < n; i++) //回溯
    {
        if (array[i] >= B[j] && array[i] <= B[j + 1])
        {
            outfile << array[i] << " ";
            j++;
            if (j == len)
                break;
        }
    }
    outfile << "\n程序耗时" << time * 1000 << "ms" << endl;
    outfile.close();
    return 0;
}