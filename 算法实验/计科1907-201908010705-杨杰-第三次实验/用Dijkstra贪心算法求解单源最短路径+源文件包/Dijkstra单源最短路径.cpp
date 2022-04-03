//��Dijkstra̰���㷨��ⵥԴ���·������
#include <cstdlib>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <windows.h>
#define MaxVerNum 1000 //���������Ŀֵ
#define VexType int    //������������
#define EdgeType int   //����������,����ͼʱ�ڽӾ���Գƣ���Ȩֵʱ��ʾȨֵ��û��ʱ1��0����
#define INF 0x3f3f3f3f //��Ϊ���ֵ
using namespace std;
//ͼ�����ݽṹ
typedef struct Graph
{
    VexType Vex[MaxVerNum];              //�����
    EdgeType Edge[MaxVerNum][MaxVerNum]; //�߱�
    int vexnum, arcnum;                  //������������
} Graph;
//�Ͻ�˹�����㷨ȫ�ֱ���
bool S[MaxVerNum]; //���㼯
int D[MaxVerNum];  //��������������·��
int Pr[MaxVerNum]; //��¼ǰ��
//*********************************************������������*****************************************//
//��ʼ������ ������ͼG ���ã���ʼ��ͼ�Ķ�����ڽӾ����
void InitGraph(Graph &G)
{
    memset(G.Vex, 0, sizeof(G.Vex)); //��ʼ�������
    //��ʼ���߱�
    for (int i = 0; i < MaxVerNum; i++)
        for (int j = 0; j < MaxVerNum; j++)
            G.Edge[i][j] = INF;
    G.vexnum = G.arcnum = 0; //��ʼ��������������
}
//��ӡͼ�Ķ����
void PrintVex(Graph &G, ofstream &outfile)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        outfile << G.Vex[i] << " ";
    }
    outfile << endl;
}
//��ӡͼ�ı߾���
void PrintEdge(Graph &G, ofstream &outfile)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        for (int j = 0; j < G.vexnum; j++)
        {
            if (G.Edge[i][j] == INF)
                outfile << "�� ";
            else
                outfile << G.Edge[i][j] << " ";
        }
        outfile << endl;
    }
}
//����ͼ����ʵ�ֺ��� ������ͼG  InsertNode ���ã�����ͼ
void CreateGraph(Graph &G, ifstream &infile, ofstream &outfile)
{
    VexType v, w;
    outfile << "�����붥����Ŀ:" << endl;
    infile >> G.vexnum;
    outfile << G.vexnum << endl;
    outfile << "���������ж�������:" << endl;
    for (int i = 0; i < G.vexnum; i++)
    {
        infile >> G.Vex[i];
        outfile << G.Vex[i] << ' ';
    }
    outfile << endl;
    outfile << "�������ڽӾ���:" << endl;
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
    outfile << "ͼ�Ķ����Ϊ:\n";
    PrintVex(G, outfile);
    outfile << "ͼ�ı߾���Ϊ:\n";
    PrintEdge(G, outfile);
}
//���·�� - Dijkstra�㷨 ������ͼG��Դ��v
void Dijkstra(Graph &G, int v)
{
    //��ʼ��
    int n = G.vexnum; //nΪͼ�Ķ������
    for (int i = 0; i < n; i++)
    {
        S[i] = false;
        D[i] = G.Edge[v][i];
        if (D[i] < INF)
            Pr[i] = 0; //v��i���ӣ�vΪǰ��
        else
            Pr[i] = -1;
    }
    S[v] = true;
    D[v] = 0;
    //��ʼ������,�����·����������S��
    for (int i = 1; i < n; i++)
    {
        int min = INF;
        int temp;
        for (int w = 0; w < n; w++)
            if (!S[w] && D[w] < min) //ĳ��tempδ����s������Ϊ��ǰ���·��
            {
                temp = w;
                min = D[w];
            }
        S[temp] = true;
        //���´�Դ����������������·�� ͨ��temp
        for (int w = 0; w < n; w++)
            if (!S[w] && D[temp] + G.Edge[temp][w] < D[w])
            {
                D[w] = D[temp] + G.Edge[temp][w];
                Pr[w] = temp;
            }
    }
}
//������·��
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
//�������·��-Dijkstra�㷨 ������ͼG��Դ��v
void Shortest_Dijkstra(Graph &G, ifstream &infile, ofstream &outfile)
{
    int vname;
    int v = -1;
    outfile << "������Դ������:" << endl;
    infile >> vname;
    outfile << vname << endl;
    for (int i = 0; i < G.vexnum; i++)
        if (G.Vex[i] == vname)
        {
            v = i;
            break;
        }
    Dijkstra(G, v);
    outfile << "Ŀ��� ���·��ֵ ���·��" << endl;
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
    QueryPerformanceCounter(&nBeginTime); //��ʼ��ʱ
    Shortest_Dijkstra(*G, infile, outfile);
    QueryPerformanceCounter(&nEndTime);                                                //ֹͣ��ʱ
    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart; //�������ִ��ʱ�䵥λΪs
    outfile << "�����ʱ" << time * 1000 << "ms" << endl;
    infile.close();
    outfile.close();
    return 0;
}