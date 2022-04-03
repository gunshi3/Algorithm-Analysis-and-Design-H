//用Dijkstra贪心算法求解单源最短路径问题
#include <cstdlib>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <windows.h>
#define MaxVerNum 1000 //顶点最大数目值
#define VexType int    //顶点数据类型
#define EdgeType int   //边数据类型,无向图时邻接矩阵对称，有权值时表示权值，没有时1连0不连
#define INF 0x3f3f3f3f //作为最大值
using namespace std;
//图的数据结构
typedef struct Graph
{
    VexType Vex[MaxVerNum];              //顶点表
    EdgeType Edge[MaxVerNum][MaxVerNum]; //边表
    int vexnum, arcnum;                  //顶点数、边数
} Graph;
//迪杰斯特拉算法全局变量
bool S[MaxVerNum]; //顶点集
int D[MaxVerNum];  //到各个顶点的最短路径
int Pr[MaxVerNum]; //记录前驱
//*********************************************基本操作函数*****************************************//
//初始化函数 参数：图G 作用：初始化图的顶点表，邻接矩阵等
void InitGraph(Graph &G)
{
    memset(G.Vex, 0, sizeof(G.Vex)); //初始化顶点表
    //初始化边表
    for (int i = 0; i < MaxVerNum; i++)
        for (int j = 0; j < MaxVerNum; j++)
            G.Edge[i][j] = INF;
    G.vexnum = G.arcnum = 0; //初始化顶点数、边数
}
//打印图的顶点表
void PrintVex(Graph &G, ofstream &outfile)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        outfile << G.Vex[i] << " ";
    }
    outfile << endl;
}
//打印图的边矩阵
void PrintEdge(Graph &G, ofstream &outfile)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        for (int j = 0; j < G.vexnum; j++)
        {
            if (G.Edge[i][j] == INF)
                outfile << "∞ ";
            else
                outfile << G.Edge[i][j] << " ";
        }
        outfile << endl;
    }
}
//创建图功能实现函数 参数：图G  InsertNode 作用：创建图
void CreateGraph(Graph &G, ifstream &infile, ofstream &outfile)
{
    VexType v, w;
    outfile << "请输入顶点数目:" << endl;
    infile >> G.vexnum;
    outfile << G.vexnum << endl;
    outfile << "请输入所有顶点名称:" << endl;
    for (int i = 0; i < G.vexnum; i++)
    {
        infile >> G.Vex[i];
        outfile << G.Vex[i] << ' ';
    }
    outfile << endl;
    outfile << "请输入邻接矩阵:" << endl;
    for (int i = 0; i < G.vexnum; i++)
    {
        for (int j = 0; j < G.vexnum; j++)
        {
            infile >> G.Edge[i][j];
            outfile << G.Edge[i][j] << ' ';
            if (G.Edge[i][j] == -1)
                G.Edge[i][j] = INF;
        }
        outfile << endl;
    }
    outfile << "图的顶点表为:\n";
    PrintVex(G, outfile);
    outfile << "图的边矩阵为:\n";
    PrintEdge(G, outfile);
}
//最短路径 - Dijkstra算法 参数：图G、源点v
void Dijkstra(Graph &G, int v)
{
    //初始化
    int n = G.vexnum; //n为图的顶点个数
    for (int i = 0; i < n; i++)
    {
        S[i] = false;
        D[i] = G.Edge[v][i];
        if (D[i] < INF)
            Pr[i] = 0; //v与i连接，v为前驱
        else
            Pr[i] = -1;
    }
    S[v] = true;
    D[v] = 0;
    //初始化结束,求最短路径，并加入S集
    for (int i = 1; i < n; i++)
    {
        int min = INF;
        int temp;
        for (int w = 0; w < n; w++)
            if (!S[w] && D[w] < min) //某点temp未加入s集，且为当前最短路径
            {
                temp = w;
                min = D[w];
            }
        S[temp] = true;
        //更新从源点出发至其余点的最短路径 通过temp
        for (int w = 0; w < n; w++)
            if (!S[w] && D[temp] + G.Edge[temp][w] < D[w])
            {
                D[w] = D[temp] + G.Edge[temp][w];
                Pr[w] = temp;
            }
    }
}
//输出最短路径
void Path(Graph &G, int v, ofstream &outfile)
{
    if (Pr[v] == 0)
    {
        outfile << "->" << G.Vex[v];
    }
    else
    {
        Path(G, Pr[v], outfile);
        outfile << "->" << G.Vex[v];
    }
}
//调用最短路径-Dijkstra算法 参数：图G、源点v
void Shortest_Dijkstra(Graph &G, ifstream &infile, ofstream &outfile)
{
    int vname;
    int v = -1;
    outfile << "请输入源点名称:" << endl;
    infile >> vname;
    outfile << vname << endl;
    for (int i = 0; i < G.vexnum; i++)
        if (G.Vex[i] == vname)
        {
            v = i;
            break;
        }
    Dijkstra(G, v);
    outfile << "目标点 最短路径值 最短路径" << endl;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (i != v)
        {
            if (D[i] != INF)
            {
                outfile << G.Vex[i] << "      " << D[i] << "        ";
                outfile << G.Vex[v];
                Path(G, i, outfile);
            }
            else
                outfile << G.Vex[i] << "      INF";
            outfile << "\n";
        }
    }
}
int main()
{
    Graph *G=new Graph();
    ifstream infile("Dijkstra_in.txt", ios::in);
    ofstream outfile("Dijkstra_out.txt", ios::out);
    InitGraph(*G);
    CreateGraph(*G, infile, outfile);
    double time = 0;
    LARGE_INTEGER nFreq, nBeginTime, nEndTime;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime); //开始计时
    Shortest_Dijkstra(*G, infile, outfile);
    QueryPerformanceCounter(&nEndTime);                                                //停止计时
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //计算程序执行时间单位为s
    outfile << "程序耗时" << time * 1000 << "ms" << endl;
    infile.close();
    outfile.close();
    return 0;
}