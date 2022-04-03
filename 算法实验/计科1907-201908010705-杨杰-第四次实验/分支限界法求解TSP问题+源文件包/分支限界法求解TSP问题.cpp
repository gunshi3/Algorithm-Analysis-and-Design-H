//分支限界法求解TSP问题
#include <iostream>
#include <fstream>
#include <windows.h>
#include <queue>
using namespace std;

ifstream infile("TSP_in.txt", ios::in);
ofstream outfile("TSP_out.txt", ios::out);
int N;

template <class Type>
class Traveling
{
    friend int main();

public:
    Type BBTSP(int v[]);

private:
    int n;      //图G的顶点数
    Type **a,   //图G的邻接矩阵
        NoEdge, //图G的无边标识
        cc,     //当前费用
        bestc;  //当前最小费用
};

template <class Type>
class MinHeapNode
{
    friend Traveling<Type>;
    friend bool operator<(MinHeapNode a, MinHeapNode b) { return a.lcost > b.lcost; }; //以lcost小为优先级

private:
    Type lcost, //子树费用的下界
        cc,     //当前费用
        rcost;  //x[s:nNoEdge]中顶点最小出边费用和
    int s,      //根节点到当前节点的路径为x[0:s]
        *x;     //需要进一步搜索的顶点是x[s+1:nNoEdge]
};

//解旅行员售货问题的优先队列式分支限界法
template <class Type>
Type Traveling<Type>::BBTSP(int v[])
{
    priority_queue<MinHeapNode<Type>> Q;
    Type *MinOut = new Type[n + 1];
    //计算MinOut[i] = 顶点i的最小出边费用
    Type MinSum = 0; //最小出边费用和
    for (int i = 1; i <= n; i++)
    {
        Type Min = NoEdge;
        for (int j = 1; j <= n; j++)
        {
            if (a[i][j] != NoEdge && (a[i][j] < Min || Min == NoEdge))
            {
                Min = a[i][j];
            }
        }
        if (Min == NoEdge)
        {
            return NoEdge; //无回路
        }
        MinOut[i] = Min;
        MinSum += Min;
    }

    //初始化
    MinHeapNode<Type> E;
    E.x = new int[n];
    for (int i = 0; i < n; i++)
    {
        E.x[i] = i + 1;
    }
    E.s = 0;          //根节点到当前节点路径为x[0:s]
    E.cc = 0;         //当前费用
    E.rcost = MinSum; //最小出边费用和
    Type bestc = NoEdge;
    //搜索排列空间树
    while (E.s < n - 1) //非叶结点
    {
        if (E.s == n - 2) //当前扩展节点是叶节点的父节点
        {
            //再加2条边构成回路
            //所构成回路是否优于当前最优解
            if (a[E.x[n - 2]][E.x[n - 1]] != NoEdge && a[E.x[n - 1]][1] != NoEdge && (E.cc + a[E.x[n - 2]][E.x[n - 1]] + a[E.x[n - 1]][1] < bestc || bestc == NoEdge))
            {
                //费用更小的回路
                bestc = E.cc + a[E.x[n - 2]][E.x[n - 1]] + a[E.x[n - 1]][1];
                E.cc = bestc;
                E.lcost = bestc;
                E.s++;
                Q.push(E);
            }
            else
            {
                delete[] E.x; //舍弃扩展节点
            }
        }
        else //产生当前扩展节点的儿子节点
        {
            for (int i = E.s + 1; i < n; i++)
            {
                if (a[E.x[E.s]][E.x[i]] != NoEdge)
                {
                    //可行儿子节点
                    Type cc = E.cc + a[E.x[E.s]][E.x[i]];
                    Type rcost = E.rcost - MinOut[E.x[E.s]];
                    Type b = cc + rcost; //下界
                    if (b < bestc || bestc == NoEdge)
                    {
                        //子树可能含有最优解
                        //节点插入最小堆
                        MinHeapNode<Type> N;
                        N.x = new int[n];
                        for (int j = 0; j < n; j++)
                        {
                            N.x[j] = E.x[j];
                        }
                        N.x[E.s + 1] = E.x[i];
                        N.x[i] = E.x[E.s + 1];
                        N.cc = cc;
                        N.s = E.s + 1;
                        N.lcost = b;
                        N.rcost = rcost;
                        Q.push(N);
                    }
                }
            }
            delete[] E.x; //舍弃扩展节点
        }
        if (Q.empty())
        {
            break;
        }
        E = Q.top(); //取下一扩展节点
        Q.pop();
    }

    if (bestc == NoEdge)
    {
        return NoEdge; //无回路
    }
    //将最优解复制到v[1:n]
    for (int i = 0; i < n; i++)
    {
        v[i + 1] = E.x[i];
    }

    while (true) //释放最小堆中所有节点
    {
        delete[] E.x;
        if (Q.empty())
        {
            break;
        }
        E = Q.top(); //取下一扩展节点
        Q.pop();
    }
    return bestc;
}

Traveling<int> t;
int main()
{
    infile >> N;
    int *bestx = new int[N + 1];
    outfile << "图的顶点个数 n=" << N << endl;
    int **a = new int *[N + 1];
    for (int i = 1; i <= N; i++)
    {
        a[i] = new int[N + 1];
    }
    outfile << "图的邻接矩阵为:" << endl;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            infile >> a[i][j];
            outfile << a[i][j] << " ";
        }
        outfile << endl;
    }
    t.a = a;
    t.n = N;
    double time = 0;
    LARGE_INTEGER nFreq, nBeginTime, nEndTime;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime); //开始计时
    int dis = t.BBTSP(bestx);
    QueryPerformanceCounter(&nEndTime);                                                //停止计时
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //计算程序执行时间单位为s
    outfile << "最短回路的长为：" << dis << endl;
    outfile << "最短回路为：" << endl;
    for (int i = 1; i <= N; i++)
    {
        outfile << bestx[i] << "-->";
    }
    outfile << bestx[1] << endl;
    outfile << "程序耗时：" << time * 1000 << "ms";
    for (int i = 1; i <= N; i++)
    {
        delete[] a[i];
    }
    delete[] a;
    delete[] bestx;
    return 0;
}