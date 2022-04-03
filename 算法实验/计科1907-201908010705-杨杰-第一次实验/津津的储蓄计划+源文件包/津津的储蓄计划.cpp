#include <iostream>
using namespace std;
int main()
{
    int a,b,sum=0,c=0;
    bool flag=true;
    for(int i=1;i<=12;i++)
    {
        cin>>a;
        if(flag && c+300<a)
        {
            flag=false;
            cout<<-i<<endl;
        }
        else
        {
            sum+=(c+300-a)/100*100;
            c=(c+300-a)%100;
        }
    }
    if(flag) cout<<c+sum*1.2<<endl;
    return 0;
}