#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const double eps = 1e-6;
const int INF = 2e9;
const LL LNF = 9e18;
const int mod = 1e9+7;
const int maxn = 5e6+10;

char s[maxn];
int dp[maxn];

int main()
{
    scanf("%s",s+1);
    int l = 0, r = 0, m = 1;
    for(int i = 1; s[i]; i++)
    {
        l = l*137+s[i];
        r = r+s[i]*m, m *= 137;
        if(l==r)
            dp[i] = dp[i/2]+1;
    }

    int ans = 0;
    for(int i = 1; s[i]; i++)
        ans += dp[i];
    printf("%d\n",ans);
}