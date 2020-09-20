
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <iomanip>
#include <queue>

using namespace std;

const double eps = 1e-8;

struct Edge
{
    int u,v;
    int w;
    Edge(int u, int v, int w):u(u),v(v),w(w){}
};

struct To
{
    int v;
    double w;
    To(int v, double w):v(v),w(w){}
};

bool spfa(vector<vector<To> >& g, int start, vector<bool>& visited)
{
    // 与 bellman ford 相同, O(VE)
    // 可以检测负环

    int N = g.size() - 1;
    vector<double> d(N + 1, INT_MAX / 2);
    d[start] = 0;
    queue<int> q;
    q.push(start);

    // 记录每个点到 start 的节点个数
    vector<int> cnt(N + 1, 0);
    cnt[start] = 1;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(To &son: g[u])
        {
            int v = son.v;
            double w = son.w;
            if(abs(d[v] - INT_MAX / 2) < eps || d[v] > d[u] + w + eps)
            {
                cnt[v] = cnt[u] + 1;
                if(cnt[u] > N)
                    return true; // 若 son 到 start 的节点个数大于 N 了说明有负环
                // 当最短距离发生变化且不在队列中时，将该节点加入队列
                d[v] = d[u] + w;
                q.push(v);
            }
        }
    }
    for(int i = 1; i <= N; ++i)
    {
        if(abs(d[i] - INT_MAX / 2) > eps)
            visited[i] = true;
    }
    return false;
}

bool bellman_ford(vector<vector<To> >& g, int start, vector<bool>& visited)
{
    // bellman ford  O(VE)
    // 可以检测负环

    int N = g.size() - 1;
    vector<double> d(N + 1, INT_MAX / 2);
    d[start] = 0.0;

    // 进行 N - 1 轮松弛
    // 因为任意两点之间最短路最多包含 N - 1 条边
    for(int cnt = 1; cnt <= N; ++cnt)
    {
        // u: 源节点，v: 子节点, w: uv 的权
        bool update = false;
        for(int u = 1; u <= N; ++u)
        {
            if(abs(d[u] - INT_MAX / 2) < eps) continue;
            for(To &son: g[u])
            {
                int v = son.v;
                double w = son.w;
                // 判断能否通过 u -> v 缩短 d[v] (松弛)
                if(d[u] + w + eps < d[v])
                {
                    update = true;
                    if(cnt >= N)
                        return true; // 负环
                    d[v] = d[u] + w;
                }
            }
        }
        if(!update)
            break;
    }
    for(int i = 1; i <= N; ++i)
    {
        if(abs(d[i] - INT_MAX / 2) > eps)
            visited[i] = true;
    }
    return false;
}

bool check(const vector<int>& wv, const vector<Edge>& edges, double mid)
{
    int N = wv.size() - 1;
    vector<vector<To>> g(N + 1);
    for(const Edge &e: edges)
        g[e.u].push_back(To(e.v,  (double)mid * (double)e.w - wv[e.u]));
    vector<bool> visited(N + 1, false);
    for(int i = 1; i <= N; ++i)
    {
        if(visited[i]) continue;
        if(bellman_ford(g, i, visited))
        // if(spfa(g, i, visited))
            return true;
    }
    return false;
}

int main()
{
    // fstream fin("negacycle.test");
    int L, P;
    cin >> L >> P;
    vector<int> wv(L + 1);
    for(int i = 1; i <= L; ++i)
        cin >> wv[i];
    vector<Edge> edges;
    for(int i = 1; i <= P; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(u, v, w);
    }
    double left = 0.0, right = 1e9;
    while(abs(right - left) > eps)
    {
        double mid = (left + right) / 2;
        if(check(wv, edges, mid))
            left = mid;
        else
            right = mid;
    }
    cout << setiosflags(ios::fixed) << setprecision(2);
    cout << left << endl;
}
