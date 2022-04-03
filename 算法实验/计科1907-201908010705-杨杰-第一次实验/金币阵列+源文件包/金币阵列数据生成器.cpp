//金币阵列数据生成器
#include <iostream>
#include <fstream>
#include <time.h>
#define random(a,b) (rand()%(b-a+1)+a)
using namespace std;
int main()
{
    int t=0;
    cin>>t;
    ofstream outfile("jinbi_in.txt",ios::out);
    outfile<<t<<endl;
    srand((int)time(NULL));
    int m=0,n=0;
    for(int i=0;i<t;i++)
    {
        m=random(2,100);
        n=random(max(m-2,2),min(m+2,100));
        outfile<<m<<' '<<n<<endl;
        for(int j=0;j<m;j++)
        {
            for(int k=0;k<n;k++)
                outfile<<random(0,1)<<' ';
            outfile<<endl;
        }
        for(int j=0;j<m;j++)
        {
            for(int k=0;k<n;k++)
                outfile<<random(0,1)<<' ';
            outfile<<endl;
        }
    }
    outfile.close();
    return 0;
}