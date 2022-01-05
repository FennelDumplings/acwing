import functools

class Solution:
    def __init__(self, N, p, a):
        self.N = N
        self.p = p
        self.a = a

    @functools.lru_cache(maxsize=int(1e7))
    def solve(self, i, j, k):
        if i == self.N + 1:
            if j <= 0 and k >= 0:
                return 1.0
            else:
                return 0.0
        return self.p[i] * self.solve(i + 1, j - 1, k + self.a[i]) \
                    + (1 - self.p[i]) * self.solve(i + 1, j, k)

if __name__ == "__main__":
    tmp = input()
    N, L, K = [int(i) for i in tmp.split(" ")]
    tmp = input()
    tmp = tmp.split(" ")
    p = [0.0] * (N + 1)
    for i in range(N):
        p[i + 1] = float(tmp[i]) / 100
    tmp = input()
    tmp = tmp.split(" ")
    a = [0] * (N + 1)
    for i in range(N):
        a[i + 1] = int(tmp[i])
    s = Solution(N, p, a)
    ans = s.solve(1, L, K)
    ans = round(ans, 6)
    print("{:.6f}".format(ans))
