
/*
 * dp[i][j] := [0..i] 上，和为 j 的方案数
 * dp[i][j] = dp[i - 1][j] + dp[i][j - v[i]]
 *
 * 从前往后枚举 j，省略 i 这一维
 * dp[j] := 和为 j 的方案数
 * dp[j] = dp[j] + dp[j - v[i]]
 */

#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

const ll MOD = 2147483648;

int main()
{
    int N;
    cin >> N;
    vector<ll> dp(N + 1);
    dp[0] = 1;
    for(int i = 1; i <= N; ++i)
        for(int j = i; j <= N; ++j)
            dp[j] = (dp[j] + dp[j - i]) % MOD;
    cout << (dp[N] - 1 + MOD) % MOD << endl;
}
