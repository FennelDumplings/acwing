#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

vector<int> a;
vector<double> p;
int N;
vector<vector<vector<double>>> dp;

double solve(int i, int j, int k)
{
    int k_tmp = min(k, N);
    if(dp[i][j + N][k_tmp + N] >= -0.5)
        return dp[i][j + N][k_tmp + N];
    if(i == N + 1)
    {
        if(j <= 0 && k >= 0)
            return dp[i][j + N][k_tmp + N] = 1.0;
        else
            return dp[i][j + N][k_tmp + N] = 0.0;
    }
    return dp[i][j + N][k_tmp + N] = p[i] * solve(i + 1, j - 1, k + a[i])
            + (1 - p[i]) * solve(i + 1, j, k);
}

int main()
{
    int L, K;
    cin >> N >> L >> K;
    dp.assign(N + 2, vector<vector<double>>(N * 2 + 1, vector<double>(N * 2 + 1, -1.0)));
    a.assign(N + 1, 0);
    p.assign(N + 1, 0.0);
    for(int i = 0; i < N; ++i)
    {
        double tmp;
        cin >> tmp;
        p[i + 1] = tmp / 100.0;
    }
    for(int i = 0; i < N; ++i)
    {
        int tmp;
        cin >> tmp;
        a[i + 1] = tmp;
    }
    double ans = solve(1, L, K);
    cout << std::fixed << std::setprecision(6);
    cout << ans << endl;
}
