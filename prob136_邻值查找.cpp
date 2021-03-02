
#include <iostream>
#include <vector>
#include <cmath>
#include <list>
#include <algorithm>

using namespace std;

struct Item
{
    int val;
    int idx; // 反向索引
    Item(int v, int i):val(v),idx(i){}
};

struct Cmp
{
    bool operator()(const Item& i1, const Item& i2) const
    {
        return i1.val < i2.val;
    }
};

int main()
{
    int n;
    cin >> n;
    vector<Item> A;
    for(int i = 0; i < n; ++i)
    {
        int v;
        cin >> v;
        A.emplace_back(v, i);
    }
    sort(A.begin(), A.end(), Cmp());
    vector<list<Item>::iterator> indexes(n);
    // indexes[i] := 原始位置为 i 的元素 A[i] 在链表中对应的元素
    list<Item> l;
    for(int i = n - 1; i >= 0; --i)
    {
        l.push_front(A[i]);
        indexes[A[i].idx] = l.begin();
    }
    vector<Item> result;
    for(int i = n - 1; i >= 1; --i)
    {
        auto it = indexes[i];
        if(it == l.end()) continue;
        int a = it -> val;
        int x = -1, p = -1;
        if(it != l.begin())
        {
            --it;
            int x1 = it -> val;
            int p1 = it -> idx;
            x = x1;
            p = p1;
            ++it;
        }
        ++it;
        if(it != l.end())
        {
            int x2 = it -> val;
            int p2 = it -> idx;
            if(p == -1 || x2 - a < a - x)
            {
                x = x2;
                p = p2;
            }
        }
        --it;
        result.emplace_back(abs(a - x), p + 1);
        l.erase(it);
        indexes[i] = l.end();
    }
    int m = result.size();
    for(int i = m - 1; i >= 0; --i)
        cout << result[i].val << " " << result[i].idx << endl;
}

/* 平衡树
#include <map>
int main()
{
    int n;
    cin >> n;
    vector<int> A(n);
    map<int, int> mapping;
    for(int i = 0; i < n; ++i)
    {
        cin >> A[i];
        mapping[A[i]] = i;
        if(i == 0) continue;
        // 2 < i < n
        // 1 <= j < i
        // 比 A[i] 大的最小的数 x1, 下标 p1
        // 比 A[i] 小的最大的数 x2, 下标 p2
        int x = -1, p = -1;
        auto it1 = mapping.upper_bound(A[i]);
        if(it1 != mapping.end())
        {
            int x1 = it1 -> first;
            int p1 = it1 -> second;
            x = x1;
            p = p1;
        }
        auto it2 = mapping.lower_bound(A[i]);
        if(it2 != mapping.begin())
        {
            --it2;
            int x2 = it2 -> first;
            int p2 = it2 -> second;
            if(p == -1 || x - A[i] >= A[i] - x2)
            {
                x = x2;
                p = p2;
            }
        }
        cout << abs(A[i] - x) << " " << p + 1 << endl;
    }
}
*/
