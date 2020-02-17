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
#include <climits>

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

// 四边形不等式优化
void solve_optim(const vector<int>& stones)
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

    vector<vector<int> > dp(n + 1, vector<int>(n, INT_MAX)); // 这里要 n + 1 行
    vector<vector<int> > s(n, vector<int>(n, 0)); // s[i][j] = dp[i][j] 取得最优解时 k 的下标
    for(int i = 0; i < n; ++i)
    {
        dp[i][i] = 0;
        s[i][i] = i;
    }

    for(int j = 1; j < n; ++j)
        for(int i = j - 1; i >= 0; --i)
        {
            for(int k = s[i][j - 1]; k <= s[i + 1][j]; ++k)
            {
                // 这里有个 dp[k+1], 可能有 k + 1 = n，所以 dp 需要有 n + 1 行
                // 直接在 dp 上 min，需要初始化为 INT_MAX
                if(dp[i][k] + dp[k + 1][j] < dp[i][j])
                {
                    dp[i][j] = dp[i][k] + dp[k + 1][j];
                    s[i][j] = k;
                }
            }
            dp[i][j] += range_sum(sums, i, j);
        }
    cout << dp[0][n - 1] << endl;
}

// GarsiaWachs 算法
void solve_optim2(vector<int>& stones)
{
    int n = stones.size();
    if(n == 1)
    {
        cout << 0 << endl;
        return;
    }
    int ans = 0;

    for(int i = 0; i < n - 1; ++i)
    {
        int m = stones.size();

        // step1
        int k = 0;
        while(k < m - 2)
        {
            if(stones[k] <= stones[k + 2])
                break;
            ++k;
        }

        // step2
        int temp = stones[k] + stones[k + 1];
        ans += temp;

        // step3
        int l = k - 1;
        while(l >= 0)
        {
            if(stones[l] > temp)
                break;
            --l;
        }

        // step4
        stones.erase(stones.begin() + k + 1);
        stones.erase(stones.begin() + k);

        // step5
        stones.insert(stones.begin() + l + 1, temp);
    }
    cout << ans << endl;
}

int main()
{
    int N;
    cin >> N;
    vector<int> stones(N, 0);
    for(int i = 0; i < N; ++i)
        cin >> stones[i];
    solve_optim2(stones);
}
