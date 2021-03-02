
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

using ll = long long;
using PLI = pair<ll, int>;

const int N = 100010;
const int M = 17;
const ll INF = 1e12;

int n;
vector<int> H;
// nxt1[i] := 从编号 i 的城市出发，下一个最近城市的编号, -1 表示不存在
// nxt2[i] := 从编号 i 的城市出发，下一个次近城市的编号, -1 表示不存在
vector<int> nxt1, nxt2;
// dp[i][j][k] := 从城市 j 出发, 共行驶 2^i 天，k 先开车，最终会到达的城市
// dpa[i][j][k] := 从城市 j 出发，共行驶 2^i 天，k 先开车，A 行驶的距离
// dpb[i][j][k] := 从城市 j 出发，共行驶 2^i 天，k 先开车，B 行驶的距离
int dp[M][N][2];
int dpa[M][N][2], dpb[M][N][2];

void init_g()
{
    nxt1.assign(n + 1, 0);
    nxt2.assign(n + 1, 0);
    set<PLI> S;
    S.insert({INF, 0});
    S.insert({INF + 1, 0});
    S.insert({-INF, 0});
    S.insert({-INF - 1, 0});

    for(int i = n; i >= 1; --i )
    {
        PLI t(H[i], i);
        auto j = S.lower_bound(t);
        ++j;
        vector<PLI> cand;
        for(int k = 0; k < 4; ++k)
        {
            cand.push_back(*j);
            --j;
        }
        ll d1 = INF, d2 = INF;
        int p1, p2;
        for(int k = 3; k >= 0; --k)
        {
            ll d = abs(H[i] - cand[k].first);
            if(d < d1)
            {
                d2 = d1;
                d1 = d;
                p2 = p1;
                p1 = cand[k].second;
            }
            else if(d < d2)
            {
                d2 = d;
                p2 = cand[k].second;
            }
        }
        S.insert(t);
        nxt1[i] = p2;
        nxt2[i] = p1;
    }
}

void init_f()
{
    for(int i = 0; i < M; ++i)
        for(int j = 1; j <= n; ++j)
        {
            if(i == 0)
            {
                dp[0][j][0] = nxt1[j];
                dp[0][j][1] = nxt2[j];
            }
            else
            {
                for(int k = 0; k < 2; ++k)
                {
                    if(i == 1)
                        dp[1][j][k] = dp[0][dp[0][j][k]][1 - k];
                    else
                        dp[i][j][k] = dp[i - 1][dp[i - 1][j][k]][k];
                }
            }
        }
}

int get_dist(int a, int b)
{
    return abs(H[a] - H[b]);
};

void init_d()
{
    for(int i = 0; i < M; ++i)
        for(int j = 1; j <= n; ++j)
        {
            if(i == 0)
            {
                dpa[0][j][0] = get_dist(j, nxt1[j]);
                dpa[0][j][1] = 0;
                dpb[0][j][1] = get_dist(j, nxt2[j]);
                dpb[0][j][0] = 0;
            }
            else
            {
                for(int k = 0; k < 2; ++k)
                {
                    if(i == 1)
                    {
                        dpa[1][j][k] = dpa[0][j][k] + dpa[0][dp[0][j][k]][1 - k];
                        dpb[1][j][k] = dpb[0][j][k] + dpb[0][dp[0][j][k]][1 - k];
                    }
                    else
                    {
                        dpa[i][j][k] = dpa[i - 1][j][k] + dpa[i - 1][dp[i - 1][j][k]][k];
                        dpb[i][j][k] = dpb[i - 1][j][k] + dpb[i - 1][dp[i - 1][j][k]][k];
                    }
                }
            }
        }
}

void calc(int p, int X, int& la, int& lb)
{
    la = 0;
    lb = 0;
    for(int i = M - 1; i >= 0; --i)
    {
        if(dp[i][p][0] > 0 && la + lb + dpa[i][p][0] + dpb[i][p][0] <= X)
        {
            la += dpa[i][p][0];
            lb += dpb[i][p][0];
            p = dp[i][p][0];
        }
    }
}

int main()
{
    cin >> n;
    H.assign(n + 1, 0);
    for(int i = 1; i <= n; ++i)
        cin >> H[i];

    init_g();
    init_f();
    init_d();

    int X0;
    cin >> X0;
    int res = 0, max_h = 0;
    double min_ratio = INF;
    for(int i = 1; i <= n; ++i)
    {
        int la, lb;
        calc(i, X0, la, lb);
        double ratio = lb != 0 ? (double)la / lb : INF;
        if(ratio < min_ratio || (ratio == min_ratio && H[i] > max_h))
        {
            min_ratio = ratio;
            max_h = H[i];
            res = i;
        }
    }
    cout << res << endl;

    int m;
    cin >> m;
    for(int i = 0; i < m; ++i)
    {
        int s, x;
        cin >> s >> x;
        int la, lb;
        calc(s, x, la, lb);
        cout << la << " " << lb << endl;
    }
}
