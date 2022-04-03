//高级模运算测试数据生成器
#include <iostream>
#include <fstream>
#include <time.h>
#define random(a, b) (rand() % (b - a + 1) + a)
using namespace std;
int main()
{
    ofstream outfile("gaojimoyunsuan_in.txt", ios::out);
    srand((int)time(NULL));
    outfile << random(1, 45000) << endl;
    int H = random(1, 20);
    outfile << H << endl;
    for (int i = 1; i <= H; i++)
    {
        outfile << random(1, 2147483648) << " " << random(1, 2147483648) << endl;
    }
    outfile.close();
    return 0;
}