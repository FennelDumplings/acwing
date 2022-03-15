#include <iostream>
#include <vector>

using namespace std;

bool check(const int x, const int M)
{
    // x 二进制的连续 0 长度均为偶数
    int i = M - 1;
    while(i >= 0)
    {
        int len = 0;
        while(i >= 0 && (x >> i & 1) == 0)
        {
            ++len;
            --i;
        }
        if(len & 1)
            return false;
        while(i >= 0 && (x >> i & 1) == 1)
            --i;
    }
    return true;
}

int main()
{
    using ll = long long;
    const int MAX_M = 11;
    int N = 11;
    vector<vector<vector<ll>>> dp_all(MAX_M + 1);
    for(int M = 1; M <= MAX_M; ++M)
    {
        vector<vector<ll>> dp(N + 1, vector<ll>(1 << M));
        dp[0][0] = 1;
        for(int i = 1; i <= N; ++i)
        {
            for(int s = 0; s < (1 << M); ++s)
            {
                for(int t = 0; t < (1 << M); ++t)
                {
                    if((s & t) != 0)
                        continue;
                    if(!check(s | t, M))
                        continue;
                    dp[i][s] += dp[i - 1][t];
                }
            }
        }
        dp_all[M] = dp;
    }
    int n, m;
    while(true)
    {
        cin >> n >> m;
        if(n == 0)
            break;
        cout << dp_all[m][n][0] << endl;
    }
}
