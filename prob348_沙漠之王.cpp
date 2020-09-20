
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>
#include <cmath>
#include <iomanip>

using namespace std;

const double eps = 1e-9;

struct Edge
{
    int v;
    double w;
    Edge(int v, double w):v(v),w(w){}
};

struct Cmp
{
    bool operator()(const Edge& e1, const Edge& e2) const
    {
        return e1.w > e2.w;
    }
};

double mst(const vector<vector<Edge>>& g)
{
    int N = g.size();
    vector<bool> visited(N, false);
    priority_queue<Edge, vector<Edge>, Cmp> pq;
    pq.push(Edge(0, 0.0));
    double cost = 0.0;
    while(!pq.empty())
    {
        Edge e = pq.top();
        pq.pop();
        if(visited[e.v])
            continue;
        visited[e.v] = true;
        cost += e.w;
        for(Edge son: g[e.v])
        {
            if(visited[son.v])
                continue;
            pq.push(son);
        }
    }
    for(int v: visited)
        if(!v)
            return -1;
    return cost;
}

struct Point
{
    int x, y, z;
    Point(int x, int y, int z):x(x),y(y),z(z){}
};

struct EdgeInfo
{
    double cost;
    double dist;
    EdgeInfo(double c, double d):cost(c),dist(d){}
};

bool check(double mid, const vector<vector<EdgeInfo>>& edgeinfos)
{
    int N = edgeinfos.size();
    vector<vector<Edge>> g(N);
    for(int i = 0; i < N - 1; ++i)
        for(int j = i + 1; j < N; ++j)
        {
            double w = edgeinfos[i][j].cost - mid * edgeinfos[i][j].dist;
            g[i].emplace_back(j, w);
            g[j].emplace_back(i, w);
        }
    double ans = mst(g);
    return ans + eps < 0;
}

int main()
{
    int N;
    while(cin >> N && N > 0)
    {
        vector<Point> points;
        for(int i = 0; i < N; ++i)
        {
            int x, y, z;
            cin >> x >> y >> z;
            points.emplace_back(x, y, z);
        }
        vector<vector<EdgeInfo>> edgeinfos(N, vector<EdgeInfo>(N, EdgeInfo(-1, -1)));
        for(int i = 0; i < N - 1; ++i)
            for(int j = i + 1; j < N; ++j)
            {
                edgeinfos[i][j].cost = abs(points[i].z - points[j].z);
                edgeinfos[i][j].dist = sqrt(pow(abs(points[i].x - points[j].x), 2) + pow(abs(points[i].y - points[j].y), 2));
            }
        double left = 0.0, right = (double)1e9;
        while(left + eps < right)
        {
            double mid = (left + right) / 2;
            if(check(mid, edgeinfos))
                right = mid;
            else
                left = mid;
        }
        cout << setiosflags(ios::fixed) << setprecision(3);
        cout << left << endl;
    }
}
