
#include<iostream>
#include<vector>
using namespace std;

void dfs(int x, int V, vector<vector<int> >& dp, vector<vector<int> >& g, vector<int>& v, vector<int>& w)
{
    for(int i = v[x]; i <= V; i++) dp[x][i] = w[x];//点x必须选，所以初始化f[x][v[x] ~ m]= w[x]
        for(int i = 0;i < (int)g[x].size(); i++)
        {
            int y = g[x][i];
            dfs(y, V, dp, g, v, w);
            for(int j = V; j >= v[x]; j--)//j的范围为v[x]~V, 小于v[x]无法选择以x为子树的物品
            {
                for(int k = 0; k <= j - v[x]; k++)//分给子树y的空间不能大于j-v[x],不然都无法选根物品x
                {
                    dp[x][j] = max(dp[x][j], dp[x][j-k] + dp[y][k]);
                }
            }
        }
}

int main()
{
    int N,V;
    cin >> N >> V;
    vector<int> v(N + 1, 0);
    vector<int> w(N + 1, 0);

    // dp[x][v]表达选择以x为子树的物品，在容量不超过v时所获得的最大价值
    vector<vector<int> > dp(N + 1, vector<int>(V + 1, 0));
    vector<vector<int> > g(N + 1, vector<int>());

    int root;
    for(int i = 1; i <= N; i++)
    {
        int fa;
        cin >> v[i] >> w[i] >> fa;
        if(fa == -1)
            root = i;
        else
            g[fa].push_back(i);
    }

    dfs(root, V, dp, g, v, w);

    cout << dp[root][V];
    return 0;
}






