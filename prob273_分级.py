
def main():
    # with open("test.txt", "r") as f:
    #     lines = f.readlines()
    #     N = int(lines[0])
    #     A = [0] * N
    #     for i in range(N):
    #         A[i] = int(lines[i + 1])

    N = int(input())
    A = [0] * N
    for i in range(N):
        A[i] = int(input())

    # 离散化
    a = sorted(set(A))
    m = len(a)

    def solve(A):
        # 构造非严格单调递增的 B
        dp = [[0 for _ in range(m)] for _ in range(N)]
        for k in range(m):
            dp[0][k] = abs(A[0] - a[k])

        for i in range(1, N):
            mx = dp[i - 1][0]
            dp[i][0] = abs(A[i] - a[0]) + mx
            for k in range(1, m):
                mx = min(mx, dp[i - 1][k])
                dp[i][k] = abs(A[i] - a[k]) + mx

        return min(dp[N - 1])

    ans1 = solve(A)
    ans2 = solve(list(reversed(A)))

    print(min(ans1, ans2))


if __name__ == "__main__":
    main()
