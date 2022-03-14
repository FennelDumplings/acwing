#include <iostream>
#include <vector>

using namespace std;

void dfs(const vector<vector<int>>& g, const vector<int>& H, int u, vector<int>& dp1, vector<int>& dp2)
{
    if(dp1[u] != -129)
        return;
    dp1[u] = H[u];
    dp2[u] = 0;
    for(int v: g[u])
    {
        dfs(g, H, v, dp1, dp2);
        dp1[u] += dp2[v];
        dp2[u] += max(dp1[v], dp2[v]);
    }
}

int main()
{
    int N;
    cin >> N;
    vector<int> H(N, -1);
    for(int i = 0; i < N; ++i)
        cin >> H[i];
    vector<vector<int>> g(N);
    vector<bool> is_root(N, true);
    for(int i = 0; i < N - 1; ++i)
    {
        int L, K;
        cin >> L >> K;
        g[K - 1].push_back(L - 1);
        is_root[L - 1] = false;
    }
    int root = -1;
    for(int i = 0; i < N; ++i)
        if(is_root[i])
        {
            root = i;
            break;
        }
    vector<int> dp1(N, -129);
    vector<int> dp2(N, -129);
    dfs(g, H, root, dp1, dp2);
    cout << max(dp1[root], dp2[root]) << endl;
}
