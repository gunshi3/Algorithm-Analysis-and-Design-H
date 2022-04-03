//金币阵列问题
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
int count=0;
int temparr[100][100],a[100][100],b[100][100];
void trans1(int i,int n) //对某一行进行翻转
{
    for(int j=0;j<n;j++)
        temparr[i][j]=1-temparr[i][j];// a[j][i]^=1; //异或运算也可以
    count++;
}
void trans2(int i,int j,int m) //对两列进行互换
{
    if(i!=j)
    {
        for(int k=0;k<m;k++)
        {
            int temp=temparr[k][i];
            temparr[k][i]=temparr[k][j];
            temparr[k][j]=temp;
        }
        count++;
    }
}
bool same(int i,int j,int m) //判断两列是否相同
{
    int k;
    bool flag=true;
    for(k=0;k<m;k++)
    {
        if(temparr[k][j]!=b[k][i])
        {
            flag=false;
            break;
        }
    }
    return flag;
}
int main()
{
    ifstream infile("jinbi_in.txt",ios::in);
    ofstream outfile("jinbi_out.txt",ios::out);
    int t=0;
    infile>>t;
    int m=0,n=0,i,j,k;
    double time=0;
	LARGE_INTEGER nFreq,nBeginTime,nEndTime;
    while(infile>>m>>n)
    {
        int answer=9999;
        QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&nBeginTime);//开始计时
        for(i=0;i<m;i++)
            for(j=0;j<n;j++)
                infile>>a[i][j];
        for(i=0;i<m;i++)
            for(j=0;j<n;j++)
                infile>>b[i][j];
        for(k=0;k<m;k++)
        {
            //copyarray
            for(i=0;i<m;i++)
                for(j=0;j<n;j++)
                    temparr[i][j]=a[i][j];
            count=0;
            trans2(0,k,m);//将第k列与第0列互换
            //对所有行的第0个元素与目标数组对应的元素进行比较，如果不同,进行行翻转
            for(i=0;i<m;i++)
                if(temparr[i][0]!=b[i][0])
                    trans1(i,n);
            //检查每一列是否满足条件
            bool found;
            for(i=0;i<n;i++)
            {
                found=false;
                if(same(i,i,m))
                {
                    found=true;
                    continue;
                }
                for(j=i+1;j<n;j++)//判断是否可以通过后续列的交换达到目的
                {
                    if(same(i,j,m))
                    {
                        trans2(i,j,m);
                        found=true;
                        break;
                    }
                }
                if(found==false)
                    break;
            }
            if(found==true && count<answer) answer=count;
        }
        QueryPerformanceCounter(&nEndTime);//停止计时
		time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为ms 
        if(answer<9999)
            outfile<<"程序耗时"<<time*1000<<"ms,结果为"<<answer<<endl;
        else
            outfile<<"程序耗时"<<time*1000<<"ms,结果为"<<-1<<endl;
    }
//整体思路，将每一列运用列交换作为第0列，然后对每一行进行判断，如果元素与目标元素不相等,进行翻转处理，再向后判断相关列是否相同。
    infile.close();
    outfile.close();
    return 0;
}