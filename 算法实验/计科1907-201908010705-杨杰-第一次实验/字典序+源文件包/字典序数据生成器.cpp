//字典序数据生成器
#include <iostream>
#include <fstream>
#include <time.h>
#define random(a,b) (rand()%(b-a+1)+a)
using namespace std;
int main()
{
    int t=0;
    cin>>t;
    ofstream outfile("zidianxu_in.txt",ios::out);
    outfile<<t<<endl;
    srand((int)time(NULL));
    for(int i=0;i<t;i++)
    {
        int l=random(1,26);
        outfile<<l<<' ';
        int k=random(97,122);
        outfile<<char(k);
        for(int j=1;j<l;j++)
        {
            if(k==122) break;
            k=random(k+1,122);
            outfile<<char(k);
        }
        outfile<<endl;
    }
    outfile.close();
    return 0;
}