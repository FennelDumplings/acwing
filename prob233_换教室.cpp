#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

using namespace std;

const double INF = 1e9;
const int M = 310;

int dist[M][M];
vector<vector<double>> dp1, dp2;
vector<int> c, d;
vector<double> p;
int n;

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
    memset(dist, -1, sizeof(dist));
    for(int i = 1; i <= v; ++i)
        dist[i][i] = 0;
    for(int i = 0; i < e; ++i)
    {
        int a, b, w;
        cin >> a >> b >> w;
        if(dist[a][b] == -1)
            dist[a][b] = dist[b][a] = w;
        else
            dist[a][b] = dist[b][a] = min(dist[a][b], w);
    }
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
    dp1.assign(n + 1, vector<double>(n + 1, INF));
    dp2.assign(n + 1, vector<double>(n + 1, INF));
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
            dp2[i][j] = min(dp1[i - 1][j - 1] + dist[c[i - 1]][d[i]] * p[i]
                                              + dist[c[i - 1]][c[i]] * (1 - p[i])
                           ,dp2[i - 1][j - 1] + dist[d[i - 1]][d[i]] * p[i] * p[i - 1]
                                              + dist[c[i - 1]][d[i]] * p[i] * (1 - p[i - 1])
                                              + dist[d[i - 1]][c[i]] * (1 - p[i]) * p[i - 1]
                                              + dist[c[i - 1]][c[i]] * (1 - p[i]) * (1 - p[i - 1])
                           );
        }
    }
    double ans = INF;
    for(int j = 0; j <= m; ++j)
        ans = min(ans, min(dp1[n][j], dp2[n][j]));

    cout << std::fixed << std::setprecision(2);
    cout << ans << endl;
}
