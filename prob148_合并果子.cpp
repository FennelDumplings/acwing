

#include <vector>
#include <iostream>
#include <queue>
#include <functional>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    priority_queue<int, vector<int>, greater<int>> pq(a.begin(), a.end());
    int ans = 0;
    while((int)pq.size() > 1)
    {
        int ai = pq.top();
        pq.pop();
        int aj = pq.top();
        pq.pop();
        int fa = ai + aj;
        ans += fa;
        pq.push(fa);
    }
    cout << ans << endl;
}
