
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool dfs(vector<int>& result, int depth, int max_depth, int n)
{
    if(depth > max_depth)
        return false;
    if(n == result.back())
        return true;
    int m = result.size();
    for(int i = m - 1; i >= m - 1; --i)
    // for(int i = m - 1; i >= 0; --i) 可行性剪枝
    // for(int i = 0; i < m; ++i) 搜索顺序
    {
        for(int j = i; j >= 0; --j)
        // for(int j = i; j < m; ++j)
        {
            int nxt = result[i] + result[j];
            if(nxt <= result.back() || nxt > n) continue;
            result.push_back(nxt);
            if(dfs(result, depth + 1, max_depth, n))
                return true;
            result.pop_back();
        }
    }
    return false;
}

vector<int> solve(int n)
{
    vector<int> result(1, 1);
    int depth = 0; // 从 [0] 往前跳了 depth 步, result 中有 depth + 1 个元素
    while(!dfs(result, 0, depth, n))
    {
        ++depth;
        result.assign(1, 1);
    }
    return result;
}

int main()
{
    // fstream fin("test/prob170.test");
    int n;
    while(cin >> n && n != 0)
    {
        vector<int> ans = solve(n);
        for(int i: ans)
            cout << i << " ";
        cout << endl;
    }
}
