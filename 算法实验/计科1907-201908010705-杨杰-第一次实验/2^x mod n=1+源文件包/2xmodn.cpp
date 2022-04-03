//2^x mod n = 1
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;
int main()
{
    int n,x,temp;
    ifstream infile("2xmodn_in.txt",ios::in);
    ofstream outfile("2xmodn_out.txt",ios::out);
    //while(scanf("%d",&n)!=EOF)
    while(infile>>n)
    {
        temp=2;
        if(n==1 || n%2==0)
        {
            //printf("2^? mod %d = 1\n",n);
            outfile<<"2^? mod "<<n<<" = 1"<<endl;
            continue;
        }
        for(x=1;;x++)
        {
            temp=temp%n;
            if(temp==1)
            {
                //printf("2^%d mod %d = 1\n",x,n);
                outfile<<"2^"<<x<<" mod "<<n<<" = 1"<<endl;
                break;
            }
            temp=temp<<1;
        }
    }
    infile.close();
    return 0;
}