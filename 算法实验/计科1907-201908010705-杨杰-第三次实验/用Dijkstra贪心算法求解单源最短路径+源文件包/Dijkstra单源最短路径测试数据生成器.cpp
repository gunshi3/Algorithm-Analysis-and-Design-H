//Dijkstra单源最短路径测试数据生成器
#include <iostream>
#include <fstream>
#include <time.h>
#define random(a, b) (rand() % (b - a + 1) + a)
using namespace std;
int main()
{
    ofstream outfile("Dijkstra_in.txt", ios::out);
    srand((int)time(NULL));
    int n;
    cin >> n;
    outfile << n << endl;
    for (int i = 1; i <= n; i++)
        outfile << i << " ";
    outfile << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            if (i == j)
                outfile << 0 << " ";
            else
                outfile << random(1, 50) << " ";
        outfile << endl;
    }
    outfile << 1;
    outfile.close();
    return 0;
}