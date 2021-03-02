
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

using ll = long long;

struct Node
{
    ll w;
    ll d;
    Node(ll w, ll d):w(w),d(d){}
};

struct HeapCmp
{
    bool operator()(const Node& node1, const Node& node2) const
    {
        if(node1.w == node2.w)
            return node1.d > node2.d;
        return node1.w > node2.w;
    }
};

int main()
{
    int n, k;
    cin >> n >> k;
    priority_queue<Node, vector<Node>, HeapCmp> pq;
    for(int i = 0; i < n; ++i)
    {
        ll w;
        cin >> w;
        pq.push(Node(w, 0));
    }

    if((n - 1) % (k - 1) != 0)
    {
        int m = k - ((n - 1) % (k - 1)) - 1;
        for(int i = 0; i < m; ++i)
            pq.push(Node(0, 0));
    }
    ll ans = 0;
    while(pq.size() != 1)
    {
        ll d = 0, w = 0;
        for(int j = 0; j < k; ++j)
        {
            Node node = pq.top();
            pq.pop();
            d = max(d, node.d + 1);
            w += node.w;
        }
        pq.push({w, d});
        ans += w;
    }
    cout << ans << endl;
    cout << pq.top().d << endl;
}

