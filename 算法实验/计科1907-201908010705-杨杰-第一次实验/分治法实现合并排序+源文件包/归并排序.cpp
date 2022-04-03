//归并排序
#include <iostream>
#include <fstream>
#include <windows.h>
#include <cmath>
using namespace std;
int A[1000001],temp[1000001];
int count=0;
void Init(fstream &infile)
{
    int x=0;
    count=0;
    while(infile>>x)
        A[count++]=x;
}
void print(fstream &outfile)
{
    int k=0;
    for(int i=0;i<count;i++)
    {
        outfile<<A[i]<<' ';
        k++;
        if(k==20) 
        {
            outfile<<endl;
            k=0;
        }
    }
}
bool cmp(int x,int y)
{
    return x<y;
}
void mergesort(int A[],int temp[],int left,int right) //归并排序 
{
    if(left==right)
        return;
    int mid=(left+right)/2;
    mergesort(A,temp,left,mid);
    mergesort(A,temp,mid+1,right);
    for(int i=left;i<=right;i++)
        temp[i]=A[i];
    int i1=left;
    int i2=mid+1;
    for(int curr=left;curr<=right;curr++)
    {
        if(i1==mid+1)
            A[curr]=temp[i2++];
        else if(i2>right)
            A[curr]=temp[i1++];
        else if(cmp(temp[i1],temp[i2]))
            A[curr]=temp[i1++];
        else 
            A[curr]=temp[i2++];
    }
}
int main()
{
	string files[6]={"100.txt","10k.txt","1M.txt",
					"out_100.txt","out_10k.txt","out_1M.txt"};
    fstream file;
	double time=0;
	LARGE_INTEGER nFreq,nBeginTime,nEndTime;
    int k=0;
    for(int i=0;i<3;i++)//对3个测试文件进行归并排序
    {
        file.open(files[i],ios::in);//打开测试文件
        Init(file);//初始化文件将数据填入序列A中
        file.close();
        QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&nBeginTime);//开始计时
    	mergesort(A,temp,0,100*pow(10,k)-1); //归并排序
		QueryPerformanceCounter(&nEndTime);//停止计时
		time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s 
        file.open(files[i+3],ios::out);//打开测试文件
        file<<"数据规模为"<<100*pow(10,k)<<"的数据进行归并排序,结果为"<<time*1000<<"ms"<<endl;
        print(file);
        file.close();
        k+=2;
    }
    return 0;
}