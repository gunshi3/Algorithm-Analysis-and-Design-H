//集合划分数据生成器
#include <iostream>
#include <fstream>
#include <time.h>
#define random(a,b) (rand()%(b-a+1)+a)
using namespace std;
int main()
{
    int t=0;
    cin>>t;
    srand((int)time(NULL));//time seed
    ofstream outfile("jihehuafen_in.txt",ios::out);
    while(t--)
        outfile<<random(1,1000)<<endl;
    outfile.close();
    return 0;
}