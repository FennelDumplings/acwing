

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
    for(int i = 0; i < N; ++i)
        cin >> v[i] >> w[i];

    vector<int> dp(V + 1, 0);
    for(int i = 1; i <= N; ++i)
        for(int j = v[i - 1]; j <= V; ++j)
            dp[j] = max(dp[j], dp[j - v[i - 1]] + w[i - 1]);


    cout << dp[V] << endl;
    return 0;
}
