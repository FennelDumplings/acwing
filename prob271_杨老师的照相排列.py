import functools

def main():
    @functools.lru_cache()
    def solve(a):
        if list(a) == [0] * len(a):
            return 1

        ans = 0
        for i in range(k):
            if a[i] > 0 and a[i] <= N[i] and (i == k - 1 or a[i] > a[i + 1]):
                nxt_a = list(a)
                nxt_a[i] -= 1
                ans += solve(tuple(nxt_a))
        return ans

    while True:
        k_str = input()
        if k_str == "0":
            break
        k = int(k_str)
        N_str = input()
        N_str = N_str.split()
        N = [int(s) for s in N_str]

        ans = solve(tuple(N))
        print(ans)


if __name__ == "__main__":
    main()
