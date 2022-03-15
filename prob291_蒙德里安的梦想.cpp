#include <iostream>
#include <vector>

using namespace std;

bool check(int x)
{
    // x 二进制的连续 1 长度均为偶数
    while(x > 0)
    {
        int len = 0;
        while(x > 0 && (x & 1) == 1)
        {
            ++len;
            x >>= 1;
        }
        if(len & 1)
            return false;
        if(x == 0)
            break;
        x >>= 1;
    }
    return true;
}

int main()
{
    const int MAX_M = 11;
    int N = 11;
    vector<vector<vector<int>>> dp_all(MAX_M + 1);
    for(int M = 1; M <= 11; ++M)
    {
        vector<vector<int>> dp(N + 1, vector<int>(1 << M));
        dp[0][0] = 1;
        for(int i = 1; i <= N; ++i)
        {
            for(int s = 0; s < (1 << 11) - 1; ++s)
            {
                for(int t = 0; t < (1 << 11) - 1; ++t)
                {
                    if((s & t) != 0)
                        continue;
                    if(!check(s | t))
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
