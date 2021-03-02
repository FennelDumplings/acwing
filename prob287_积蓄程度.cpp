#include <vector>
#include <iostream>

using namespace std;

struct EdgeTo
{
    int v;
    int w;
    EdgeTo(int v, int w):v(v),w(w){}
};

void dfs1(const vector<vector<EdgeTo>>& g, int u, int fa, vector<int>& dpdown, vector<int>& degrees)
{
    for(const EdgeTo &son: g[u])
    {
        int v = son.v;
        ++degrees[u];
        if(v == fa)
            continue;
        dfs1(g, v, u, dpdown, degrees);
        if(degrees[v] > 1)
            dpdown[u] += min(son.w, dpdown[v]);
        else
            dpdown[u] += son.w;
    }
}

void dfs2(const vector<vector<EdgeTo>>& g, int u, int fa, const vector<int>& dpdown, vector<int>& dpup, int& ans, const vector<int>& degrees)
{
    ans = max(ans, dpdown[u] + dpup[u]);
    for(const EdgeTo &son: g[u])
    {
        int v = son.v;
        if(v == fa)
            continue;
        if(degrees[u] > 1)
            dpup[v] = min(dpdown[u] + dpup[u] - min(dpdown[v], son.w), son.w);
        else
            dpup[v] = son.w;
        dfs2(g, v, u, dpdown, dpup, ans, degrees);
    }
}

void solve()
{
    int N;
    cin >> N;
    vector<vector<EdgeTo>> g(N + 1);
    for(int i = 1; i <= N -1; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    int root = 1;
    vector<int> dpdown(N + 1);
    vector<int> degrees(N + 1);
    dfs1(g, root, -1, dpdown, degrees);
    vector<int> dpup(N + 1);
    int ans = 0;
    dfs2(g, root, -1, dpdown, dpup, ans, degrees);
    cout << ans << endl;
}

int main()
{
    int T;
    cin >> T;
    for(int i = 1; i <= T; ++i)
        solve();
}
