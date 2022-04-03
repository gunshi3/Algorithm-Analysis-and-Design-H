//��֧�޽編���TSP����
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
    int n;      //ͼG�Ķ�����
    Type **a,   //ͼG���ڽӾ���
        NoEdge, //ͼG���ޱ߱�ʶ
        cc,     //��ǰ����
        bestc;  //��ǰ��С����
};

template <class Type>
class MinHeapNode
{
    friend Traveling<Type>;
    friend bool operator<(MinHeapNode a, MinHeapNode b) { return a.lcost > b.lcost; }; //��lcostСΪ���ȼ�

private:
    Type lcost, //�������õ��½�
        cc,     //��ǰ����
        rcost;  //x[s:nNoEdge]�ж�����С���߷��ú�
    int s,      //���ڵ㵽��ǰ�ڵ��·��Ϊx[0:s]
        *x;     //��Ҫ��һ�������Ķ�����x[s+1:nNoEdge]
};

//������Ա�ۻ���������ȶ���ʽ��֧�޽編
template <class Type>
Type Traveling<Type>::BBTSP(int v[])
{
    priority_queue<MinHeapNode<Type>> Q;
    Type *MinOut = new Type[n + 1];
    //����MinOut[i] = ����i����С���߷���
    Type MinSum = 0; //��С���߷��ú�
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
            return NoEdge; //�޻�·
        }
        MinOut[i] = Min;
        MinSum += Min;
    }

    //��ʼ��
    MinHeapNode<Type> E;
    E.x = new int[n];
    for (int i = 0; i < n; i++)
    {
        E.x[i] = i + 1;
    }
    E.s = 0;          //���ڵ㵽��ǰ�ڵ�·��Ϊx[0:s]
    E.cc = 0;         //��ǰ����
    E.rcost = MinSum; //��С���߷��ú�
    Type bestc = NoEdge;
    //�������пռ���
    while (E.s < n - 1) //��Ҷ���
    {
        if (E.s == n - 2) //��ǰ��չ�ڵ���Ҷ�ڵ�ĸ��ڵ�
        {
            //�ټ�2���߹��ɻ�·
            //�����ɻ�·�Ƿ����ڵ�ǰ���Ž�
            if (a[E.x[n - 2]][E.x[n - 1]] != NoEdge && a[E.x[n - 1]][1] != NoEdge && (E.cc + a[E.x[n - 2]][E.x[n - 1]] + a[E.x[n - 1]][1] < bestc || bestc == NoEdge))
            {
                //���ø�С�Ļ�·
                bestc = E.cc + a[E.x[n - 2]][E.x[n - 1]] + a[E.x[n - 1]][1];
                E.cc = bestc;
                E.lcost = bestc;
                E.s++;
                Q.push(E);
            }
            else
            {
                delete[] E.x; //������չ�ڵ�
            }
        }
        else //������ǰ��չ�ڵ�Ķ��ӽڵ�
        {
            for (int i = E.s + 1; i < n; i++)
            {
                if (a[E.x[E.s]][E.x[i]] != NoEdge)
                {
                    //���ж��ӽڵ�
                    Type cc = E.cc + a[E.x[E.s]][E.x[i]];
                    Type rcost = E.rcost - MinOut[E.x[E.s]];
                    Type b = cc + rcost; //�½�
                    if (b < bestc || bestc == NoEdge)
                    {
                        //�������ܺ������Ž�
                        //�ڵ������С��
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
            delete[] E.x; //������չ�ڵ�
        }
        if (Q.empty())
        {
            break;
        }
        E = Q.top(); //ȡ��һ��չ�ڵ�
        Q.pop();
    }

    if (bestc == NoEdge)
    {
        return NoEdge; //�޻�·
    }
    //�����Ž⸴�Ƶ�v[1:n]
    for (int i = 0; i < n; i++)
    {
        v[i + 1] = E.x[i];
    }

    while (true) //�ͷ���С�������нڵ�
    {
        delete[] E.x;
        if (Q.empty())
        {
            break;
        }
        E = Q.top(); //ȡ��һ��չ�ڵ�
        Q.pop();
    }
    return bestc;
}

Traveling<int> t;
int main()
{
    infile >> N;
    int *bestx = new int[N + 1];
    outfile << "ͼ�Ķ������ n=" << N << endl;
    int **a = new int *[N + 1];
    for (int i = 1; i <= N; i++)
    {
        a[i] = new int[N + 1];
    }
    outfile << "ͼ���ڽӾ���Ϊ:" << endl;
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
    QueryPerformanceCounter(&nBeginTime); //��ʼ��ʱ
    int dis = t.BBTSP(bestx);
    QueryPerformanceCounter(&nEndTime);                                                //ֹͣ��ʱ
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //�������ִ��ʱ�䵥λΪs
    outfile << "��̻�·�ĳ�Ϊ��" << dis << endl;
    outfile << "��̻�·Ϊ��" << endl;
    for (int i = 1; i <= N; i++)
    {
        outfile << bestx[i] << "-->";
    }
    outfile << bestx[1] << endl;
    outfile << "�����ʱ��" << time * 1000 << "ms";
    for (int i = 1; i <= N; i++)
    {
        delete[] a[i];
    }
    delete[] a;
    delete[] bestx;
    return 0;
}