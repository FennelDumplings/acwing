import functools

class Solution:
    def __init__(self, A, B, C, D):
        self.A = A
        self.B = B
        self.C = C
        self.D = D

    @functools.lru_cache(maxsize=int(2e6))
    def solve(self, a, b, c, d, x, y):
        reached = True
        reached = reached and (a + (x == 0) + (y == 0) >= self.A)
        reached = reached and (b + (x == 1) + (y == 1) >= self.B)
        reached = reached and (c + (x == 2) + (y == 2) >= self.C)
        reached = reached and (d + (x == 3) + (y == 3) >= self.D)
        if reached:
            return 0.0
        diff = max(self.A - 13 - (x == 0) - (y == 0), 0)
        diff += max(self.B - 13 - (x == 1) - (y == 1), 0)
        diff += max(self.C - 13 - (x == 2) - (y == 2), 0)
        diff += max(self.D - 13 - (x == 3) - (y == 3), 0)
        if diff > (x == 4) + (y == 4):
            return 1e9
        S = 54 - (a + b + c + d + (x != 4) + (y != 4))
        ans = 1.0
        if 13 - a > 0:
            ans += (13 - a) / S * self.solve(a + 1, b, c, d, x, y)
        if 13 - b > 0:
            ans += (13 - b) / S * self.solve(a, b + 1, c, d, x, y)
        if 13 - c > 0:
            ans += (13 - c) / S * self.solve(a, b, c + 1, d, x, y)
        if 13 - d > 0:
            ans += (13 - d) / S * self.solve(a, b, c, d + 1, x, y)
        if x == 4:
            ans += 1 / S * min(self.solve(a, b, c, d, 0, y)
                              ,self.solve(a, b, c, d, 1, y)
                              ,self.solve(a, b, c, d, 2, y)
                              ,self.solve(a, b, c, d, 3, y)
                              )
        if y == 4:
            ans += 1 / S * min(self.solve(a, b, c, d, x, 0)
                              ,self.solve(a, b, c, d, x, 1)
                              ,self.solve(a, b, c, d, x, 2)
                              ,self.solve(a, b, c, d, x, 3)
                              )
        return ans

if __name__ == "__main__":
    tmp = input()
    A, B, C, D = tmp.split(" ")
    A = int(A)
    B = int(B)
    C = int(C)
    D = int(D)
    s = Solution(A, B, C, D)
    ans = s.solve(0, 0, 0, 0, 4, 4)
    if ans > 55:
        print("{:.3f}".format(-1.0))
    else:
        print("{:.3f}".format(round(ans, 3)))
