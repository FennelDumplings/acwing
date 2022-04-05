#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

ll merge_sort(vector<ll>& a, int l, int r)
{
    if(l == r)
        return 0;
    int mid = (l + r) / 2;
    ll n1 = merge_sort(a, l, mid);
    ll n2 = merge_sort(a, mid + 1, r);
    int i = l;
    int j = mid + 1;
    ll n3 = 0;
    vector<int> tmp(r - l + 1);
    int k = 0;
    while(i <= mid && j <= r)
    {
        if(a[i] > a[j])
        {
            n3 += mid + 1 - i;
            tmp[k++] = a[j++];
        }
        else
            tmp[k++] = a[i++];
    }
    while(i <= mid)
        tmp[k++] = a[i++];
    while(j <= r)
        tmp[k++] = a[j++];
    for(int i = l; i <= r; ++i)
        a[i] = tmp[i - l];
    return n1 + n2 + n3;
}

int main()
{
    vector<ll> a;
    while(true)
    {
        int n;
        cin >> n;
        if(n == 0)
            break;
        a.assign(n, -1);
        for(int i = 0; i < n; ++i)
            cin >> a[i];
        ll ans = merge_sort(a, 0, n - 1);
        cout << ans << endl;
    }
}
