#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

using ll = long long;

ll solve(vector<int>& a)
{
    // 解决 a 上的环形均分纸牌问题，返回最小交换次数，不满足则返回 -1
    int n = a.size();
    ll sum = accumulate(a.begin(), a.end(), (ll)0);
    if(sum % n != 0)
        return -1;
    ll M = sum / n;

    vector<ll> A(n);
    for(int i = 0; i < n; ++i)
        A[i] = a[i] - M;

    vector<ll> Sums(n + 1);
    for(int i = 1; i <= n; ++i)
        Sums[i] = Sums[i - 1] + A[i - 1];
    sort(Sums.begin() + 1, Sums.end());

    int k = n / 2 + 1; // 从 k 与 k - 1 之间断开
    int median = Sums[k];
    ll ans = 0;
    for(int i = 1; i <= n; ++i)
        ans += abs(Sums[i] - median);

    return ans;
}

int main()
{
    int N, M, T;
    cin >> N >> M >> T;
    vector<int> a(N); // N 行感兴趣的个数
    vector<int> b(M); // M 列感兴趣的个数
    for(int i = 0; i < T; ++i)
    {
        int x, y;
        cin >> x >> y;
        a[x - 1]++;
        b[y - 1]++;
    }
    ll row_result = solve(a);
    ll col_result = solve(b);
    if(row_result == -1 && col_result == -1)
        cout << "impossible";
    else if(row_result != -1 && col_result != -1)
        cout << "both " << row_result + col_result;
    else if(row_result != -1)
        cout << "row " << row_result;
    else
        cout << "column " << col_result;
}
