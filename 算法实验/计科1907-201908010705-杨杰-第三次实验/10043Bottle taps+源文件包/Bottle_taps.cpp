#include <stdio.h>
#include <algorithm>
#define eps 1e-8
#define M 1000100
#define LL __int64
#define INF 0x3f3f3f
#define PI 3.1415926535898

using namespace std;

const int maxn = 1010;

int dp[1 << 22];
int num[maxn];
int f[maxn];
int st[maxn];
int n;

void dfs(int x, int y, int z)
{
    if (x == n)
    {
        dp[y] = z;
        return;
    }
    dfs(x + 1, y, z);
    dfs(x + 1, y | (1 << x), z + num[x]);
}

int main()
{
    while (1)
    {
        scanf("%d", &n);
        if (!n)
            break;
        for (int i = 0; i < (1 << n); i++)
            dp[i] = INF;
        for (int i = 0; i < n; i++)
            scanf("%d", &num[i]);
        dfs(0, 0, 0);
        int m;
        scanf("%d", &m);
        for (int i = 0; i < m; i++)
        {
            scanf("%d", &f[i]);
            int x;
            scanf("%d", &x);
            int sum = 0;
            int tmx;
            for (int j = 0; j < x; j++)
            {
                scanf("%d", &tmx);
                sum |= (1 << (tmx - 1));
            }
            st[i] = sum;
        }
        int kk;
        scanf("%d", &kk);
        int ans = 0;
        int p;
        for (int i = 0; i < kk; i++)
        {
            scanf("%d", &p);
            ans |= (1 << (p - 1));
        }
        int Min = INF;
        for (int i = 0; i < (1 << n); i++)
        {
            if ((i & ans) == ans)
                Min = min(Min, dp[i]);
            for (int j = 0; j < m; j++)
                dp[i | st[j]] = min(dp[i | st[j]], dp[i] + f[j]);
        }
        printf("%d\n", Min);
    }
    return 0;
}