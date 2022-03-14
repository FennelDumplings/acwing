#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

// 邻接表
const int E_SIZE = 8e4; // 总边数
const int V_SIZE = 2e4; // 总点数

int head[V_SIZE]; // head[i] 的值是 ver 下标，相当于链表节点指针
int ver[E_SIZE]; // 边的终点，相当于链表节点的 v 字段
int next_[E_SIZE]; // 相当于链表节点的 next 字段

// tot 表示 node 数组(这里是 ver 和 next)已使用的最右位置，而不是链表长度
int tot;

void init()
{
    tot = 0;
    memset(head, -1, sizeof(head));
    memset(next_, -1, sizeof(next_));
}

void add(int x, int y)
{
    // 增加有向边 (x, y)
    ver[++tot] = y;
    next_[tot] = head[x];
    head[x] = tot; // 在表头 x 处插入
}

// 匈牙利算法
bool visited[V_SIZE];
bool forbidden[V_SIZE];
int match[V_SIZE];

int key(int x, int y, int N)
{
    // 棋盘坐标与图节点编号的映射
    return (x - 1) * N + (y - 1);
}

bool dfs(int u)
{
    // 返回是否找到增广路
    for(int i = head[u]; i != -1; i = next_[i])
    {
        int v = ver[i];
        if(visited[v])
            continue;
        visited[v] = true;
        if(match[v] == -1 || dfs(match[v]))
        {
            match[v] = u; // 若找到增广路，回溯阶段把各个边的匹配状态取反
            return true;
        }
    }
    return false;
}

int main()
{
    // 输入
    int N, t;
    cin >> N >> t;
    memset(forbidden, false, sizeof(forbidden));
    for(int i = 0; i < t; ++i)
    {
        int x, y;
        cin >> x >> y;
        forbidden[key(x, y, N)] = true;
    }

    // 建图
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    init();
    for(int i = 1; i <= N; ++i)
        for(int j = 1; j <= N; ++j)
        {
            int u = key(i, j, N);
            if(forbidden[u])
                continue;
            for(int d = 0; d < 4; ++d)
            {
                int x = i + dx[d];
                int y = j + dy[d];
                if(x < 1 || x > N || y < 1 || y > N)
                    continue;
                int v = key(x, y, N);
                if(forbidden[v])
                    continue;
                add(u, v);
            }
        }

    int ans = 0;
    memset(match, -1, sizeof(match));
    for(int i = 1; i <= N; ++i)
        for(int j = 1; j <= N; ++j)
        {
            int u = key(i, j, N);
            if(forbidden[u])
                continue;
            memset(visited, false, sizeof(visited));
            // 此时 u 是非匹配点
            if(dfs(u))
                ++ans;
        }
    cout << ans / 2 << endl;
}
