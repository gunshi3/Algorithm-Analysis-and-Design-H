//�鲢����
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
void mergesort(int A[],int temp[],int left,int right) //�鲢���� 
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
    for(int i=0;i<3;i++)//��3�������ļ����й鲢����
    {
        file.open(files[i],ios::in);//�򿪲����ļ�
        Init(file);//��ʼ���ļ���������������A��
        file.close();
        QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ
    	mergesort(A,temp,0,100*pow(10,k)-1); //�鲢����
		QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ
		time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs 
        file.open(files[i+3],ios::out);//�򿪲����ļ�
        file<<"���ݹ�ģΪ"<<100*pow(10,k)<<"�����ݽ��й鲢����,���Ϊ"<<time*1000<<"ms"<<endl;
        print(file);
        file.close();
        k+=2;
    }
    return 0;
}