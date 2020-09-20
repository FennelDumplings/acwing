#include <iostream>

using namespace std;

using ll = long long;

int quickpower2(int a, int b, int p)
{
    int ans = 1;
    while(b)
    {
        if(b & 1) ans = ((ll)ans * a) % p;
        a = (ll)a * a % p;
        b >>= 1;
    }
    return ans % p;
}

int main()
{
    int a, b, p;
    cin >> a >> b >> p;
    cout << quickpower2(a, b, p) << endl;
}
