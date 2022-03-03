#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <list>
#include <algorithm>

using namespace std;

struct Node
{
    int value;
    int prev, next;
};

const int SIZE = 2e5;
Node node[SIZE];
int head, tail, tot;

void init()
{
    tot = 2;
    head = 1;
    tail = 2;
    node[head].next = tail;
    node[tail].prev = head;
}

int insert(int p, int val)
{
    // 在 p 后插入新节点，数据为 val
    int tmp = ++tot;
    node[tmp].value = val;
    node[node[p].next].prev = tmp;
    node[tmp].next = node[p].next;
    node[p].next = tmp;
    node[tmp].prev = p;
    return tmp;
}

void remove(int p)
{
    // 删除节点 p
    node[node[p].prev].next = node[p].next;
    node[node[p].next].prev = node[p].prev;
}

void recycle()
{
    memset(node, 0, sizeof(node));
    head = tail = tot = 0;
}

struct Item
{
    int val;
    int idx; // 反向索引
    Item(){}
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
    // 输入
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

    // 链表
    init();
    vector<int> indexes(n);
    for(int i = 0; i < n; ++i)
    {
        int nodeidx = insert(node[tail].prev, i);
        indexes[A[i].idx] = nodeidx;
    }

    // 枚举
    vector<Item> result(n); // A[result[i]].val, A[result[i]].idx
    for(int i = n - 1; i >= 1; --i)
    {
        int nodeidx = indexes[i];
        if(nodeidx == tail)
            continue;
        int a = A[node[nodeidx].value].val;
        int x = -1, p = -1;
        if(node[nodeidx].prev != head)
        {
            x = A[node[node[nodeidx].prev].value].val;
            p = A[node[node[nodeidx].prev].value].idx;
        }
        if(node[nodeidx].next != tail)
        {
            int x2 = A[node[node[nodeidx].next].value].val;
            int p2 = A[node[node[nodeidx].next].value].idx;
            if(p == -1 || x2 - a < a - x)
            {
                x = x2;
                p = p2;
            }
        }
        result[i].idx = p + 1;
        result[i].val = abs(x - a);
        remove(nodeidx);
        indexes[i] = tail;
    }
    for(int i = 1; i < n; ++i)
        cout << result[i].val << " " << result[i].idx << endl;
}

/* 简易链表
struct Item
{
    int val;
    int idx; // 反向索引
    Item(){}
    Item(int v, int i):val(v),idx(i){}
};

struct Cmp
{
    bool operator()(const Item& i1, const Item& i2) const
    {
        return i1.val < i2.val;
    }
};

struct Node
{
    int value; // 排序后的数组中的索引
    Node *prev, *next;
};

Node *head, *tail;

void init()
{
    // 新建链表
    head = new Node();
    tail = new Node();
    head -> next = tail;
    tail -> prev = head;
}

Node* insert(Node* p, int val)
{
    // 在 p 后插入新节点，数据为 val
    Node *tmp = new Node();
    tmp -> value = val;
    p -> next -> prev = tmp;
    tmp -> next = p -> next;
    p -> next = tmp;
    tmp -> prev = p;
    return tmp;
}

void remove(Node* p)
{
    // 删除节点 p
    p -> prev -> next = p -> next;
    p -> next -> prev = p -> prev;
    delete p;
}

void recycle()
{
    // 链表内存回收
    while(head != tail)
    {
        head = head -> next;
        delete head -> prev;
    }
    delete tail;
}

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

    init();
    vector<Node*> indexes(n);
    for(int i = 0; i < n; ++i)
    {
        Node *node = insert(tail -> prev, i);
        indexes[A[i].idx] = node;
    }

    vector<Item> result(n); // A[result[i]].val, A[result[i]].idx
    for(int i = n - 1; i >= 1; --i)
    {
        Node *node = indexes[i];
        if(node == tail)
            continue;
        int a = A[node -> value].val;
        int x = -1, p = -1;
        if(node -> prev != head)
        {
            x = A[node -> prev -> value].val;
            p = A[node -> prev -> value].idx;
        }
        if(node -> next != tail)
        {
            int x2 = A[node -> next -> value].val;
            int p2 = A[node -> next -> value].idx;
            if(p == -1 || x2 - a < a - x)
            {
                x = x2;
                p = p2;
            }
        }
        result[i].idx = p + 1;
        result[i].val = abs(x - a);
        remove(node);
        indexes[i] = tail;
    }
    for(int i = 0; i < n; ++i)
        cout << result[i].val << " " << result[i].idx << endl;
}*/

/* STL list
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
} */

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
