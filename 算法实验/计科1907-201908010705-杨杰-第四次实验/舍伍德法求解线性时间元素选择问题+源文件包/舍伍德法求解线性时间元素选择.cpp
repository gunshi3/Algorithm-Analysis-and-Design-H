//����·��������ʱ��Ԫ��ѡ��
#include <iostream>
#include <windows.h>
#include <fstream>
#include <time.h>
using namespace std;
#define INF 0x7fffffff //����������ж��Ƿ����
#define Random(n) (int)rand() % n

/************************************************�㷨����*/
template <class Type>
Type select(Type a[], int l, int r, int k)
{
    while (true)
    {
        if (l >= r)
            return a[l];
        int i = l, j = l + Random(r - l + 1); //������֣�jΪ[i:r]֮���һ������λ��
        swap(a[i], a[j]);                     //����a[i]��a[j]������Ԫ�ط��ڻ��ֵ�a[j]
        j = r + 1;                            //��j�����Ҷ˵�
        Type pivot = a[l];                    //pivotѡ��Ϊ��
        while (true)                          //С��pivot��Ԫ�ع�Ϊ��ߣ������Ϊ�ұ�
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
            return pivot;  //����Ҷ˵�����˵�ľ���֮�����k��˵���ҵ�һ����
        a[l] = a[j];       //���ỻ���м�
        a[j] = pivot;      //
        if (j - l + 1 < k) //������
        {
            k = k - j + l - 1; //kֵҪ��С(j-l+1),ǰ���б�kС��j-l+1��Ԫ��
            l = j + 1;
        }
        else
            r = j - 1; //������
    }
}
/***********************************************�㷨����*/

template <class Type>
Type Select(Type a[], int n, int k)
{
    if (k < 1 || k > n)
        return INF; //������
    return select<Type>(a, 0, n - 1, k);
}
template <class Type>
double testTime(Type Select(Type a[], int n, int k), Type a[], int n, int k, Type &numberK)
{
    LARGE_INTEGER frequency;               //ʱ�����
    double dff, begin_, _end;              //ʱ��Ƶ�ʣ���ʼʱ�䣬����ʱ�䣬ʱ���
    QueryPerformanceFrequency(&frequency); //���ʱ��Ƶ��
    dff = (double)frequency.QuadPart;      //ȡ��Ƶ��
    QueryPerformanceCounter(&frequency);
    begin_ = frequency.QuadPart; //��ó�ʼֵ

    numberK = Select(a, n, k);

    QueryPerformanceCounter(&frequency);
    _end = frequency.QuadPart;    //�����ֵֹ
    return (_end - begin_) / dff; //��ֵ����Ƶ�ʵõ�ʱ��
}
int main()
{
    ifstream infile("����·��������ʱ��Ԫ��ѡ��_in.txt", ios::in);   //����
    ofstream outfile("����·��������ʱ��Ԫ��ѡ��_out.txt", ios::out); //д��
    int n, k, numberK;
    infile >> n >> k;
    int a[n + 1] = {0};
    for (int i = 0; i < n; i++)
        infile >> a[i]; //��������

    /*���Ժ���*/
    double time = testTime<int>(Select, a, n, k, numberK);
    /*������*/
    outfile << "���ݹ�ģ��  n=" << n << "  k=" << k << endl;
    if (numberK != INF)
        outfile << "��k��Ԫ��Ϊ��" << numberK << endl;
    else
        outfile << "Ԫ���������в����ڣ�" << endl;
    outfile << "ʱ�仨��Ϊ��spendTime=" << time * 1000 << "ms";
    outfile << endl
            << "-------------------------------------------------" << endl;
    infile.close();
    outfile.close();
    cout << "excute sucefully!" << endl;
    return 0;
}