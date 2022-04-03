//查找最大最小值.cpp
#include <iostream>
#include <fstream>
#include <windows.h> 
#include <cmath>
using namespace std;
int A[1000001];
void BS(int a[],int left,int right,int& max,int& min)
{
	int middle,max1,max2,min1,min2;
	if(left==right)
    {		
		max=a[left];
		min=a[left];	
	}
    else
    {
		middle=(left+right)/2;
		BS(a,left,middle,max1,min1);	
		BS(a,middle+1,right,max2,min2);
		if(min1>min2)
			min=min2;
		else
			min=min1;
		if(max2>max1)
			max=max2;
		else
			max=max1;
	}
}
int main()
{
	string files[6]={"100.txt","10k.txt","1M.txt",
					"out_100.txt","out_10k.txt","out_1M.txt"};
    fstream file;
	int len=100,k=0;
	for(int i=0;i<3;i++)
	{
		file.open(files[i],ios::in);
		for(int i=0;i<len;i++)
			file>>A[i];
		file.close();
		int max=A[0],min=max;
		LARGE_INTEGER time,time0,time1;
		QueryPerformanceFrequency(&time);
		QueryPerformanceCounter(&time0);
		BS(A,0,len-1,max,min);
		QueryPerformanceCounter(&time1);
		file.open(files[i+3],ios::out);
		file<<"最大值为："<<max<<" 最小值为："<<min<<" 时间为："<<1000.0*(time1.QuadPart-time0.QuadPart)/time.QuadPart<<"ms"<<endl;
		file.close();
		len*=pow(10,k);
		k+=2;
	}
	return 0;
}