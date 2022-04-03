//舍伍德法求解线性时间元素选择
#include <iostream>
#include <windows.h>
#include <fstream>
#include <time.h>
using namespace std;
#define INF 0x7fffffff //无穷大用于判断是否存在
#define Random(n) (int)rand() % n

/************************************************算法过程*/
template <class Type>
Type select(Type a[], int l, int r, int k)
{
    while (true)
    {
        if (l >= r)
            return a[l];
        int i = l, j = l + Random(r - l + 1); //随机划分，j为[i:r]之间的一个任意位置
        swap(a[i], a[j]);                     //交换a[i]和a[j]，将首元素放在划分点a[j]
        j = r + 1;                            //将j换成右端点
        Type pivot = a[l];                    //pivot选定为轴
        while (true)                          //小于pivot的元素归为左边，否则归为右边
        {
            while (a[++i] < pivot && i <= r)
                ;
            while (a[--j] > pivot && j >= 0)
                ;
            if (i >= j)
                break;
            swap(a[i], a[j]);
        }

        if (j - l + 1 == k)
            return pivot;  //如果右端点与左端点的距离之差等于k，说明找到一个解
        a[l] = a[j];       //将轴换回中间
        a[j] = pivot;      //
        if (j - l + 1 < k) //右序列
        {
            k = k - j + l - 1; //k值要减小(j-l+1),前面有比k小的j-l+1个元素
            l = j + 1;
        }
        else
            r = j - 1; //左序列
    }
}
/***********************************************算法结束*/

template <class Type>
Type Select(Type a[], int n, int k)
{
    if (k < 1 || k > n)
        return INF; //不存在
    return select<Type>(a, 0, n - 1, k);
}
template <class Type>
double testTime(Type Select(Type a[], int n, int k), Type a[], int n, int k, Type &numberK)
{
    LARGE_INTEGER frequency;               //时间对象
    double dff, begin_, _end;              //时钟频率，起始时间，结束时间，时间差
    QueryPerformanceFrequency(&frequency); //获得时钟频率
    dff = (double)frequency.QuadPart;      //取得频率
    QueryPerformanceCounter(&frequency);
    begin_ = frequency.QuadPart; //获得初始值

    numberK = Select(a, n, k);

    QueryPerformanceCounter(&frequency);
    _end = frequency.QuadPart;    //获得终止值
    return (_end - begin_) / dff; //差值除以频率得到时间
}
int main()
{
    ifstream infile("舍伍德法求解线性时间元素选择_in.txt", ios::in);   //读入
    ofstream outfile("舍伍德法求解线性时间元素选择_out.txt", ios::out); //写入
    int n, k, numberK;
    infile >> n >> k;
    int a[n + 1] = {0};
    for (int i = 0; i < n; i++)
        infile >> a[i]; //读入数据

    /*测试函数*/
    double time = testTime<int>(Select, a, n, k, numberK);
    /*输出结果*/
    outfile << "数据规模：  n=" << n << "  k=" << k << endl;
    if (numberK != INF)
        outfile << "第k个元素为：" << numberK << endl;
    else
        outfile << "元素在序列中不存在！" << endl;
    outfile << "时间花费为：spendTime=" << time * 1000 << "ms";
    outfile << endl
            << "-------------------------------------------------" << endl;
    infile.close();
    outfile.close();
    cout << "excute sucefully!" << endl;
    return 0;
}