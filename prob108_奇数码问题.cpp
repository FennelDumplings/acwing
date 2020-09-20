
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void change_zero(vector<vector<int>>& s)
{
    // 将 s 中的 0 交换至右下角
    int N = s.size();
    int x = -1,y = -1;
    for(int i = 0; i < N; ++i)
        for(int j = 0; j < N; ++j)
        {
            if(s[i][j] == 0)
            {
                x = i;
                y = j;
                break;
            }
        }
    while(x < N - 1)
    {
        swap(s[x][y], s[x + 1][y]);
        ++x;
    }
    while(y < N - 1)
    {
        swap(s[x][y], s[x][y + 1]);
        ++y;
    }
}

bool check(vector<vector<int>>& s, vector<vector<int>>& t)
{
    int N = s.size();
    change_zero(s);
    change_zero(t);
    vector<int> idx_i(N * N, -1);
    vector<int> idx_j(N * N, -1);
    for(int i = 0; i < N; ++i)
        for(int j = 0; j < N; ++j)
        {
            idx_i[s[i][j]] = i;
            idx_j[s[i][j]] = j;
        }
    int swap_cnt = 0;
    for(int i = 0; i < N; ++i)
        for(int j = 0; j < N; ++j)
        {
            if(s[i][j] == t[i][j])
                continue;
            int a = s[i][j];
            int x = idx_i[t[i][j]];
            int y = idx_j[t[i][j]];
            swap(s[i][j], s[idx_i[t[i][j]]][idx_j[t[i][j]]]);
            idx_i[a] = x;
            idx_j[a] = y;
            ++swap_cnt;
        }
    return (swap_cnt & 1) == 0;
}

int main()
{
    int N;
    while(cin >> N)
    {
        vector<vector<int>> s(N, vector<int>(N, -1));
        vector<vector<int>> t(N, vector<int>(N, -1));
        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < N; ++j)
                cin >> s[i][j];
        }
        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < N; ++j)
                cin >> t[i][j];
        }
        if(check(s, t))
            cout << "TAK" << endl;
        else
            cout << "NIE" << endl;
    }
}

