//高级模运算
#include <stdio.h>
int m, h;
long long A, B, res = 0;
long long binPow(long long x, long long y)
{ 
    long long ans = 1;
    while (y != 0)
    {
        if (y % 2 == 1)
            ans = ans * x % m;
        y /= 2;
        x = x * x % m;
    }
    return ans;
}
int main()
{
    scanf("%d%d", &m, &h);
    for (int i = 0; i < h; i++)
    {
        scanf("%d%d", &A, &B);
        res += binPow(A, B);
    }
    printf("%lld\n", res % m);
    return 0;
}