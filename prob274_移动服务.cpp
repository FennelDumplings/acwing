#include <iostream>
#include <vector>
#include <climits>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXL = 201;
const int MAXN = 1001;
int dp[MAXN][MAXL][MAXL];
int c[MAXL][MAXL];
int p[MAXN];
int N, L;

void iterative(int i)
{
    // 当前阶段为 i
    if(i == N)
        return;

    for(int x = 1; x <= L; ++x)
        for(int y = 1; y <= L; ++y)
        {
            // 当前的附加信息为 p[i], x, y
            // x != y != p[i]
            if(x == y || x == p[i] || p[i] == y)
                continue;
            // 基于当前阶段的各个状态 dp[i][x][y]，更新后续阶段的状态
            dp[i + 1][x][y] = min(dp[i + 1][x][y], dp[i][x][y] + c[p[i]][p[i + 1]]);
            dp[i + 1][p[i]][y] = min(dp[i + 1][p[i]][y], dp[i][x][y] + c[x][p[i + 1]]);
            dp[i + 1][x][p[i]] = min(dp[i + 1][x][p[i]], dp[i][x][y] + c[y][p[i + 1]]);
        }

    // 进入下一阶段
    traverse(i + 1);
}

int main()
{
    cin >> L >> N;
    for(int i = 1; i <= L; ++i)
        for(int j = 1; j <= L; ++j)
            cin >> c[i][j];
    for(int i = 1; i <= N; ++i)
        cin >> p[i];

    memset(dp, INF, sizeof(dp));

    dp[0][1][2] = 0;
    p[0] = 3;
    iterative(0);

    int ans = INT_MAX;
    for(int x = 1; x <= L; ++x)
    {
        for(int y = 1; y <= L; ++y)
        {
            if(x == y || y == p[N] || p[N] == x)
                continue;
            ans = min(ans, dp[N][x][y]);
        }
    }
    cout << ans << endl;
}
