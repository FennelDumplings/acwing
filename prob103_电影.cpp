#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

struct MovieInfo
{
    int idx; // 电影编号
    int b; // 懂该电影声音语言的人数
    int c; // 懂该电影字幕语言的人数
    MovieInfo(){}
    bool operator<(const MovieInfo& movie) const
    {
        if(b == movie.b)
            return c < movie.c;
        return b < movie.b;
    }
};

int main()
{
    int n;
    cin >> n;
    vector<int> a(n); // a[i] := 第 i 个人懂的语言
    unordered_map<int, int> mapping;
    for(int i = 0; i < n; ++i)
    {
        cin >> a[i];
        ++mapping[a[i]];
    }
    int m;
    cin >> m;
    // b[i] := 第 i 个电影的声音语言
    // c[i] := 第 i 个电影的字幕语言
    vector<int> b(m), c(m);
    for(int i = 0; i < m; ++i)
        cin >> b[i];
    for(int i = 0; i < m; ++i)
        cin >> c[i];
    vector<MovieInfo> movies(m);
    for(int i = 0; i < m; ++i)
    {
        movies[i].idx = i;
        movies[i].b = mapping[b[i]];
        movies[i].c = mapping[c[i]];
    }
    sort(movies.begin(), movies.end());
    cout << movies.back().idx + 1 << endl;
}
