#include <vector>
#include <iostream>

using namespace std;

int main()
{
    int N = 12;
    vector<int> d(N + 1);
    d[1] = 1;
    for(int i = 2; i <= N; ++i)
        d[i] = 2 * d[i - 1] + 1;
    vector<int> f(13, 1e9);
    f[1] = 1;
    for(int n = 2; n <= N; ++n)
    {
        for(int i = 1; i < n; ++i)
            f[n] = min(f[n], 2 * f[i] + d[n - i]);
    }
    for(int i = 1; i <= N; ++i)
        cout << f[i] << endl;
}
