

#include <vector>
#include <iostream>

using namespace std;

int main()
{
    int N;
    int V;
    int M;
    cin >> N >> V >> M;
    vector<int> v(N, 0);
    vector<int> w(N, 0);
    vector<int> m(N, 0);
    for(int i = 0; i < N; ++i)
        cin >> v[i] >> m[i] >> w[i];

    vector<vector<int> > dp(V + 1, vector<int>(M + 1, 0));
    for(int i = 1; i <= N; ++i)
        for(int j = V; j >= v[i - 1]; --j)
            for(int k = M; k >= m[i - 1]; --k)
            {
                dp[j][k] = max(dp[j][k], dp[j - v[i - 1]][k - m[i - 1]] + w[i - 1]);
            }


    cout << dp[V][M] << endl;
    return 0;
}
