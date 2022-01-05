#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

double dp[16][16][16][16][5][5];
int A, B, C, D;

double solve(int a, int b, int c, int d, int x, int y)
{
    if(dp[a][b][c][d][x][y] >= 0.0)
        return dp[a][b][c][d][x][y];
    bool reached = true;
    reached = reached && (a + (x == 0) + (y == 0)) >= A;
    reached = reached && (b + (x == 1) + (y == 1)) >= B;
    reached = reached && (c + (x == 2) + (y == 2)) >= C;
    reached = reached && (d + (x == 3) + (y == 3)) >= D;
    if(reached)
        return dp[a][b][c][d][x][y] = 0.0;
    int diff = max(A - 13 - (x == 0) - (y == 0), 0);
    diff += max(B - 13 - (x == 1) - (y == 1), 0);
    diff += max(C - 13 - (x == 2) - (y == 2), 0);
    diff += max(D - 13 - (x == 3) - (y == 3), 0);
    if(diff > (x == 4) + (y == 4))
        return dp[a][b][c][d][x][y] = 1e9;
    double ans = 1.0;
    double S = 54 - (a + b + c + d + (x != 4) + (y != 4));
    if(13 - a > 0)
        ans += (13 - a) / S * solve(a + 1, b, c, d, x, y);
    if(13 - b > 0)
        ans += (13 - b) / S * solve(a, b + 1, c, d, x, y);
    if(13 - c > 0)
        ans += (13 - c) / S * solve(a, b, c + 1, d, x, y);
    if(13 - d > 0)
        ans += (13 - d) / S * solve(a, b, c, d + 1, x, y);
    if(x == 4)
    {
        double tmp = 1e9;
        tmp = min(tmp, solve(a, b, c, d, 0, y));
        tmp = min(tmp, solve(a, b, c, d, 1, y));
        tmp = min(tmp, solve(a, b, c, d, 2, y));
        tmp = min(tmp, solve(a, b, c, d, 3, y));
        ans += 1 / S * tmp;
    }
    if(y == 4)
    {
        double tmp = 1e9;
        tmp = min(tmp, solve(a, b, c, d, x, 0));
        tmp = min(tmp, solve(a, b, c, d, x, 1));
        tmp = min(tmp, solve(a, b, c, d, x, 2));
        tmp = min(tmp, solve(a, b, c, d, x, 3));
        ans += 1 / S * tmp;
    }
    return dp[a][b][c][d][x][y] = ans;
}

int main()
{
    memset(dp, -1, sizeof(dp));
    cin >> A >> B >> C >> D;
    double ans = solve(0, 0, 0, 0, 4, 4);
    cout << std::fixed << std::setprecision(3);
    if(ans > 55)
        cout << -1.0 << endl;
    else
        cout << ans << endl;
}
