

// dp[i][j] := 考虑 [0..i], 体积为 j 的方案数
// dp[i][0] = 1
// dp[i][j] = dp[i - 1][j] + dp[i - 1][j - v[i]]
// 倒序枚举 j，省略 i 这一维
// dp[j] := 体积为 j 的方案数
// dp[0] = 1
// dp[j] = dp[j] + dp[j - v[i]]

#include <vector>
#include <iostream>

using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    for(int i = 0; i < N; ++i)
        cin >> A[i];
    vector<int> dp(M + 1);
    dp[0] = 1;
    for(int i = 0; i < N; ++i)
        for(int j = M; j >= A[i]; --j)
            dp[j] += dp[j - A[i]];
    cout << dp[M] << endl;
}
