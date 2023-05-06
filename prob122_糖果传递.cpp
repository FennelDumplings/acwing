#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

using ll = long long;

int main()
{
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    ll M = accumulate(a.begin(), a.end(), (ll)0) / n;

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
    cout << ans << endl;
}
