//字符距离数据生成器
#include <iostream>
#include <fstream>
#include <time.h>
#define random(a, b) (rand() % (b - a + 1) + a)
using namespace std;
int main()
{
    ofstream outfile("zifujuli_in.txt", ios::out);
    srand((int)time(NULL));
    int a = random(1, 50);
    int b = random(1, 50);
    char ch;
    for (int j = 0; j < a; j++)
    {
        ch = random('a', 'z');
        outfile << ch;
    }
    outfile << endl;
    for (int j = 0; j < b; j++)
    {
        ch = random('a', 'z');
        outfile << ch;
    }
    outfile << endl;
    outfile << random(1, 10) << endl;
    outfile.close();
    return 0;
}