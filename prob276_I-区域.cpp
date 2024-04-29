#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 15;
const int MAXM = 15;
const int MAXK = MAXN * MAXM;
int dp[MAXN][MAXK][MAXM][MAXM][2][2];
int A[MAXN][MAXM];
int sums[MAXN][MAXM + 1];
int N, M, K;

int solve(int i, int j, int l, int r, int x, int y)
{
    if(dp[i][j][l][r][x][y] != INF)
        return dp[i][j][l][r][x][y];

    int w = r - l + 1;
    int s = sums[i][r + 1] - sums[i][l];

    if(j < w)
        return -1;
    if(j == w)
         return s;
    if(i == 0 && j > w)
        return -1;

    // i > 0, j > w
    int ans = -1;
    if(x == 1 && y == 0)
    {
        int x_ = 1;
        int y_ = 0;
        for(int p = l; p <= r; ++p)
            for(int q = p; q <= r; ++q)
            {
                int res = solve(i - 1, j - w, p, q, x_, y_);
                if(res != -1 && s + res > ans)
                    ans = s + res;
            }
    }
    if(x == 0 && y == 0)
    {
        int y_ = 0;
        for(int x_ = 0; x_ <= 1; ++x_)
            for(int p = 0; p <= l; ++p)
                for(int q = l; q <= r; ++q)
                {
                    int res = solve(i - 1, j - w, p, q, x_, y_);
                    if(res != -1 && s + res > ans)
                        ans = s + res;
                }
    }
    if(x == 1 && y == 1)
    {
        int x_ = 1;
        for(int y_ = 0; y_ <= 1; ++y_)
            for(int p = l; p <= r; ++p)
                for(int q = r; q < M; ++q)
                {
                    int res = solve(i - 1, j - w, p, q, x_, y_);
                    if(res != -1 && s + res > ans)
                        ans = s + res;
                }
    }
    if(x == 0 && y == 1)
    {
        for(int x_ = 0; x_ <= 1; ++x_)
            for(int y_ = 0; y_ <= 1; ++y_)
                for(int p = 0; p <= l; ++p)
                    for(int q = r; q < M; ++q)
                    {
                        int res = solve(i - 1, j - w, p, q, x_, y_);
                        if(res != -1 && s + res > ans)
                            ans = s + res;
                    }
    }
    return dp[i][j][l][r][x][y] = ans;
}

void get_best_decisions(int i, int j, int l, int r, int x, int y, vector<vector<int>>& ans_best_decisions, int ans)
{
    ans_best_decisions.push_back({i, j, l, r, x, y});

    int w = r - l + 1;
    int s = sums[i][r + 1] - sums[i][l];

    if(j == w)
        return;

    // i > 0, j > w
    if(x == 1 && y == 0)
    {
        int x_ = 1;
        int y_ = 0;
        for(int p = l; p <= r; ++p)
            for(int q = p; q <= r; ++q)
            {
                int res = solve(i - 1, j - w, p, q, x_, y_);
                if(res == ans - s)
                {
                    get_best_decisions(i - 1, j - w, p, q, x_, y_, ans_best_decisions, ans - s);
                    return;
                }
            }
    }
    if(x == 0 && y == 0)
    {
        int y_ = 0;
        for(int x_ = 0; x_ <= 1; ++x_)
            for(int p = 0; p <= l; ++p)
                for(int q = l; q <= r; ++q)
                {
                    int res = solve(i - 1, j - w, p, q, x_, y_);
                    if(res == ans - s)
                    {
                        get_best_decisions(i - 1, j - w, p, q, x_, y_, ans_best_decisions, ans - s);
                        return;
                    }
                }
    }
    if(x == 1 && y == 1)
    {
        int x_ = 1;
        for(int y_ = 0; y_ <= 1; ++y_)
            for(int p = l; p <= r; ++p)
                for(int q = r; q < M; ++q)
                {
                    int res = solve(i - 1, j - w, p, q, x_, y_);
                    if(res == ans - s)
                    {
                        get_best_decisions(i - 1, j - w, p, q, x_, y_, ans_best_decisions, ans - s);
                        return;
                    }
                }
    }
    if(x == 0 && y == 1)
    {
        for(int x_ = 0; x_ <= 1; ++x_)
            for(int y_ = 0; y_ <= 1; ++y_)
                for(int p = 0; p <= l; ++p)
                    for(int q = r; q < M; ++q)
                    {
                        int res = solve(i - 1, j - w, p, q, x_, y_);
                        if(res == ans - s)
                        {
                            get_best_decisions(i - 1, j - w, p, q, x_, y_, ans_best_decisions, ans - s);
                            return;
                        }
                    }
    }
}

int main()
{
    memset(dp, INF, sizeof(dp));
    memset(A, -1, sizeof(A));
    memset(sums, -1, sizeof(sums));

    cin >> N >> M >> K;
    for(int i = 0; i < N; ++i)
        for(int j = 0; j < M; ++j)
            cin >> A[i][j];

    for(int i = 0; i < N; ++i)
        for(int j = 1; j <= M; ++j)
            sums[i][j] = sums[i][j - 1] + A[i][j - 1];

    int ans = -1;
    vector<int> start;
    for(int i = 0; i < N; ++i)
        for(int l = 0; l < M; ++l)
            for(int r = l; r < M; ++r)
                for(int x = 0; x <= 1; ++x)
                    for(int y = 0; y <= 1; ++y)
                    {
                        int res = solve(i, K, l, r, x, y);
                        if(res != -1 && res > ans)
                        {
                            ans = res;
                            start = {i, K, l, r, x, y};
                        }
                    }

    if(ans == -1)
        cout << "Oil : " << 0 << endl;
    else
    {
        cout << "Oil : " << ans << endl;

        vector<vector<int>> ans_best_decisions;
        get_best_decisions(start[0], start[1], start[2], start[3], start[4], start[5], ans_best_decisions, ans);
        reverse(ans_best_decisions.begin(), ans_best_decisions.end());
        for(vector<int>& decison: ans_best_decisions)
        {
            int i = decison[0];
            int l = decison[2];
            int r = decison[3];
            for(int j = l; j <= r; j++)
                cout << i + 1 << " " << j + 1 << endl;
        }
    }
}
