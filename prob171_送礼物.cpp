#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

using ll = long long;

void dfs1(const vector<int>& A, const int W, int w, int pos, const int t, vector<int>& tmp)
{
    if(pos == t)
    {
        tmp.push_back(w);
        return;
    }
    dfs1(A, W, w, pos + 1, t, tmp);
    if((ll)w + A[pos] <= W)
        dfs1(A, W, w + A[pos], pos + 1, t, tmp);
}

void dfs2(const vector<int>& A, const int W, int w, int pos, const int t, int& ans, vector<int>& tmp)
{
    if(pos == t)
    {
        // 找 w + x <= W 的最大 x, t <= W - w 的最大 x
        auto it = upper_bound(tmp.begin(), tmp.end(), W - w);
        if(it != tmp.begin())
        {
            int x = *(--it);
            ans = max(ans, w + x);
            return;
        }
    }
    dfs2(A, W, w, pos + 1, t, ans, tmp);
    if((ll)w + A[pos] <= W)
        dfs2(A, W, w + A[pos], pos + 1, t, ans, tmp);
}

int solve(const vector<int>& A, const int W)
{
    int N = A.size();
    vector<int> tmp;
    dfs1(A, W, 0, 0, N / 2 + 3, tmp);
    sort(tmp.begin(), tmp.end());
    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
    int ans = 0;
    dfs2(A, W, 0, N / 2 + 3, N, ans, tmp);
    return ans;
}

int main()
{
    int W, N;
    cin >> W >> N;
    vector<int> A(N);
    for(int i = 0; i < N; ++i)
        cin >> A[i];
    sort(A.begin(), A.end(), greater<int>());
    int ans = solve(A, W);
    cout << ans << endl;
}
