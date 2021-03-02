#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

using ll = long long;

class SegmentTree
{
public:
    SegmentTree(int n)
    {
        this -> n = n;
        tree.assign(n * 4, 0);
        lazy_add.assign(n * 4 , 0);
    }

    void range_update_add(int i, int j, int delta)
    {
        _range_update(0, 0, n - 1, i, j, delta);
    }

    int query()
    {
        return tree[0];
    }

private:
    vector<int> tree; // tree[i] := 当前事件的 x 下, y=i 可以取到的权值和
    vector<int> lazy_add;
    int n;

    void _range_update(int node, int l, int r, int i, int j, int delta)
    {
        if(lazy_add[node] != 0)
        {
            tree[node] = tree[node] + lazy_add[node];
            if(l != r)
            {
                lazy_add[node * 2 + 1] = lazy_add[node * 2 + 1] + lazy_add[node];
                lazy_add[node * 2 + 2] = lazy_add[node * 2 + 2] + lazy_add[node];
            }
            lazy_add[node] = 0;
        }
        // 线段树节点 node 持有的区间 [l, r]，待更新区间 [i, j]
        if(l > r || l > j || i > r)
            return;
        if(i <= l && r <= j)
        {
            tree[node] = tree[node] + delta;
            if(l != r)
            {
                lazy_add[node * 2 + 1] = lazy_add[node * 2 + 1] + delta;
                lazy_add[node * 2 + 2] = lazy_add[node * 2 + 2] + delta;
            }
            return;
        }
        int mid = (l + r) / 2;
        _range_update(node * 2 + 1, l, mid, i, j, delta);
        _range_update(node * 2 + 2, mid + 1, r, i, j, delta);
        tree[node] = max(tree[node * 2 + 1], tree[node * 2 + 2]);
    }
};

struct Rectangle
{
    ll x1, y1, x2, y2;
    Rectangle(){}
    Rectangle(ll x1, ll y1, ll x2, ll y2):x1(x1),y1(y1),x2(x2),y2(y2){}
};

struct Event
{
    vector<Rectangle> *recs;
    int id; // 所属矩形 id
    int left; // 1 表示左边，-1 表示右边
    int w; // 权值
    Event(vector<Rectangle> *recs, int id, int left, int w):recs(recs),id(id),left(left),w(w){}
    ll getx() const
    {
        if(left == 1)
            return (*recs)[id].x1;
        else
            return (*recs)[id].x2;
    }
    bool operator<(const Event& e) const
    {
        if(getx() == e.getx())
            return left < e.left;
        return getx() < e.getx();
    }
};

int find(ll v, const vector<ll>& aa) // 从 nums 的值找到对应的离散化之后的值
{
    return lower_bound(aa.begin(), aa.end(), v) - aa.begin();
}

int solve(vector<Rectangle>& recs, const vector<int>& w)
{
    vector<ll> ys;
    vector<Event> events;
    for(int i = 0; i < (int)recs.size(); ++i)
    {
        ys.push_back(recs[i].y1);
        ys.push_back(recs[i].y2);
        events.emplace_back(&recs, i, 1, w[i]);
        events.emplace_back(&recs, i, -1, w[i]);
    }
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    sort(events.begin(), events.end());

    SegmentTree sttree((int)ys.size());

    int ans = 0;
    for(int i = 0; i < (int)events.size(); ++i)
    {
        int delta = events[i].left * events[i].w;
        ll y1 = recs[events[i].id].y1;
        ll y2 = recs[events[i].id].y2;
        int l = find(y1, ys);
        int r = find(y2, ys);
        // 影响 ys 上的 [l, r) 区间
        sttree.range_update_add(l, r, delta);
        ans = max(ans, sttree.query());
    }
    return ans;
}

int main()
{
    int n;
    ll W, H;
    while(cin >> n >> W >> H && (n > 0))
    {
        vector<Rectangle> recs;
        vector<int> ws;
        for(int i = 0; i < n; ++i)
        {
            ll x, y, w;
            cin >> x >> y >> w;
            recs.emplace_back(x, y, x + W, y + H - 1);
            ws.push_back(w);
        }
        int ans = solve(recs, ws);
        cout << ans << endl;
    }
}
