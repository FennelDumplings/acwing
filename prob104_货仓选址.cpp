#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> a(N);
    for(int i = 0; i < N; ++i)
        cin >> a[i];
    sort(a.begin(), a.end());
    int X = *(a.begin() + (N / 2));
    int ans = 0;
    for(int i = 0; i < N; ++i)
        ans += abs(a[i] - X);
    cout << ans << endl;
}
