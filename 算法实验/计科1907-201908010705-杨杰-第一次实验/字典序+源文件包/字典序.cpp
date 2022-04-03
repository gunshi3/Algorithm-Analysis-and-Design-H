//字典序问题
#include <iostream>
#include <fstream>
#include <string.h>
#include <windows.h>
using namespace std;
ofstream outfile("zidianxu_out.txt",ios::out);
int com(int m,int n) //计算组合数
{
    int result=1;
    for(int i=0;i<n;i++)
        result=result*(m-i)/(i+1);
    return result;
}
int num(char a,char b,int l) //计算从以a字母打头，到以b字母打头，长度为l的升序字符串个数
{
    int sum=0;
    for(int i=a;i<=b;i++)
        sum+=com(122-i,l-1);
    return sum;
}
void fun(string s) //计算给定字符串在字典中的字典序
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
    outfile<<"计算字符串"<<s<<"的字典序,结果为"<<sum+1<<endl;
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
        QueryPerformanceCounter(&nBeginTime);//开始计时
        fun(str);
        QueryPerformanceCounter(&nEndTime);//停止计时
        time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
        outfile<<"运行时间为"<<time*1000<<"ms"<<endl;
    }
    infile.close();
    outfile.close();
    return 0;
}