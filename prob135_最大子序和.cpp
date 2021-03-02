#include <iostream>
#include <vector>
#include <deque>
#include <climits>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> sums(n + 1);
    deque<int> deq;
    deq.push_back(0);
    int ans = INT_MIN;
    for(int i = 0; i < n; ++i)
    {
        int v;
        cin >> v;
        sums[i + 1] = sums[i] + v;
        int mx = sums[deq.front()];
        ans = max(ans, sums[i + 1] - mx);
        while(!deq.empty() && sums[deq.back()] >= sums[i + 1])
            deq.pop_back();
        deq.push_back(i + 1);
        // i - (deq.front() - 1) + 1 <= m - 1
        if(i - (deq.front() - 1) + 1 > m)
            deq.pop_front();
    }
    cout << ans << endl;
}
