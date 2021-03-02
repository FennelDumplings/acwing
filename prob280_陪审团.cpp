#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 210, M = 810, offset = 400;
int dp[N][21][M];
int d[N], p[N];

int main()
{
    int C = 1;
    int n, m;
    while(cin >> n >> m && !(n == 0 && m == 0))
    {
        for(int i = 1; i <= n; ++i)
            cin >> p[i] >> d[i];

        // dp 初始化
        memset(dp, -0x3f, sizeof(dp));
        dp[0][0][offset] = 0;

        // 求 dp
        for(int i = 1; i <= n; ++i)
        {
            for(int j = 0; j <= m; ++j)
            {
                for(int k = 0; k < M; ++k)
                {
                    dp[i][j][k] = dp[i - 1][j][k]; // 不选 i
                    if(j == 0) continue;
                    int prev_diff = k - p[i] + d[i];
                    if(prev_diff < 0 || prev_diff > 800)
                        continue;
                    // i 可以选
                    if(dp[i - 1][j - 1][prev_diff] < 0)
                        continue;
                    dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - 1][prev_diff] + p[i] + d[i]);
                }
            }
        }

        // 后处理1 求 diff 以及最后一个阶段的决策
        int diff = 0;
        while(diff <= offset && dp[n][m][offset + diff] < 0 && dp[n][m][offset - diff] < 0)
            ++diff;
        if(dp[n][m][offset - diff] > dp[n][m][offset + diff])
            diff = offset - diff;
        else
            diff = offset + diff;

        // 倒推前面各个阶段的决策
        int i = n, j = m;
        vector<int> cand(m + 1);
        while(j > 0)
        {
            if(dp[i][j][diff] == dp[i - 1][j][diff])
                --i;
            else
            {
                cand[j] = i;
                diff -= (p[i] - d[i]);
                --i;
                --j;
            }
        }

        int tp = 0, td = 0;
        for(int i = 1; i <= m; ++i)
        {
            tp += p[cand[i]];
            td += d[cand[i]];
        }

        // 输出
        cout << "Jury #" << C++ << endl;
        cout << "Best jury has value " << tp << " for prosecution and value " << td << " for defence:" << endl;
        for(int i = 1; i <= m; ++i)
            cout << cand[i] << " ";
        cout << endl;
        cout << endl;
    }
}
