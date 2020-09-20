#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

const int MOD = 1e9 + 7;
using ll = long long;

// 快速幂求逆元

int quickpower2(int a, int n, int m) // 处理不了n是负数
{
    int ans = 1;
    while(n)
    {
        if(n & 1) ans = ((ll)ans * a) % m;
        a = (ll)a * a % m;
        n >>= 1;
    }
    return ans;
}

ll get_inv(ll b, ll p)
{
    return quickpower2(b, p - 2, p);
}

// 预处理逆元

vector<int> inv;

void init(int N)
{
    inv.assign(N, -1);
    for(int i = 1; i < N; ++i)
        inv[i] = get_inv(i, MOD);
}

int C(ll n, int m, int MOD)
{
    // n < 0 和 n < m 的情况在调用方处理
    n %= MOD;
    int ans = 1;
    for(int i = 0; i < m; ++i)
        ans = (ll)ans * (n - i) % MOD;
    for(int i = 1; i <= m; ++i)
        ans = (ll)ans * inv[i] % MOD;
    return ans;
}

int main()
{
    ll N, M;
    cin >> N >> M;
    vector<ll> A(N);
    for(int i = 1; i <= N; ++i)
        cin >> A[i - 1];

    init(N);

    int ans = 0;
    for(int x = 0; x <= pow(2, N) - 1; ++x)
    {
        // 枚举 x 中所有为 1 的位
        ll n = N + M;
        int p = 0; // x 中有 p 个 1
        for(int i = 0; i < N; ++i)
        {
            if(x >> i & 1)
            {
                ++p;
                n -= A[i];
            }
        }
        n -= (p + 1);
        if(n < 0 || n < N - 1) continue;
        if(p & 1)
            ans = (ans - C(n, N - 1, MOD) + MOD) % MOD;
        else
            ans = (ans + C(n, N - 1, MOD)) % MOD;
    }
    cout << (ans + MOD) % MOD << endl;
}
