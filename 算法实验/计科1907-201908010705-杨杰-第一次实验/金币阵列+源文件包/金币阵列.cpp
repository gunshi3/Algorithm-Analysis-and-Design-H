//�����������
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
int count=0;
int temparr[100][100],a[100][100],b[100][100];
void trans1(int i,int n) //��ĳһ�н��з�ת
{
    for(int j=0;j<n;j++)
        temparr[i][j]=1-temparr[i][j];// a[j][i]^=1; //�������Ҳ����
    count++;
}
void trans2(int i,int j,int m) //�����н��л���
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
bool same(int i,int j,int m) //�ж������Ƿ���ͬ
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
		QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ
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
            trans2(0,k,m);//����k�����0�л���
            //�������еĵ�0��Ԫ����Ŀ�������Ӧ��Ԫ�ؽ��бȽϣ������ͬ,�����з�ת
            for(i=0;i<m;i++)
                if(temparr[i][0]!=b[i][0])
                    trans1(i,n);
            //���ÿһ���Ƿ���������
            bool found;
            for(i=0;i<n;i++)
            {
                found=false;
                if(same(i,i,m))
                {
                    found=true;
                    continue;
                }
                for(j=i+1;j<n;j++)//�ж��Ƿ����ͨ�������еĽ����ﵽĿ��
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
        QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ
		time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪms 
        if(answer<9999)
            outfile<<"�����ʱ"<<time*1000<<"ms,���Ϊ"<<answer<<endl;
        else
            outfile<<"�����ʱ"<<time*1000<<"ms,���Ϊ"<<-1<<endl;
    }
//����˼·����ÿһ�������н�����Ϊ��0�У�Ȼ���ÿһ�н����жϣ����Ԫ����Ŀ��Ԫ�ز����,���з�ת����������ж�������Ƿ���ͬ��
    infile.close();
    outfile.close();
    return 0;
}