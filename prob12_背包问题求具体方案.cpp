
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int N, V;
    cin >> N >> V;
    vector<int> v(N+1, 0);
    vector<int> w(N+1, 0);

    for(int i = 0 ; i < N; i++)
        cin >> v[i] >> w[i];

    vector<vector<int> > dp(N + 1, vector<int>(V + 1, 0));

    for(int i = N; i >= 1; --i)
        for(int j = 0; j <= V; ++j)
        {
            dp[i - 1][j] = dp[i][j];
            if(j >= v[i - 1])
                dp[i - 1][j] = max(dp[i - 1][j], dp[i][j - v[i - 1]] + w[i - 1]);
        }
    // 以上 dp 枚举在 01 背包求最大价值上通过

    vector<int> result;
    int vol = V;
    for(int i = 1; i <= N; ++i)
    {
        if(vol - v[i - 1] >= 0 && dp[i - 1][vol] == dp[i][vol - v[i - 1]] + w[i - 1])
        {
            cout << i << " ";
            vol -= v[i - 1];
        }
    }

    return 0;
}
