import functools

def main():
    @functools.lru_cache(int(1e7))
    def solve(i: int, j: int, l: int, r: int, x: int, y: int) -> int:
        # N * K * M * M * 2 * 2
        w = r - l + 1
        s = sums[i][r + 1] - sums[i][l]

        if j < w:
            return -1
        if j == w:
            return s
        if i == 0 and j > w:
            return -1

        # i > 0, j > w
        ans = -1

        if (x, y) == (1, 0):
            x_, y_ = 1, 0
            for p in range(l, r + 1):
                for q in range(p, r + 1):
                    # M * M
                    res = solve(i - 1, j - w, p, q, x_, y_)
                    if res != -1 and s + res > ans:
                        ans = s + res

        if (x, y) == (0, 0):
            y_ = 0
            for x_ in range(2):
                for p in range(0, l + 1):
                    for q in range(l, r + 1):
                        res = solve(i - 1, j - w, p, q, x_, y_)
                        if res != -1 and s + res > ans:
                            ans = s + res

        if (x, y) == (1, 1):
            x_ = 1
            for y_ in range(2):
                for p in range(l, r + 1):
                    for q in range(r, M):
                        res = solve(i - 1, j - w, p, q, x_, y_)
                        if res != -1 and s + res > ans:
                            ans = s + res

        if (x, y) == (0, 1):
            for x_ in range(2):
                for y_ in range(2):
                    for p in range(0, l + 1):
                        for q in range(r, M):
                            res = solve(i - 1, j - w, p, q, x_, y_)
                            if res != -1 and s + res > ans:
                                ans = s + res

        return ans

    def get_best_decisions(i: int, j: int, l: int, r: int, x: int, y: int, ans: int) -> None:
        ans_best_decisions.append((i, j, l, r, x, y))

        w = r - l + 1
        s = sums[i][r + 1] - sums[i][l]

        if j == w:
            return

        # i > 0, j > w
        if (x, y) == (1, 0):
            x_, y_ = 1, 0
            for p in range(l, r + 1):
                for q in range(p, r + 1):
                    # M * M
                    res = solve(i - 1, j - w, p, q, x_, y_)
                    if res == ans - s:
                        get_best_decisions(i - 1, j - w, p, q, x_, y_, ans - s)
                        return

        if (x, y) == (0, 0):
            y_ = 0
            for x_ in range(2):
                for p in range(0, l + 1):
                    for q in range(l, r + 1):
                        res = solve(i - 1, j - w, p, q, x_, y_)
                        if res == ans - s:
                            get_best_decisions(i - 1, j - w, p, q, x_, y_, ans - s)
                            return

        if (x, y) == (1, 1):
            x_ = 1
            for y_ in range(2):
                for p in range(l, r + 1):
                    for q in range(r, M):
                        res = solve(i - 1, j - w, p, q, x_, y_)
                        if res == ans - s:
                            get_best_decisions(i - 1, j - w, p, q, x_, y_, ans - s)
                            return

        if (x, y) == (0, 1):
            for x_ in range(2):
                for y_ in range(2):
                    for p in range(0, l + 1):
                        for q in range(r, M):
                            res = solve(i - 1, j - w, p, q, x_, y_)
                            if res == ans - s:
                                get_best_decisions(i - 1, j - w, p, q, x_, y_, ans - s)
                                return

    N, M, K = list(map(int, input().split()))
    A = [[] for _ in range(N)]
    for i in range(N):
        A[i] = list(map(int, input().split()))


    sums = [[0 for _ in range(M + 1)] for _ in range(N)]
    for i in range(N):
        for j in range(1, M + 1):
            sums[i][j] = sums[i][j - 1] + A[i][j - 1]

    ans = -1
    start = []
    for i in range(N):
        for l in range(M):
            for r in range(l, M):
                for (x, y) in [(0, 0), (0, 1), (1, 0), (1, 1)]:
                    res = solve(i, K, l, r, x, y)
                    if res != -1 and res > ans:
                        ans = res
                        start = [i, K, l, r, x, y]

    if ans == -1:
        print("Oil : {}".format(0))
        return

    print("Oil : {}".format(ans))

    ans_best_decisions = []
    get_best_decisions(*start, ans)
    ans_best_decisions.reverse()
    for decision in ans_best_decisions:
        i = decision[0]
        l = decision[2]
        r = decision[3]
        for j in range(l, r + 1):
            print("{} {}".format(i + 1, j + 1))


if __name__ == "__main__":
    main()
