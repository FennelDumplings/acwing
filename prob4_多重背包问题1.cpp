
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    int N;
    int V;
    cin >> N >> V;
    vector<int> v(N, 0);
    vector<int> w(N, 0);
    vector<int> s(N, 0);
    for(int i = 0; i < N; ++i)
        cin >> v[i] >> w[i] >> s[i];

    vector<int> dp(V + 1, 0);
    for(int i = 1; i <= N; ++i)
        for(int j = V; j >= v[i - 1]; --j)
            for(int k = 0; k <= s[i - 1] && k * v[i - 1] <= j; ++k)
                dp[j] = max(dp[j], dp[j - k * v[i - 1]] + k * w[i - 1]);

    cout << dp[V] << endl;
    return 0;
}
