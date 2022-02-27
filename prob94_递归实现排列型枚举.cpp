#include <iostream>
#include <vector>

using namespace std;

void dfs(vector<int>& vec, int n, int& visited)
{
    if(vec.size() == n)
    {
        for(int x: vec)
            cout << x << " ";
        cout << endl;
        return;
    }
    for(int i = 1; i <= n; ++i)
    {
        if(visited >> i & 1)
            continue;
        vec.push_back(i);
        visited |= (1 << i);
        dfs(vec, n, visited);
        vec.pop_back();
        visited &= ~(1 << i);
    }
}

int main()
{
    int n;
    cin >> n;

    vector<int> vec;
    // visited >> i & 1 表示 i 是否已经选了
    int visited = 0;
    dfs(vec, n, visited);
}
