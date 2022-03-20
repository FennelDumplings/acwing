#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

using ll = long long;

const int N = 1e5 + 5;
ll B[N];

int main()
{
    int n;
    cin >> n;
    ll prev = 0;
    for(int i = 0; i < n; ++i)
    {
        ll cur;
        cin >> cur;
        B[i] = cur - prev;
        prev = cur;
    }
    ll n1 = 0; // 正值之和
    ll n2 = 0; // 负值的相反数之和
    for(int i = 1; i < n; ++i)
    {
        if(B[i] > 0)
            n1 += B[i];
        if(B[i] < 0)
            n2 -= B[i];
    }
    ll net = abs(n1 - n2); // 净值
    cout << max(n1, n2) << endl;
    cout << net + 1 << endl;
}
