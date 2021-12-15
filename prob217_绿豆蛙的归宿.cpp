#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>

using namespace std;

struct Edge
{
    int v;
    int l;
    Edge(int v, int l):v(v),l(l){}
};

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<Edge>> g(N + 1);
    vector<vector<Edge>> rg(N + 1);
    for(int i = 0; i < M; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        rg[b].push_back(Edge(a, c));
        g[a].push_back(Edge(b, c));
    }

    vector<int> outdegree(N + 1);
    for(int i = 1; i <= N; ++i)
        outdegree[i] = g[i].size();

    queue<int> q;
    q.push(N);

    vector<double> dp(N + 1);
    while(!q.empty())
    {
        int i = q.front();
        q.pop();
        int n = g[i].size();
        for(int j = 0; j < n; ++j)
            dp[i] += g[i][j].l + dp[g[i][j].v];
        if(n > 0)
            dp[i] /= n;
        for(const Edge &son: rg[i])
        {
            --outdegree[son.v];
            if(outdegree[son.v] == 0)
                q.push(son.v);
        }
    }
    cout << std::fixed << std::setprecision(2);
    cout << dp[1] << endl;
}
