//工作分配随机数据生成器
#include <iostream>
#include <fstream>
#include <time.h>
#define random(a, b) (rand() % (b - a + 1) + a)
using namespace std;
int main()
{
    ofstream outfile("gongzuofenpei_in.txt", ios::out);
    srand((int)time(NULL));
    int n = 0;
    cin >> n;
    outfile << n << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            outfile << random(1, 20) << " ";
        outfile << endl;
    }
    return 0;
}