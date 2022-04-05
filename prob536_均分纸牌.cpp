#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> a(N);
    int sum = 0;
    for(int i = 0; i < N; ++i)
    {
        cin >> a[i];
        sum += a[i];
    }
    int ans = 0;
    int diff = 0;
    int t = sum / N;
    for(int i = 0; i < N - 1; ++i)
    {
        diff = a[i] + diff - t;
        ans += abs(diff);
    }
    cout << ans << endl;
}
