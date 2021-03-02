#include <iostream>
#include <climits>
#include <vector>

using namespace std;

vector<vector<int>> dp;

void solve(const vector<int>& U, int N, int B)
{
    for(int i = 2; i <= N; ++i)
    {
        for(int k = B; k >= 0; --k)
        {
            if(i > k)
            {
                // 第 i 小时不休息
                dp[k][0] = max(dp[k][1], dp[k][0]);
            }
            if(k > 0)
            {
                // 第 i 小时休息
                dp[k][1] = dp[k - 1][0];
                if(dp[k - 1][1] >= 0)
                    dp[k][1] = max(dp[k - 1][1] + U[i], dp[k][1]);
            }
        }
    }
}

int main()
{
    int N, B;
    cin >> N >> B;
    vector<int> U(N + 1);
    for(int i = 1; i <= N; ++i)
        cin >> U[i];

    dp.assign(B + 1, vector<int>(2, -1));
    dp[0][0] = 0;
    dp[1][1] = 0;
    solve(U, N, B);
    int ans1 = dp[B][1];
    int ans2 = dp[B][0];
    int ans = max(ans1, ans2);

    dp.assign(B + 1, vector<int>(2, -1));
    dp[1][1] = U[1];
    solve(U, N, B);
    int ans3 = dp[B][1];
    ans = max(ans, ans3);
    cout << ans << endl;
}

