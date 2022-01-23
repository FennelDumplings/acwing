#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    int L, R;
    while(cin >> L >> R)
    {
        if(L == 1)
            L = 2;
        int m = sqrt(R);
        vector<bool> vec(m + 1, true);
        vec[0] = false;
        vec[1] = false;
        int n = R - L + 1;
        vector<bool> f(n, true);
        // f[i] := i + L 是否是质数
        int cnt = 0;
        vector<int> primes;
        for(int i = 2; i <= m; ++i)
        {
            if(vec[i])
            {
                // i 是质数
                int p = i;
                for(int j = max((int)ceil(L / (double)p), 2); j <= (int)floor(R / (double)p); ++j)
                    f[j * p - L] = false;
            }
            for(int j = 0; j < cnt && i * primes[j] < m; ++j)
            {
                vec[i * primes[j]] = false;
                if(i % primes[j] == 0)
                    break;
            }
        }
        int l = -1;
        int r = -1;
        int min_d, C1, C2;
        int max_d, D1, D2;
        min_d = C1 = C2 = D1 = D2 = n + 1;
        max_d = -1;
        for(int i = 0; i < n; ++i)
        {
            if(f[i])
            {
                if(l == -1)
                    l = i;
                else
                {
                    r = i;
                    if(min_d > r - l)
                    {
                        min_d = r - l;
                        C1 = l;
                        C2 = r;
                    }
                    if(max_d < r - l)
                    {
                        max_d = r - l;
                        D1 = l;
                        D2 = r;
                    }
                    l = r;
                }
            }
        }
        if(r == -1)
            cout << "There are no adjacent primes." << endl;
        else
            cout << C1 + L << "," << C2 + L << " are closest, " << D1 + L << "," << D2 + L << " are most distant." << endl;
    }
}
