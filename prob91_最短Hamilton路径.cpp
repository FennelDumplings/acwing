#include <vector>
#include <iostream>
#include <climits>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
        {
            cin >> a[i][j];
        }
    vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX / 2));
    dp[1][0] = 0;
    for(int s = 2; s < (1 << n); ++s)
    {
        for(int v = 0; v < n; ++v)
        {
            if((s >> v & 1) == 0)
                continue;
            for(int u = 0; u < n; ++u)
            {
                if(u == v)
                    continue;
                if((s >> u & 1) == 0)
                    continue;
                dp[s][v] = min(dp[s][v], dp[s ^ (1 << v)][u] + a[u][v]);
            }
        }
    }
    cout << dp[(1 << n) - 1][n - 1] << endl;;
}
