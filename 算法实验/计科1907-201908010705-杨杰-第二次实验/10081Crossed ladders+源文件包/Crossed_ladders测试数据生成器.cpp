//Crossed ladders测试数据生成器
#include <iostream>
#include <fstream>
#include <time.h>
#define random(a, b) (rand() % (b - a + 1) + a)
using namespace std;
int main()
{
    int t;
    cin >> t;
    ofstream outfile("Crossed ladders_in.txt", ios::out);
    srand((int)time(NULL));
    for (int i = 1; i <= t; i++)
    {
        outfile << random(25, 40) << " ";
        outfile << random(25, 40) << " ";
        outfile << random(10, 20) <<endl;
    }
    outfile.close();
    return 0;
}