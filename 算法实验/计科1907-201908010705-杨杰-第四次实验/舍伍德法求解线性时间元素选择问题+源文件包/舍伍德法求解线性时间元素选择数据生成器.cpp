//����·��������ʱ��Ԫ��ѡ������������
#include <iostream>
#include <fstream>
#include <time.h>
#define random(a, b) (rand() % (b - a + 1) + a)
using namespace std;
int main()
{
    ofstream outfile("����·��������ʱ��Ԫ��ѡ��_in.txt", ios::out);
    int t,k;
    cin >> t;
    srand((int)time(NULL));//time seed
    k=random(1,t);
    outfile<<t<<" "<<k<<endl;
    for(int i=1;i<=t;i++)
    {
        outfile<<random(1,10000)<<" ";
        if(i%20==0)
            outfile<<endl;
    }
    outfile.close();
    return 0;
}