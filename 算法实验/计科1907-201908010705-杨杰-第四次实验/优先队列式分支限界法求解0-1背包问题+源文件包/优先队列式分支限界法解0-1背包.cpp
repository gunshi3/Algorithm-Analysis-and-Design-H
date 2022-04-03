//���ȶ���ʽ��֧�޽編���0-1��������
#include <iostream>
#include <algorithm>
#include <windows.h>
#include <queue>
#include <fstream>
#define MAX 2000
using namespace std;
int bestx[MAX];

struct bbnode
{ //���츸�ڵ�
    bbnode(bbnode *p = NULL, bool s = false) : parent(p), select(s){};
    bbnode *parent;
    bool select;
};

struct Node
{
    Node(int vv = 0, int ww = 0, float bb = 0, int ll = 0, bool ss = false, bbnode *p = NULL) : value(vv), weight(ww), bound(bb), level(ll), select(ss), pr(p){};
    friend bool operator<(Node a, Node b) { return a.bound < b.bound; }; //��bound��Ϊ���ȼ�
    int value;                                                           //��ֵ
    int weight;                                                          //����
    float bound;                                                         //������������+ʣ����Ʒ������װ�����õ�������֮��
    int level;                                                           //����
    bool select;                                                         //�Ƿ�ѡ��
    bbnode *pr;                                                          //��չ�ڵ�ָ��
};

struct Pair
{ //�����Ʒ
    Pair(int ww = 0, int vv = 0, int ii = 0) : weight(ww), value(vv), id(ii), S(float(vv) / float(ww)){};
    int weight, value, id;
    float S;
};
Pair p[MAX];

bool cmp(Pair a, Pair b)
{
    return a.S > b.S;
}

float Bound(Pair p[], int n, int level, int cLeft, int value) //bound������������+ʣ����Ʒ������װ�����õ�������֮��
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

void Knapsack(Pair p[], int n, int c, int bestx[], int &best) //����,��ֵ������������n�����ѡ��ʽ
{
    sort(p + 1, p + n + 1, cmp); //����
    priority_queue<Node> Q;
    int i = 1, cw = 0, cp = 0;
    bbnode *E = NULL;
    float bound;
    while (i <= n)
    {
        if (cw + p[i].weight <= c)
        { //���Է��뱳��
            bound = Bound(p, n, i, c - cw, cp);
            if (cp + p[i].value > best)
                best = cp + p[i].value;                                           //��ʱ���¾��ܻ�û����Ҷ�ڵ�
            AddNode(Q, bound, cw + p[i].weight, cp + p[i].value, true, i + 1, E); //�����
        }
        bound = Bound(p, n, i + 1, c - cw, cp); //����boundֵ
        if (bound >= best)
        { //����������
            AddNode(Q, bound, cw, cp, false, i + 1, E);
        }
        Node q = Q.top(); //ȡ�����ֵ�ڵ�
        Q.pop();
        /*ȡ�����ֵ�ڵ㣬�õ�����ֵ*/
        i = q.level;
        cw = q.weight;
        cp = q.value;
        E = q.pr;
    }
    /*���������*/
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
    int n;        //��Ʒ����
    int c = 3000; //��������
    int best = 0; //��ǰ���ż�ֵ
    infile >> n;
    int w, v;
    for (int i = 1; i <= n; i++)
    {
        infile >> w >> v;
        p[i] = Pair(w, v, i); //��������
    }
    /*���Ժ���*/
    double time = 0;
    LARGE_INTEGER nFreq, nBeginTime, nEndTime;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime); //��ʼ��ʱ
    Knapsack(p, n, c, bestx, best);
    QueryPerformanceCounter(&nEndTime);                                                //ֹͣ��ʱ
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //�������ִ��ʱ�䵥λΪs
    /*������*/
    outfile << "��֧�޽編\n";
    outfile << "���ݹ�ģ��n=" << n << "  c=" << c << endl;
    outfile << "���Ž�Ϊ��" << best << endl;
    outfile << "������Ϊ��\n";
    for (int i = 1; i <= n; i++)
    {
        outfile << bestx[i] << ' ';
        if (i % 20 == 0 && i != n)
            outfile << endl;
    }
    outfile << "\n�����ʱ��" << time * 1000 << "ms";
    infile.close();
    outfile.close();
    return 0;
}
