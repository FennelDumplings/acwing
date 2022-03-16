#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void divide(int n, vector<int>& p, vector<int>& c)
{
    p.clear();
    c.clear();
    for(int i = 2; i <= sqrt(n); ++i)
    {
        if(n % i == 0)
        {
            // i 是质数
            int cnt = 0;
            while(n % i == 0)
            {
                n /= i;
                ++cnt;
            }
            p.push_back(i);
            c.push_back(cnt);
        }
    }
    if(n > 1)
    {
        // n 是质数
        p.push_back(n);
        c.push_back(1);
    }
}

const int MOD = 9901;
using ll = long long;

int quickpower2(int a, int n, int MOD) // 处理不了n是负数
{
    int ans = 1;
    while(n)
    {
        if(n & 1) ans = ((ll)ans * a) % MOD;
        a = (ll)a * a % MOD;
        n >>= 1;
    }
    return ans % MOD;
}

int sum(int p, int n)
{
    // 首项为 1，项数为 n + 1，公比为 p 的等比数列的和，模 MOD
    if(n == 0)
        return 1;
    if((n & 1) == 0)
        return ((ll)quickpower2(p, n, MOD) + sum(p, n - 1)) % MOD;
    return ((1 + (ll)quickpower2(p, (n + 1) / 2, MOD)) * sum(p, (n - 1) / 2)) % MOD;
}

// 扩展欧几里得算法
ll exgcd(ll a, ll b, ll& x, ll& y)
{
    // 求出 ax + by = gcd(a, b) 的一组特接并返回 a,b 的最大公约数 d。
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y);
    int z = x;
    x = y;
    y = z - y * (a / b);
    return d;
}

// 求 b 模 p 的乘法逆元 (b 与 p 互质)
ll inv(ll b, ll p)
{
    // 解方程 bx 与 1 模 p 同余
    // 扩展欧几里得求 bx0 + py0 = 1
    ll x0 = 0, y0 = 0;
    ll d = exgcd(b, p, x0, y0);
    if(d != 1) // b 和 p 不互质的情况不不存在逆元
        return -1;
    return (x0 % p + p) % p;
}

int sum2(int p, int n)
{
    // 首项为 1，项数为 n + 1，公比为 p 的等比数列的和，模 MOD
    return ((ll)(quickpower2(p, n, MOD) - 1) * inv((p - 1), MOD)) % MOD;
}

int main()
{
    int A, B;
    cin >> A >> B;
    if(A == 0)
        cout << 0 << endl;
    else if(B == 0)
        cout << 1 << endl;
    else
    {
        vector<int> p, c;
        divide(A, p, c);
        int ans = 1;
        int k = p.size();
        for(int i = 0; i < k; ++i)
            ans = ((ll)ans * sum2(p[i], (ll)B * c[i])) % MOD;
        cout << ans << endl;
    }
}
