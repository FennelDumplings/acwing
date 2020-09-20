
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <cmath>

using namespace std;

using ll = long long;

const int N = 3;
const int M = 3;
const int L = N * M;

// “u”、“d”、“l”、“r”
int d[4] = {-M, M, -1, 1};
string ops = "udlr";
unordered_set<ll> visited;
vector<int> idx_end;
vector<vector<int>> dist;

void _swap(ll& s, int x, int y)
{
    // 交换 x, y 元素
    x = L - 1 - x;
    y = L - 1 - y;
    ll digit = (s / (ll)pow(10, x)) % 10;
    ll digit2 = (s / (ll)pow(10, y)) % 10;
    s -= digit * (ll)pow(10, x);
    s -= digit2 * (ll)pow(10, y);
    s += digit * (ll)pow(10, y);
    s += digit2 * (ll)pow(10, x);
}

void change_zero(ll& s, int zero_idx)
{
    int x = zero_idx / M;
    int y = zero_idx % M;
    while(y < M - 1)
    {
        _swap(s, zero_idx, zero_idx + 1);
        ++y;
        ++zero_idx;
    }
    while(x < N - 1)
    {
        _swap(s, zero_idx, zero_idx + M);
        ++x;
        zero_idx += M;
    }
}

int get_digit(ll s, int i)
{
    return (s / (ll)pow(10, (L - 1 - i))) % 10;
}

bool check(ll s, ll t, int zero_idx)
{
    change_zero(s, zero_idx);
    vector<int> idx(L, -1);
    idx_end.assign(L, -1);
    for(int i = 0; i < L; ++i)
    {
        idx[get_digit(s, i)] = i;
        idx_end[get_digit(t, i)] = i;
    }
    int swap_cnt = 0;
    for(int i = 0; i < L; ++i)
    {
        ll a = get_digit(s, i);
        ll b = get_digit(t, i);
        if(a == b)
            continue;
        int j = idx[b];
        _swap(s, i, j);
        idx[b] = i;
        idx[a] = j;
        ++swap_cnt;
    }
    return (swap_cnt & 1) == 0;
}

int h(ll s)
{
    int ans = 0;
    for(int i = 0; i < L; ++i)
    {
        int digit = get_digit(s, i);
        if(digit == 0)
            continue;
        int j = idx_end[digit];
        ans += dist[i][j];
    }
    return ans;
}

bool dfs(ll s, const ll t, int zero_idx, int deep, const int max_depth, string& path)
{
    if(deep + h(s) > max_depth)
        return false;
    if(s == t)
        return true;
    for(int i = 0; i < 4; ++i)
    {
        int nxt_zero_idx = zero_idx + d[i];
        if(nxt_zero_idx < 0 || nxt_zero_idx >= L || (nxt_zero_idx / M != zero_idx / M && nxt_zero_idx % M != zero_idx % M))
            continue;
        ll nxt_s = s;
        _swap(nxt_s, nxt_zero_idx, zero_idx);
        if(visited.count(nxt_s))
            continue;
        visited.insert(nxt_s);
        path += ops[i];
        if(dfs(nxt_s, t, nxt_zero_idx, deep + 1, max_depth, path))
            return true;
        path.pop_back();
        visited.erase(nxt_s);
    }
    return false;
}

void init_manhattan()
{
    dist.assign(L, vector<int>(L, -1));
    for(int i = 0; i < L; ++i)
    {
        for(int j = 0; j < L; ++j)
        {
            dist[i][j] = (abs(i / M - j / M) + abs(i % M - j % M));
        }
    }
}

int main()
{
    // fstream fin("test/prob179.test");
    ll end = 123456780;
    ll start = 0;
    int zero_idx = -1;
    for(int i = 0; i < L; ++i)
    {
        char ch;
        cin >> ch;
        start *= 10;
        if(ch == 'x')
        {
            zero_idx = i;
            continue;
        }
        int num = ch - '0';
        start += num;
    }
    if(!check(start, end, zero_idx))
    {
        cout << "unsolvable" << endl;
        return 0;
    }
    init_manhattan();
    int depth = 0;
    visited.insert(start);
    string path;
    while(!dfs(start, end, zero_idx, 0, depth, path))
    {
        ++depth;
        path = "";
        visited.clear();
        visited.insert(start);
    }
    cout << path << endl;
}
