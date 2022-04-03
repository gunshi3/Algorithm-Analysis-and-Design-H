//优先队列式分支限界法求解0-1背包问题
#include <iostream>
#include <algorithm>
#include <windows.h>
#include <queue>
#include <fstream>
#define MAX 2000
using namespace std;
int bestx[MAX];

struct bbnode
{ //构造父节点
    bbnode(bbnode *p = NULL, bool s = false) : parent(p), select(s){};
    bbnode *parent;
    bool select;
};

struct Node
{
    Node(int vv = 0, int ww = 0, float bb = 0, int ll = 0, bool ss = false, bbnode *p = NULL) : value(vv), weight(ww), bound(bb), level(ll), select(ss), pr(p){};
    friend bool operator<(Node a, Node b) { return a.bound < b.bound; }; //以bound大为优先级
    int value;                                                           //价值
    int weight;                                                          //重量
    float bound;                                                         //背包已有重量+剩下物品将背包装满所得到的重量之和
    int level;                                                           //层数
    bool select;                                                         //是否被选择
    bbnode *pr;                                                          //扩展节点指针
};

struct Pair
{ //存放物品
    Pair(int ww = 0, int vv = 0, int ii = 0) : weight(ww), value(vv), id(ii), S(float(vv) / float(ww)){};
    int weight, value, id;
    float S;
};
Pair p[MAX];

bool cmp(Pair a, Pair b)
{
    return a.S > b.S;
}

float Bound(Pair p[], int n, int level, int cLeft, int value) //bound背包已有重量+剩下物品将背包装满所得到的重量之和
{
    while (level <= n && p[level].weight <= cLeft)
    {
        cLeft -= p[level].weight;
        value += p[level].value;
        level++;
    }
    if (level <= n)
        value += p[level].S * cLeft;
    return value;
}

void AddNode(priority_queue<Node> &Q, float bound, int cw, int cp, bool select, int level, bbnode *E)
{
    bbnode *b = new bbnode(E, select);
    Q.push(Node(cp, cw, bound, level, select, b));
}

void Knapsack(Pair p[], int n, int c, int bestx[], int &best) //重量,价值，容量，总数n，最佳选择方式
{
    sort(p + 1, p + n + 1, cmp); //排序
    priority_queue<Node> Q;
    int i = 1, cw = 0, cp = 0;
    bbnode *E = NULL;
    float bound;
    while (i <= n)
    {
        if (cw + p[i].weight <= c)
        { //可以放入背包
            bound = Bound(p, n, i, c - cw, cp);
            if (cp + p[i].value > best)
                best = cp + p[i].value;                                           //及时更新尽管还没到达叶节点
            AddNode(Q, bound, cw + p[i].weight, cp + p[i].value, true, i + 1, E); //加入堆
        }
        bound = Bound(p, n, i + 1, c - cw, cp); //计算bound值
        if (bound >= best)
        { //处理右子树
            AddNode(Q, bound, cw, cp, false, i + 1, E);
        }
        Node q = Q.top(); //取出最大值节点
        Q.pop();
        /*取出最大值节点，得到属性值*/
        i = q.level;
        cw = q.weight;
        cp = q.value;
        E = q.pr;
    }
    /*构造解向量*/
    for (int i = n; i >= 1; i--)
    {
        int index = p[i].id;
        bestx[index] = E->select;
        E = E->parent;
    }
}

int main()
{
    ifstream infile("01beibao_in.txt", ios::in);
    ofstream outfile("01beibao_out.txt", ios::out);
    int n;        //物品数量
    int c = 3000; //背包容量
    int best = 0; //当前最优价值
    infile >> n;
    int w, v;
    for (int i = 1; i <= n; i++)
    {
        infile >> w >> v;
        p[i] = Pair(w, v, i); //读入数据
    }
    /*测试函数*/
    double time = 0;
    LARGE_INTEGER nFreq, nBeginTime, nEndTime;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime); //开始计时
    Knapsack(p, n, c, bestx, best);
    QueryPerformanceCounter(&nEndTime);                                                //停止计时
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //计算程序执行时间单位为s
    /*输出结果*/
    outfile << "分支限界法\n";
    outfile << "数据规模：n=" << n << "  c=" << c << endl;
    outfile << "最优解为：" << best << endl;
    outfile << "解向量为：\n";
    for (int i = 1; i <= n; i++)
    {
        outfile << bestx[i] << ' ';
        if (i % 20 == 0 && i != n)
            outfile << endl;
    }
    outfile << "\n程序耗时：" << time * 1000 << "ms";
    infile.close();
    outfile.close();
    return 0;
}
