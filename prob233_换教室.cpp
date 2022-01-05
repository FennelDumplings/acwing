#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

vector<vector<int>> adj;
vector<vector<double>> dp1, dp2;
vector<int> c, d;
vector<double> p;
vector<vector<int>> dist;
int n;

double solve2(int i, int j);

double solve1(int i, int j)
{
    if(i == n)
        return dp1[i][j] = 0.0;
    if(dp1[i][j] > -0.5)
        return dp1[i][j];
    double ans = dist[c[i]][c[i + 1]] + solve1(i + 1, j);
    if(j > 0)
    {
        double tmp = p[i + 1] * (dist[c[i]][d[i + 1]] + solve2(i + 1, j - 1));
        tmp += (1 - p[i + 1]) * (dist[c[i]][c[i + 1]] + solve1(i + 1, j - 1));
        ans = min(ans, tmp);
    }
    return dp1[i][j] = ans;
}

double solve2(int i, int j)
{
    if(i == n)
        return dp2[i][j] = 0.0;
    if(dp2[i][j] > -0.5)
        return dp2[i][j];
    double ans = dist[d[i]][c[i + 1]] + solve1(i + 1, j);
    if(j > 0)
    {
        double tmp = p[i + 1] * (dist[d[i]][d[i + 1]] + solve2(i + 1, j - 1));
        tmp += (1 - p[i + 1]) * (dist[d[i]][c[i + 1]] + solve1(i + 1, j - 1));
        ans = min(ans, tmp);
    }
    return dp2[i][j] = ans;
}

int main()
{
    int m, v, e;
    cin >> n >> m >> v >> e;
    c.assign(n + 1, -1);
    for(int i = 0; i < n; ++i)
        cin >> c[i + 1];
    d.assign(n + 1, -1);
    for(int i = 0; i < n; ++i)
        cin >> d[i + 1];
    p.assign(n + 1, -1);
    for(int i = 0; i < n; ++i)
        cin >> p[i + 1];
    adj.assign(v + 1, vector<int>(v + 1, -1));
    for(int i = 1; i <= v; ++i)
        adj[i][i] = 0;
    for(int i = 0; i < e; ++i)
    {
        int a, b, w;
        cin >> a >> b >> w;
        adj[a][b] = w;
        adj[b][a] = w;
    }
    dist = adj;
    // 遍历所有节点，其中 k 是用于松弛的点
    for(int k = 1; k <= v; ++k)
        for(int i = 1; i <= v; ++i)
            for(int j = 1; j <= v; ++j)
                // 使用 k 松弛 i > j 的最短路径
                if(dist[i][k] != -1 && dist[k][j] != -1)
                {
                    if(dist[i][j] != -1)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    else
                        dist[i][j] = dist[i][k] + dist[k][j];
                }
    dp1.assign(n + 1, vector<double>(n + 1, 1e9));
    dp2.assign(n + 1, vector<double>(n + 1, 1e9));
    // double ans = min(solve1(1, m), p[1] * solve2(1, m - 1) + (1 - p[1]) * solve1(1, m - 1));
    dp1[1][0] = 0;
    dp2[1][1] = 0;
    for(int i = 2; i <= n; ++i)
    {
        dp1[i][0] = dist[c[i - 1]][c[i]] + dp1[i - 1][0];
        for(int j = 1; j <= min(i, m); ++j)
        {
            dp1[i][j] = min(dist[c[i - 1]][c[i]] + dp1[i - 1][j]
                           ,p[i - 1] * (dist[d[i - 1]][c[i]] + dp2[i - 1][j])
                               + (1 - p[i - 1]) * (dist[c[i - 1]][c[i]] + dp2[i - 1][j])
                           );
            dp2[i][j] = min(p[i] * (dist[c[i - 1]][d[i]] + dp1[i - 1][j - 1])
                               + (1 - p[i]) * (dist[c[i - 1]][c[i]] + dp1[i - 1][j - 1])
                           ,p[i] * (p[i - 1] * (dist[d[i - 1]][d[i]] + dp2[i - 1][j - 1])
                                    + (1 - p[i - 1]) * (dist[c[i - 1]][d[i]] + dp2[i - 1][j - 1])
                            ) + (1 - p[i]) * (p[i - 1] * (dist[d[i - 1]][c[i]] + dp2[i - 1][j - 1])
                                    + (1 - p[i - 1]) * (dist[c[i - 1]][c[i]] + dp2[i - 1][j - 1])
                            )
                           );
        }
    }
    double ans = 1e9;
    for(int j = 0; j <= m; ++j)
    {
        ans = min(ans, min(dp1[n][j], dp2[n][j]));
    }

    cout << std::fixed << std::setprecision(2);
    cout << ans << endl;
}
