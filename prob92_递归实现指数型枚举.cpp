#include <iostream>
#include <vector>

using namespace std;

vector<int> vec; // 被选择的
int n;

void dfs(int i)
{
    if(i > n)
    {
        // 问题边界
        for(int x: vec)
            cout << x << " ";
        cout << endl;
        return;
    }
    // 不选 i
    dfs(i + 1);
    // 选 i
    vec.push_back(i); // 记录 i 已被选择
    dfs(i + 1);
    vec.pop_back(); // 回溯前，还原现场
}

int main()
{
    cin >> n;
    dfs(1);
}

/*
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
*/
