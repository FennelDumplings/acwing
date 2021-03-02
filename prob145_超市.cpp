#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

struct Item
{
    int p;
    int d;
    Item(int p, int d):p(p),d(d){}
};

struct Sort_cmp
{
    bool operator()(const Item& i1, const Item& i2) const
    {
        return i1.d < i2.d;
    }
};

struct Heap_cmp
{
    bool operator()(const Item& i1, const Item& i2) const
    {
        return i1.p > i2.p;
    }
};

int main()
{
    int N;
    while(cin >> N)
    {
        vector<Item> items;
        for(int i = 0; i < N; ++i)
        {
            int p, d;
            cin >> p >> d;
            items.emplace_back(p, d);
        }
        sort(items.begin(), items.end(), Sort_cmp());
        priority_queue<Item, vector<Item>, Heap_cmp> pq;
        int left = 0;
        int ans = 0;
        for(const Item& i: items)
        {
            pq.push(i);
            ++left;
            ans += i.p;
            if(left > i.d)
            {
                ans -= pq.top().p;
                pq.pop();
                --left;
            }
        }
        cout << ans << endl;
    }
}
