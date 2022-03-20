#include <vector>
#include <iostream>

using namespace std;

const int n = 5001;
int sums[n + 1][n + 1];

int main()
{
    int N, R;
    cin >> N >> R;
    for(int i = 0; i < N; ++i)
    {
        int x, y, w;
        cin >> x >> y >> w;
        sums[x + 1][y + 1] += w;
    }
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            sums[i + 1][j + 1] += sums[i][j + 1] + sums[i + 1][j] - sums[i][j];
    int ans = 0;
    R = min(R, n);
    for(int x1 = 0; x1 + R <= n; ++x1)
    {
        for(int y1 = 0; y1 + R <= n; ++y1)
        {
            int x2 = x1 + R;
            int y2 = y1 + R;
            ans = max(ans, sums[x2][y2] - sums[x2][y1] - sums[x1][y2] + sums[x1][y1]);
        }
    }
    cout << ans << endl;
}
