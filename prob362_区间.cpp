
// s[i] := [0..i] 中最少选择的数字个数
// s[b[i]] - a[a[i] - 1] >= c[i]
// s[k] - s[k - 1] >= 0
// s[k] - s[k - 1] <= 0
// 0 <= a[i], b[i] <= 50000
// 需要 -1 ~ 50000
// 映射：a[i] -> a[i] + 1; b[i] -> b[i] + 1
// 节点：0 ~ 50001

#include <vector>
#include <iostream>
#include <queue>

using namespace std;

struct To
{
    int v, w;
    To(int v, int w):v(v),w(w){}
};

vector<int> spfa(const vector<vector<To>>& g, int st)
{
    int N = g.size();
    vector<int> d(N, -1);
    d[st] = 0;
    queue<int> q;
    q.push(st);
    vector<int> cnt(N, 0);
    cnt[st] = 1;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(const To &son: g[u])
        {
            int v = son.v;
            int w = son.w;
            if(d[v] < d[u] + w)
            {
                cnt[v] = cnt[u] + 1;
                if(cnt[v] > N)
                    return {};
                d[v] = d[u] + w;
                q.push(v);
            }
        }
    }
    return d;
}

int main()
{
    int n;
    cin >> n;
    int N = 50002;
    vector<vector<To>> g(N);
    for(int i = 1; i < N; ++i)
    {
        g[i].push_back(To(i - 1, -1));
        g[i - 1].push_back(To(i, 0));
    }
    for(int i = 0; i < n; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back(To(b + 1, c));
    }
    vector<int> d = spfa(g, 0);
    if(d.empty())
        cout << -1 << endl;
    else
        cout << d[N - 1] << endl;
}
