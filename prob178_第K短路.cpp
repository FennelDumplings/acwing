#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <climits>
#include <unordered_set>

using namespace std;

struct State
{
    int u, d;
    int h;
    State(int u, int d, int h=0):u(u),d(d),h(h){}
};

struct Cmp
{
    bool operator()(const State& s1, const State& s2) const
    {
        return s1.d + s1.h > s2.d + s2.h;
    }
};

struct To
{
    int v, w;
    To(int v, int w):v(v),w(w){}
};

vector<int> dijkstra(const vector<vector<To>>& rg, const int T)
{
    priority_queue<State, vector<State>, Cmp> pq;
    pq.push(State(T, 0));
    int N = rg.size() - 1;
    vector<int> d(N + 1, INT_MAX / 2);
    while(!pq.empty())
    {
        State cur = pq.top();
        pq.pop();
        if(d[cur.u] < cur.d)
            continue;
        for(const To &son: rg[cur.u])
        {
            if(cur.d + son.w >= d[son.v])
                continue;
            d[son.v] = cur.d + son.w;
            pq.push(State(son.v, cur.d + son.w));
        }
    }
    return d;
}

vector<int> dijkstra_array(const vector<vector<To>>& rg, const int T)
{
    int N = rg.size() - 1;
    vector<int> d(N + 1, INT_MAX / 2);
    for(const To &son: rg[T])
        d[son.v] = son.w;
    vector<bool> got(N + 1, false);
    for(int cnt = 1; cnt <= N - 1; ++cnt)
    {
        int minx = INT_MAX / 2;
        int u = -1;
        for(int i = 1; i <= N; ++i)
        {
            if(!got[i] && d[i] < minx)
            {
                minx = d[i];
                u = i;
            }
        }
        if(u == -1)
            return d;
        got[u] = true;
        for(const To &son: rg[u])
            d[son.v] = min(d[son.v], d[u] + son.w);
    }
    return d;
}

int h(const int s, const vector<int>& rd)
{
    return rd[s];
}

int solve(const vector<vector<To>>& g, int S, int T, int K, const vector<int>& rd)
{
    priority_queue<State, vector<State>, Cmp> pq;
    pq.push(State(S, 0, h(S, rd)));
    int N = g.size() - 1;
    vector<int> cnts(N + 1, K);
    if(S == T)
        ++cnts[T];
    while(!pq.empty())
    {
        State cur = pq.top();
        pq.pop();
        --cnts[cur.u];
        if(cnts[T] == 0)
            return cur.d;
        for(const To &son: g[cur.u])
        {
            if(rd[son.v] < INT_MAX / 2 && cnts[son.v] > 0)
                pq.push(State(son.v, cur.d + son.w, h(son.v, rd)));
        }
    }
    return -1;
}

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<To>> g(N + 1);
    vector<vector<To>> rg(N + 1); // 用于求所有可以到达 T 的上游节点
    for(int i = 1; i <= M; ++i)
    {
        int a, b, l;
        cin >> a >> b >> l;
        g[a].push_back(To(b, l));
        rg[b].push_back(To(a, l));
    }
    int S, T, K;
    cin >> S >> T >> K;

    // 记录反图中 T 可以到达的所有节点集合 setting
    vector<int> rd = dijkstra_array(rg, T);
    // vector<int> rd = dijkstra(rg, T);
    if(rd[T] == INT_MAX / 2)
    {
        cout << "-1" << endl;
        return 0;
    }
    int ans = solve(g, S, T, K, rd);
    if(ans == -1)
        cout << "-1" << endl;
    else
        cout << ans << endl;
}
