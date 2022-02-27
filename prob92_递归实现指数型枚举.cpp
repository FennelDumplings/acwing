#include <iostream>
#include <vector>

using namespace std;

void dfs(vector<int>& vec, int i, const int n)
{
    if(i > n)
    {
        for(int x: vec)
            cout << x << " ";
        cout << endl;
        return;
    }
    dfs(vec, i + 1, n);
    vec.push_back(i);
    dfs(vec, i + 1, n);
    vec.pop_back();
}

int main()
{
    int n;
    cin >> n;

    vector<int> vec;
    dfs(vec, 1, n);
}
