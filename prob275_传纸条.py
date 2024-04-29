import functools

def main():
    # with open("test.txt", "r") as f:
    #     lines = f.readlines()
    #     m, n = map(int, lines[0].split())
    #     grid = [[] for _ in range(m)]
    #     for i in range(m):
    #         grid[i] = list(map(int, lines[i + 1].split()))

    m, n = map(int, input().split())
    grid = [[] for _ in range(m)]
    for i in range(m):
        grid[i] = list(map(int, input().split()))

    # dp[i][x1][x2] := 第i步时，两个人分别走到了 (x1, i-x1), (x2, i-x2) 位置，过程中的最大好感
    # 过程中始终要求 x1 < x2 或者 x1=x2 且 y2 < y1
    # dp[i][x1][x2] = grid[x1][i-x1] + grid[x2][i-x2] + max(dp[i - 1][x1][x2]
    #                                                      ,dp[i - 1][x1-1][x2]
    #                                                      ,dp[i - 1][x1][x2-1]
    #                                                      ,dp[i - 1][x1-1][x2-1]
    #                                                      )

    dp = [[[0 for _ in range(n)] for _ in range(m)] for _ in range(n + m - 1)]

    def check(x1, y1, x2, y2):
        # 判定可行决策
        if x1 < 0 or y1 < 0:
            return False
        if x2 < 0 or y2 < 0:
            return False
        return x1 < x2

    @functools.lru_cache(int(1e7))
    def solve(i, x1, x2):
        # print(i, x1, x2)
        # 已经保证 x1 < x2
        y1 = i - x1
        y2 = i - x2
        if i == 1:
            # 初始化
            return grid[x1][y1] + grid[x2][y2]

        mx = -1
        if check(x1 - 1, y1, x2 - 1, y2):
            mx = max(mx, solve(i - 1, x1 - 1, x2 - 1))
        if check(x1 - 1, y1, x2, y2 - 1):
            mx = max(mx, solve(i - 1, x1 - 1, x2))
        if check(x1, y1 - 1, x2 - 1, y2):
            mx = max(mx, solve(i - 1, x1, x2 - 1))
        if check(x1, y1 - 1, x2, y2 - 1):
            mx = max(mx, solve(i - 1, x1, x2))

        return -1 if mx == -1 else mx + grid[x1][i - x1] + grid[x2][i - x2]


    ans = solve(n + m - 3, m - 2, m - 1)
    print(ans)


if __name__ == "__main__":
    main()
