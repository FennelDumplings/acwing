
#include <iostream>

using namespace std;

using ll = long long;

ll mul(ll a, ll b, ll p)
{
    ll ans = 0;
    while(b)
    {
        if(b & 1)
            ans = (ans + a) % p;
        b >>= 1;
        a = (a * 2) % p;
    }
    return ans;
}

int main()
{
    ll a, b, p;
    cin >> a;
    cin >> b;
    cin >> p;
    cout << mul(a, b, p) << endl;
}
