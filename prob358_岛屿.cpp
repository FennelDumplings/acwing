#include <iostream>
#include <cmath>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

struct Edge
{
    int v;
    int L;
    int id;
    Edge(){}
    Edge(int v, int L, int id):v(v),L(L),id(id){}
};

void dfs1(const vector<vector<Edge>>& g, const int u, vector<int>& visited, vector<int>& circle, vector<int>& dist, vector<Edge>& path)
{
    // 遍历基环树、记录环
    visited[u] = 1;
    for(const Edge& e: g[u])
    {
        int v = e.v;
        int l = path.size();
        int id = e.id;
        if(l > 0 && path[l - 1].id == id)
            continue;
        if(visited[v] == 2)
            continue;
        if(visited[v] == 1)
        {
            // 找到环，记录环
            circle.push_back(u);
            dist.push_back(path[l - 1].L);
            int i = l - 1;
            while(path[i].v != v)
            {
                circle.push_back(path[i].v);
                dist.push_back(path[i - 1].L);
                i--;
            }
            circle.push_back(v);
            dist.push_back(e.L);
            continue;
        }
        path.push_back(Edge(u, e.L, e.id));
        dfs1(g, v, visited, circle, dist, path);
        path.pop_back();
    }
    visited[u] = 2;
}

long long dfs2(const vector<vector<Edge>>& g, const int u, long long& ans, const int sl, const int sr, const int prev)
{
    // 树形 DP 求直径，在 ans 中更新，返回最大深度
    long long max1 = 0;
    long long max2 = 0;
    for(const Edge& e: g[u])
    {
        int v = e.v;
        if(v == sl || v == sr)
            continue;
        if(v == prev)
            continue;
        long long max_d = dfs2(g, v, ans, sl, sr, u);
        if(max_d + e.L > max1)
        {
            max2 = max1;
            max1 = max_d + e.L;
        }
        else if(max_d + e.L > max2)
            max2 = max_d + e.L;
        ans = max(ans, max1 + max2);
    }
    return max1;
}

long long solve(const vector<vector<Edge>>& g, const int N, const int s, vector<int>& visited, vector<long long>& d)
{
    vector<int> circle;
    vector<int> dist;
    vector<Edge> path;
    // 搜索环
    dfs1(g, s, visited, circle, dist, path);

    int t = circle.size();
    long long ans1 = 0; // 第一种情况
    for(int i = 0; i < t; ++i)
    {
        int si = circle[i];
        int sl = circle[(i + t - 1) % t];
        int sr = circle[(i + 1) % t];
        // 树的直径
        d[si] = dfs2(g, si, ans1, sl, sr, -1);
    }

    // circle[i..j]：d[circle[i]] + d[circle[j]] + dist[i, j] 的最大值
    // 枚举 j，找一个 max(0, j - t + 1) <= i <= j - 1，使得 d[circle[i]] + d[circle[j]] + sums[j] - sums[i] 最大
    circle.insert(circle.end(), circle.begin(), circle.end());
    dist.insert(dist.end(), dist.begin(), dist.end());
    vector<long long> sums(t * 2 + 1);
    for(int i = 1; i <= t * 2; ++i)
        sums[i] = sums[i - 1] + dist[i - 1];

    deque<int> deq;
    deq.push_back(0);
    long long ans2 = 0; // 第二种情况
    for(int j = 1; j < t * 2; ++j)
    {
        // deq 中是 [max(0, j - t + 1), j - 1]

        // 更新答案
        ans2 = max(ans2, d[circle[j]] + sums[j] + d[circle[deq.front()]] - sums[deq.front()]);

        // 插入 j 保持单调性
        while(!deq.empty() && d[circle[deq.back()]] - sums[deq.back()] <= d[circle[j]] - sums[j])
            deq.pop_back();
        deq.push_back(j);

        // 弹出 <=
        if(!deq.empty() && deq.front() < j - t + 2)
            deq.pop_front();
    }

    return max(ans1, ans2);
}

int main()
{
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;
    vector<vector<Edge>> g(N + 1);
    for(int i = 1; i <= N; ++i)
    {
        int a, L;
        cin >> a >> L;
        g[i].emplace_back(a, L, i);
        g[a].emplace_back(i, L, i);
    }

    long long ans = 0;
    vector<int> visited(N + 1);
    vector<long long> d(N + 1);
    for(int s = 1; s <= N; ++s)
    {
        if(visited[s] == 0)
        {
            ans += solve(g, N, s, visited, d);
        }
    }

    cout << ans << endl;
}
