//��������������
#include <iostream>
#include <fstream>
#include <time.h>
#define random(a, b) (rand() % (b - a + 1) + a)
using namespace std;
int main()
{
    int t;
    cin >> t;
    ofstream outfile("beibao_in_m.txt", ios::out);
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