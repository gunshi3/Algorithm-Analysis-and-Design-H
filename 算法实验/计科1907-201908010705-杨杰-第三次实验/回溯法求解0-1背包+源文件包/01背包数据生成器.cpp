//01背包数据生成器
#include <iostream>
#include <fstream>
#include <time.h>
#define random(a, b) (rand() % (b - a + 1) + a)
using namespace std;
int main()
{
    int t;
    cin >> t;
    ofstream outfile("01beibao_in.txt", ios::out);
    outfile << t << endl;
    srand((int)time(NULL));
    for (int i = 1; i <= 2 * t; i++)
    {
        outfile << random(1, 100) << " ";
        if (i % 20 == 0)
            outfile << endl;
    }
    outfile.close();
    return 0;
}