//LIS随机数据生成器
#include <iostream>
#include <fstream>
#include <time.h>
#define random(a, b) (rand() % (b - a + 1) + a)
using namespace std;
int main()
{
    int t = 0;
    cin >> t;
    ofstream outfile("LIS_in.txt", ios::out);
    outfile << t << endl;
    srand((int)time(NULL));
    for (int i = 1; i <= t; i++)
    {
        outfile << random(1, 100) << " ";
        if (i % 20 == 0)
            outfile << endl;
    }
    outfile.close();
    return 0;
}