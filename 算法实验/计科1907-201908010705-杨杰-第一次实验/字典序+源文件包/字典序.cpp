//�ֵ�������
#include <iostream>
#include <fstream>
#include <string.h>
#include <windows.h>
using namespace std;
ofstream outfile("zidianxu_out.txt",ios::out);
int com(int m,int n) //���������
{
    int result=1;
    for(int i=0;i<n;i++)
        result=result*(m-i)/(i+1);
    return result;
}
int num(char a,char b,int l) //�������a��ĸ��ͷ������b��ĸ��ͷ������Ϊl�������ַ�������
{
    int sum=0;
    for(int i=a;i<=b;i++)
        sum+=com(122-i,l-1);
    return sum;
}
void fun(string s) //��������ַ������ֵ��е��ֵ���
{
    int len=s.length();
    int sum=0;
    for(int i=1;i<len;i++)
        sum+=num('a',char(123-i),i);
    sum+=num('a',s[0]-1,len);
    int k=1;
    for(int i=len-1;i>0;i--)
    {
            sum+=num(s[k-1]+1,s[k]-1,i); 
            //sum+=num(s[k-1]+1,s[k++]-1,i);
            k++;
    }
    outfile<<"�����ַ���"<<s<<"���ֵ���,���Ϊ"<<sum+1<<endl;
}
int main()
{
    ifstream infile("zidianxu_in.txt",ios::in);
    int x=0;
    infile>>x;
    string str;
    double time=0;
	LARGE_INTEGER nFreq,nBeginTime,nEndTime;
    while(infile>>str)
    {
        QueryPerformanceFrequency(&nFreq);
        QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ
        fun(str);
        QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ
        time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
        outfile<<"����ʱ��Ϊ"<<time*1000<<"ms"<<endl;
    }
    infile.close();
    outfile.close();
    return 0;
}