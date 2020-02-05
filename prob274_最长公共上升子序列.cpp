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
    //            dp[k][l] 取到 max (A[i] == B[j]时)
    int N = A.size();
    vector<vector<int> > dp(N, vector<int>(N, 0));
    for(int i = 0; i < N; ++i)
        for(int j = 0; j < N; ++j)
            if(A[i] == B[j])
                for(int k = 0; k < i; ++k)
                    for(int l = 0; l < j; ++l)
                        if(A[k] < A[i] && B[l] < B[j])
                            dp[i][j] = max(dp[i][j], dp[k][l]);
    cout << dp[N - 1][N - 1];
    return;
}

int main()
{
    int N;
    cin >> N;
    vector<int> A(N, 0);
    vector<int> B(N, 0);
    for(int i = 0; i < N; ++i)
        cin >> A[i];
    for(int i = 0; i < N; ++i)
        cin >> B[i];
    solve(A, B);
    return 0;
}
