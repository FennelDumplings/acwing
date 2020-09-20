#include <vector>
#include <climits>
#include <iostream>

using namespace std;

void get_path(vector<int>& path, int x, int y, const vector<vector<int>>& pos)
{
    if(pos[x][y] == 0) return;
    get_path(path, x, pos[x][y], pos);
    path.push_back(pos[x][y]);
    get_path(path, pos[x][y], y, pos);
}

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> adj(N + 1, vector<int>(N + 1, INT_MAX / 2));
    for(int i = 1; i <= M; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        if(u < 1 || u > N || v < 1 || v > N) continue;
        adj[u][v] = min(adj[u][v], w);
        adj[v][u] = min(adj[v][u], w);
    }
    for(int i = 1; i <= N; ++i)
        adj[i][i] = 0;
    vector<vector<int>> d = adj;
    int ans = INT_MAX / 2;
    vector<int> path;
    vector<vector<int>> pos(N + 1, vector<int>(N + 1, 0));
    for(int k = 1; k <= N; ++k)
    {
        for(int i = 1; i < k; ++i)
            for(int j = i + 1; j < k; ++j)
            {
                if(ans > (long long)d[i][j] + adj[j][k] + adj[k][i])
                {
                    ans = d[i][j] + adj[j][k] + adj[k][i];
                    path.clear();
                    path.push_back(i);
                    get_path(path, i, j, pos);
                    path.push_back(j);
                    path.push_back(k);
                }
            }
        for(int i = 1; i <= N; ++i)
            for(int j = 1; j <= N; ++j)
            {
                if(d[i][j] > d[i][k] + d[k][j])
                {
                    d[i][j] = d[i][k] + d[k][j];
                    pos[i][j] = k;
                }
            }
    }
    if(ans == INT_MAX / 2)
        cout << "No solution." << endl;
    else
    {
        for(int i: path) cout << i << " ";
        cout << endl;
    }
}
