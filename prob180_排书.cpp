
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

using ll = long long;
const int MOD = 1e9 + 7;

bool check(const vector<int>& s, const vector<int>& t)
{
    int n = s.size();
    for(int i = 1; i < n; ++i)
        if(s[i] != t[i])
            return false;
    return true;
}

void show(const vector<int>& s)
{
    for(int i: s) cout << i << " ";
    cout << endl;
}

int h(const vector<int>& s)
{
    int ans = 0;
    int n = s.size();
    for(int i = 1; i < n; ++i)
    {
        if(s[i] != s[i - 1] + 1)
            ++ans;
    }
    return (ans + 2) / 3;
}

bool dfs(const vector<int>& s, const vector<int>& t, int deep, const int max_deep)
{
    if(deep + h(s) > max_deep)
        return false;
    if(check(s, t))
    {
        return true;
    }
    int n = s.size();
    for(int i = 1; i < n; ++i)
    {
        for(int j = i; j <= n; ++j)
        {
            for(int k = j; k <= n; ++k)
            {
                // [0..i..j..k..n-1]
                vector<int> nxt(s.begin(), s.begin() + i);
                nxt.insert(nxt.end(), s.begin() + j, s.begin() + k);
                nxt.insert(nxt.end(), s.begin() + i, s.begin() + j);
                nxt.insert(nxt.end(), s.begin() + k, s.end());
                if(dfs(nxt, t, deep + 1, max_deep))
                    return true;
            }
        }
    }
    return false;
}

// 1 3 4 6 2 5
int solve(vector<int>& books)
{
    vector<int> start = books;
    vector<int> t = books;
    sort(t.begin(), t.end());
    int depth = 0;
    while(depth < 5 && !dfs(start, t, 0, depth))
    {
        ++depth;
        start = books;
    }
    if(depth == 5)
        return -1;
    return depth;
}

int main()
{
    int T;
    cin >> T;
    for(int i = 1; i <= T; ++i)
    {
        int n;
        cin >> n;
        vector<int> books(n + 1);
        for(int j = 1; j <= n; ++j)
            cin >> books[j];
        int ans = solve(books);
        if(ans == -1)
            cout << "5 or more" << endl;
        else
            cout << ans << endl;
    }
}

