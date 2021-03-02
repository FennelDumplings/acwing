#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double EPS = 1e-8;

// const int N = 520;
// long double z[N][N];
// int cost[N];

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<long double>> z(n + 1, vector<long double>(m + 1));
    // z[i][j] := 第 i 件装备的第 j 个属性
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= m; ++j)
        {
            double x;
            scanf("%lf",&x);
            z[i][j] = x;
        }
    }
    vector<int> cost(n + 1);
    for(int i = 1; i <= n; ++i)
    {
        int x;
        scanf("%d", &x);
        cost[i] = x;
    }

    int dim = 0;
    int ans = 0;
    for(int i = 1; i <= m; ++i)
    {
        // 考虑元 x[i]
        int choose_j = -1;
        for(int j = dim + 1; j <= n; ++j)
        {
            if(fabs(z[j][i]) > EPS)
            {
                if((choose_j == -1 || cost[j] < cost[choose_j]))
                    choose_j = j;
            }
        }

        if(choose_j == -1)
            continue; // x[i] 为自由元

        ++dim; // x[i] 为主元
        ans += cost[choose_j];

        for(int k = 1; k <= m; ++k)
            swap(z[choose_j][k], z[dim][k]);
        swap(cost[choose_j],cost[dim]);

        // 消元 x[dim]
        for(int j = 1; j <= n; ++j)
        {
            if(j == dim) continue;
            if(fabs(z[j][i]) > EPS)
            {
                long double rate = z[j][i] / z[dim][i];
                for(int k = i; k <= m; ++k)
                    z[j][k] -= rate * z[dim][k];
            }
        }
    }

    cout << dim << " " << ans << endl;
}

