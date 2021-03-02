#include <iostream>
#include <vector>

using namespace std;

void dfs(const vector<vector<int>>& g, int u, const int V, const vector<int>& w, vector<vector<int>>& dp)
{
    // u 必选，即至少选一门课，因此 dp[u][1 ~ V] = w[u] 而 dp[u][0] = 0
    for(int j = 1; j <= V; ++j)
        dp[u][j] = w[u];
    for(int v: g[u])
    {
        dfs(g, v, V, w, dp);
        for(int j = V; j >= 1; --j)
        {
            // 当前子树 u 对应的物品组的虚拟物品的体积为 j
            for(int k = 0; k <= j - 1; ++k)
            {
                // 从子树 v 中选择体积为 k 的虚拟物品，价值为 dp[v][k]
                dp[u][j] = max(dp[u][j], dp[u][j - k] + dp[v][k]);
            }
        }
    }
}

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> scores(N + 1);
    vector<vector<int>> g(N + 1);
    int root = 0; // 虚拟根
    for(int u = 1; u <= N; ++u)
    {
        int fa;
        cin >> fa;
        cin >> scores[u];
        g[fa].push_back(u);
    }
    vector<vector<int>> dp(N + 1, vector<int>(M + 2));
    // dp[u][j] := 在子树 u 上最多选 j 门课的最多学分
    // 一共 N + 1 门课，虚拟根视为一门学分为零的课
    dfs(g, root, M + 1, scores, dp);
    cout << dp[root][M + 1] << endl;
}
