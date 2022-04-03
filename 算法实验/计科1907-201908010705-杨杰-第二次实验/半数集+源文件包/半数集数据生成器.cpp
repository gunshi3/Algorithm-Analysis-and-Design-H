//半数集数据生成器
#include <iostream>
#include <fstream>
#include <time.h>
#define random(a,b) (rand()%(b-a+1)+a)
using namespace std;
int main()
{
    ofstream outfile("banshuji_in.txt",ios::out);
    srand((int)time(NULL));
    int t=0;
    cin>>t;
    while(t--)
        outfile<<random(1,2000)<<endl;
    return 0;
}