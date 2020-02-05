// 最长公共上升子序列
// acwimng 274
// https://www.acwing.com/problem/content/274/

// 数列A和B的长度均不超过3000。

// 输入格式
// 第一行包含一个整数N，表示数列A，B的长度。
// 第二行包含N个整数，表示数列A。
// 第三行包含N个整数，表示数列B。
//
// 输出格式
// 输出一个整数，表示最长公共子序列的长度。
//
// 数据范围
// 1≤N≤3000,序列中的数字均不超过2^31−1

/*
 *
 */

#include <iostream>
#include <vector>

using namespace std;

void solve(const vector<int> &A, const vector<int> &B)
{
    // 状态定义
    // dp[i][j] := 考虑到 A[i], B[j], 且选了 A[i] B[j] 的 LCIS 长度
    // 状态转移
    // dp[i][j] = 0         (A[i] != B[j]时)
    //          = k < i, l < j 的某个 k, l 处, 且要满足 A[k] < A[i], B[l] < B[j]
    //            dp[k][l] 取到 max ，然后再加1(A[i] == B[j]时)
    int N = A.size();
    vector<vector<int> > dp(N + 1, vector<int>(N + 1, 0));
    int ans = 0;
    for(int i = 1; i < N; ++i)
        for(int j = 1; j < N; ++j)
            if(A[i] == B[j])
            {
                for(int k = 1; k < i; ++k)
                    for(int l = 1; l < j; ++l)
                        if(A[k] < A[i] && B[l] < B[j])
                            dp[i][j] = max(dp[i][j], dp[k][l]);
                dp[i][j] += 1;
                ans = max(ans, dp[i][j]);
            }
    cout << ans << endl;
    return;
}

void solve_optim_1(const vector<int> &A, const vector<int> &B)
{
    // 求 max dp[k][l] 时候，对 max 有贡献的 k,l 一定是匹配的(A[k] == B[l])
    // 所以 max 的条件中 A[k]<A[i] 和 B[l]<B[j] 只要满足了一个，另一个一定满足
    //
    // 状态定义
    // dp[i][j] := 考虑到 A[i],B[j],且选了 B[j] 的 LCIS 的长度
    // 状态转移
    // dp[i][j] = dp[i - 1]dp[j] (A[i] != B[j]时)
    //            因为定义是选了 j 因此，一定有某个 A[k] = B[j] 该信息在 dp[i - 1][j]中 -> i 这个维度是前缀信息
    //          = l < j 且 B[l] < B[j]，
    //            dp[i - 1][l] 取到的最大值再加 1. (A[i] == B[j]时)
    //
    // 可以滚动数组优化空间
    int N = A.size();
    vector<int> dp(N + 1, 0);
    for(int i = 1; i < N; ++i)
        for(int j = 1; j < N; ++j)
        {
            if(A[i] == B[j])
            {
                int mv = 0;
                for(int l = 1; l < j; ++l)
                    if(B[l] < B[j])
                        mv = max(mv, dp[l]);
                dp[j] = mv + 1;
            }
        }

    int ans = 0;
    for(int i = 1; i < N; ++i)
        ans = max(ans, dp[i]);
    cout << ans << endl;
    return;
}

void solve_optim_2(const vector<int> &A, const vector<int> &B)
{
    // optim_1 的基础上对代码做等价变形
    int N = A.size();
    vector<int> dp(N + 1, 0);
    for(int i = 1; i < N; ++i)
    {
        int mv = 0;
        for(int j = 1; j < N; ++j)
        {
            if(B[j] < A[i])
                mv = max(mv, dp[j]);
            if(A[i] == B[j])
                dp[j] = mv + 1;
        }
    }

    int ans = 0;
    for(int i = 1; i < N; ++i)
        ans = max(ans, dp[i]);
    cout << ans << endl;
    return;
}


int main()
{
    int N;
    cin >> N;
    vector<int> A(N + 1, 0);
    vector<int> B(N + 1, 0);
    for(int i = 1; i <= N; ++i)
        cin >> A[i];
    for(int i = 1; i <= N; ++i)
        cin >> B[i];
    solve_optim_1(A, B);
    return 0;
}
