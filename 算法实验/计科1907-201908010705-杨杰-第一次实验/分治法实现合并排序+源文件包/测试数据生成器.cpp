//测试数据生成器.cpp
#include <iostream>
#include <time.h>
#include <fstream>
#include <cmath>
#define random(x) (int)(((double)rand()/RAND_MAX)*pow(10,rand()%x))
using namespace std;
const int maxn=1e6;//1M
int array[maxn+5]={0};//存储产生的随机数
void print(fstream &outfile,int n,int A[])//输出
{
	for(int i=0;i<n;i++)
		outfile<<A[i]<<endl;
}
int main()
{
    srand((int)time(NULL));//time seed
    string files[5]={"100.txt","1k.txt","10k.txt","100k.txt","1M.txt"};
    fstream file;
    for(int i=0;i<maxn;i++)//随机产生1M的数据
        array[i]=random(7);
    int k=100;
    for(int i=0;i<5;i++)//装载5个test文件
    {
        file.open(files[i],ios::out);//打开文件
        print(file,k,array);
        file.close();//关闭文件
        k*=10;
    }
    cout<<"随机数生成成功！"<<endl;
    return 0;
}