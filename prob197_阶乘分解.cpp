
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

vector<int> get_primes(int n) {
    if(n < 2) return {};
    vector<bool> vec(n, true);
    vec[0] = false;
    vec[1] = false;
    int cnt = 0;
    vector<int> primes;
    for(int i = 2; i < n; ++i)
    {
        if(vec[i])
        {
            ++cnt;
            primes.push_back(i);
        }
        for(int j = 0; j < cnt && i * primes[j] < n; ++j)
        {
            vec[i * primes[j]] = false;
            if(i % primes[j] == 0)
                break;
        }
    }
    return primes;
}

vector<int> factorial_get_prime_factor(int N, const vector<int>& primes)
{
    int m = primes.size();
    vector<int> c(m, 0);
    for(int i = 0; i < m; ++i)
    {
        int p = primes[i];
        int cnt = 0;
        for(int j = 1; pow(p, j) <= N; ++j)
            cnt += N / pow(p, j);
        c[i] = cnt;
    }
    return c;
}

int main()
{
    int N;
    cin >> N;
    vector<int> p = get_primes(N + 1);
    vector<int> c = factorial_get_prime_factor(N, p);
    int m = p.size();
    for(int i = 0; i < m; ++i)
    {
        cout << p[i] << " " << c[i] << endl;
    }
}
