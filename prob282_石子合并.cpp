// prob282: 石子合并
// https://www.acwing.com/problem/content/284/

// 输入格式
// 第一行一个数N表示石子的堆数N。
//
// 第二行N个数，表示每堆石子的质量(均不超过1000)。
//
// 输出格式
// 输出一个整数，表示最小代价。
//
// 数据范围
// 1≤N≤300

#include <iostream>
#include <vector>

using namespace std;

int range_sum(const vector<int>& sums, int i, int j)
{
    return sums[j + 1] - sums[i];
}

void solve(const vector<int>& stones)
{
    int n = stones.size();
    if(n == 1)
    {
        cout << 0 << endl;
        return;
    }
    vector<int> sums(n + 1, 0);
    for(int i = 1; i <=n ; ++i)
        sums[i] = sums[i - 1] + stones[i - 1];
    vector<vector<int> > dp(n, vector<int>(n, 0));
    for(int j = 1; j < n; ++j)
        for(int i = j - 1; i >= 0; --i)
        {
            dp[i][j] = range_sum(sums, i, j);
            int partition_num = j - i;
            int mx = dp[i][i] + dp[i + 1][j];
            for(int k = 1; k < partition_num; ++k)
                mx = min(mx, dp[i][i + k] + dp[i + 1 + k][j]);
            dp[i][j] += mx;
        }
    cout << dp[0][n - 1] << endl;
}

int main()
{
    int N;
    cin >> N;
    vector<int> stones(N, 0);
    for(int i = 0; i < N; ++i)
        cin >> stones[i];
    solve(stones);
}
