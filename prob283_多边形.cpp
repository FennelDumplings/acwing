
#include <vector>
#include <string>
#include <iostream>
#include <climits>

using namespace std;

void solve(const string& ops, const vector<int>& nums, const int max_len)
{
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n, INT_MIN));
    vector<vector<int>> dp2(n, vector<int>(n, INT_MAX));
    for(int i = 0; i < n; ++i)
    {
        dp[i][i] = nums[i];
        dp2[i][i] = nums[i];
    }
    for(int len = 2; len <= max_len; ++len)
        for(int i = 0; i <= n - len; ++i)
        {
            int j = i + len - 1;
            for(int k = i + 1; k <= j; ++k)
            {
                if(ops[k] == 't')
                {
                    dp[i][j] = max(dp[i][j], dp[i][k - 1] + dp[k][j]);
                    dp2[i][j] = min(dp2[i][j], dp2[i][k - 1] + dp2[k][j]);
                }
                else
                {
                    dp[i][j] = max(dp[i][j], dp[i][k - 1] * dp[k][j]);
                    dp[i][j] = max(dp[i][j], dp[i][k - 1] * dp2[k][j]);
                    dp[i][j] = max(dp[i][j], dp2[i][k - 1] * dp[k][j]);
                    dp[i][j] = max(dp[i][j], dp2[i][k - 1] * dp2[k][j]);
                    dp2[i][j] = min(dp2[i][j], dp[i][k - 1] * dp[k][j]);
                    dp2[i][j] = min(dp2[i][j], dp[i][k - 1] * dp2[k][j]);
                    dp2[i][j] = min(dp2[i][j], dp2[i][k - 1] * dp[k][j]);
                    dp2[i][j] = min(dp2[i][j], dp2[i][k - 1] * dp2[k][j]);
                }
            }
        }
    int ans = dp[0][max_len - 1];
    vector<int> cands(1, 0);
    for(int i = 1; i < max_len; ++i)
    {
        if(dp[i][i + max_len - 1] > ans)
        {
            ans = dp[i][i + max_len - 1];
            cands.clear();
            cands.push_back(i);
        }
        else if(dp[i][i + max_len - 1] == ans)
            cands.push_back(i);
    }
    cout << ans << endl;
    for(int i: cands)
        cout << i + 1 << " ";
    cout << endl;
}

int main()
{
    int N;
    cin >> N;
    string ops(N, ' ');
    vector<int> nums(N);
    for(int i = 0; i < N; ++i)
    {
        cin >> ops[i];
        cin >> nums[i];
    }
    nums.insert(nums.end(), nums.begin(), nums.end());
    ops.insert(ops.end(), ops.begin(), ops.end());
    solve(ops, nums, N);
};
