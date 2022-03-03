#include <cstring>
#include <vector>
#include <iostream>

using namespace std;

const int E_SIZE = 2e4; // 总边数
const int V_SIZE = 2e2; // 总点数

int head[V_SIZE]; // head[i] 的值是 ver 下标，相当于链表节点指针
int ver[E_SIZE]; // 边的终点，相当于链表节点的 v 字段
int next_[E_SIZE]; // 相当于链表节点的 next 字段

int tot;
// tot 表示 node 数组(这里是 ver 和 next)已使用的最右位置，而不是链表长度

void init()
{
    tot = 0;
    memset(head, 0, sizeof(head));
    memset(next_, 0, sizeof(next_));
}

// 增加有向边 (x, y), 权值为 z
void add(int x, int y)
{
    ver[++tot] = y;
    next_[tot] = head[x], head[x] = tot; // 在表头 x 处插入
}

bool visited[V_SIZE];
bool match[V_SIZE];

bool dfs(int x)
{
    // 此时 x 是非匹配点
    // 返回是否找到增广路
    for(int i = head[x]; i != 0; i = next_[i])
    {
        int y = ver[i];
        if(!visited[y])
        {
            visited[y] = 1;
            if(!match[y] || dfs(match[y]))
            {
                match[y] = x; // 若找到增广路，回溯阶段把各个边的匹配状态取反
                return true;
            }
        }
    }
    return false;
}

int main()
{
    // 输入
    int N, t;
    cin >> N >> t;
    vector<vector<bool>> forbidden(N + 1, vector<bool>(N + 1, false));
    for(int i = 0; i < t; ++t)
    {
        int x, y;
        cin >> x >> y;
        forbidden[x][y] = true;
    }

    // 建图
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    init();
    for(int i = 1; i <= N; ++i)
        for(int j = 1; j <= N; ++j)
        {
            int u = (i - 1) * N + (j - 1);
            for(int d = 0; d < 4; ++d)
            {
                int x = i + dx[d];
                int y = j + dy[d];
                if(x < 1 || x > N || y < 1 || y > N)
                    continue;
                if(forbidden[x][y])
                    continue;
                int v = (x - 1) * N + (y - 1);
                add(u, v);
            }
        }

    int ans = 0;
    for(int i = 1; i <= N; ++i)
        for(int j = 1; j <= N; ++j)
        {
            if(forbidden[i][j])
                continue;
            int u = (i - 1) * N + (j - 1);
            memset(visited, 0, sizeof(visited));
            if(dfs(u))
                ++ans;
        }
    cout << ans << endl;
}
