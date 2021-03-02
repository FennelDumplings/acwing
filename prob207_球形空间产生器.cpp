
#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPS = 1e-8;

int main()
{
    int n;
    cin >> n;
    vector<vector<double>> a(n + 2, vector<double>(n + 1, 0.0));
    for(int i = 1; i <= n + 1; ++i)
        for(int j = 1; j <= n; ++j)
            cin >> a[i][j];

    vector<vector<double>> c(n + 1, vector<double>(n + 1, 0.0)); // 系数矩阵
    vector<double> b(n + 1, 0.0); // 常数列
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
        {
            c[i][j] = 2 * (a[i][j] - a[i+1][j]);
            b[i] += a[i][j] * a[i][j] - a[i + 1][j] * a[i + 1][j];
        }

    // 高斯消元, 保证有唯一解
    for(int i = 1; i <= n; ++i)
    {
        // 找到 x[i] 的系数不为零的一个方程
        for(int j = i; j <= n ;++j)
        {
            if(fabs(c[j][i]) > EPS)
            {
                for(int k = 1; k <= n; ++k)
                    swap(c[i][k], c[j][k]);
                swap(b[i], b[j]);
            }
        }
        // 消去其它方程的 x[i] 的系数
        for(int j = 1; j <= n; ++j)
        {
            if(i == j) continue;
            double rate = c[j][i] / c[i][i];
            for(int k = i; k <= n; ++k)
                c[j][k] -= c[i][k] * rate;
            b[j] -= b[i] * rate;
        }
    }

    cout << std::fixed << std::setprecision(3);
    for(int i = 1; i <= n; ++i)
        cout << b[i] / c[i][i] << " ";
    cout << endl;
}
