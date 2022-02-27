#include <iostream>
#include <vector>

using namespace std;

void dfs(vector<int>& vec, int i, const int n, const int m)
{
    if(vec.size() == m)
    {
        for(int x: vec)
            cout << x << " ";
        cout << endl;
        return;
    }
    if(vec.size() + n - i + 1 < m)
        return;
    vec.push_back(i);
    dfs(vec, i + 1, n, m);
    vec.pop_back();
    dfs(vec, i + 1, n, m);
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> vec;
    dfs(vec, 1, n, m);
}
