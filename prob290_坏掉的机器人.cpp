#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const double EPS = 1e-8;

void gaussian_elimination(vector<vector<double>>& A)
{
    int M = A.size() - 1;

    for(int i = 1; i < M; ++i)
    {
        // 用第 i 行消第 i + 1 行
        double rate = A[i + 1][i] / A[i][i];
        for(int k = i; k <= (i + 1); ++k)
            A[i + 1][k] -= rate * A[i][k];
        A[i + 1][M + 1] -= rate * A[i][M + 1];
    }
    for(int i = M; i >= 2; --i)
    {
        // 用第 i 行消第 i - 1 行
        double rate = A[i - 1][i] / A[i][i];
        A[i - 1][i] -= rate * A[i][i];
        A[i - 1][M + 1] -= rate * A[i][M + 1];
    }
}

int main()
{
    int N, M;
    cin >> N >> M;
    int x, y;
    cin >> x >> y;
    vector<vector<double>> dp(N + 1, vector<double>(M + 1, 0.0));
    cout << std::fixed << std::setprecision(4);
    if(M == 1)
    {
        // 特判
        for(int i = N - 1; i >= x; --i)
            dp[i][1] = dp[i + 1][1] + 2.0;
        cout << dp[x][1] << endl;
        return 0;
    }
    // M >= 2
    vector<vector<double>> A(M + 1, vector<double>(M + 2)); // 增广矩阵
    for(int i = N - 1; i >= x; --i)
    {
        // dp[i][1], dp[i][2], ..., dp[i][M] 共 M 个未知数
        // 系数矩阵为 M * M

        // 增广矩阵 A 的第一行
        A[1][1] = 2;
        A[1][2] = -1;
        A[1][M + 1] = 3 + dp[i + 1][1];
        // 增广矩阵 A 的第 M 行
        A[M][M] = 2;
        A[M][M - 1] = -1;
        A[M][M + 1] = 3 + dp[i + 1][M];
        // 增广矩阵 A 的第 2~M-1 行
        for(int l = 2; l <= M - 1; ++l)
        {
            A[l][l] = 3;
            A[l][l + 1] = -1;
            A[l][l - 1] = -1;
            A[l][M + 1] = 4 + dp[i + 1][l];
        }

        gaussian_elimination(A);

        for(int j = 1; j <= M; ++j)
            dp[i][j] = A[j][M + 1] / A[j][j];
    }

    cout << dp[x][y] << endl;
}
