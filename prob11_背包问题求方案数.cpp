
#include <vector>
#include <iostream>
#include <climits>


using namespace std;

int main()
{
    int N;
    int V;
    int mod = 1e9 + 7;
    cin >> N >> V;
    vector<int> v(N, 0);
    vector<int> w(N, 0);
    for(int i = 0; i < N; ++i)
        cin >> v[i] >> w[i];

    vector<int> dp(V + 1, INT_MIN);
    vector<int> g(V + 1, 0);
    g[0] = 1, dp[0] = 0;

    for(int i = 1; i <= N; ++i)
        for(int j = V; j >= v[i - 1]; --j)
        {
            int s = 0;
            int t = max(dp[j], dp[j - v[i - 1]] + w[i - 1]);
            if(dp[j] == t) s += g[j];
            if(dp[j - v[i - 1]] + w[i - 1] == t) s += g[j - v[i - 1]];
            if(s >= mod) s -= mod;
            dp[j] = t;
            g[j] = s;
        }

    int maxw = 0;
    for(int i = 0; i <= V; ++i)
        maxw = max(maxw, dp[i]);

    int result = 0;
    for(int i = 0; i <= V; ++i)
        if(maxw == dp[i])
        {
            result += g[i];
            if(result > mod) result -= mod;
        }

    cout << result << endl;
    return 0;
}
