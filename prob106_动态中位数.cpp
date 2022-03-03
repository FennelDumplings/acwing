#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

struct Node
{
    int value;
    int prev, next;
};

const int SIZE = 2e5;
Node node[SIZE];
int head, tail, tot;
// tot 表示 node 数组已使用的最右位置，而不是链表长度

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
    int P;
    cin >> P;

    for(int x = 1; x <= P; ++x)
    {
        // 输入
        int idx, n;
        cin >> idx >> n;
        vector<Item> vec(n);
        for(int j = 0; j < n / 10; ++j)
        {
            for(int k = 0; k < 10; ++k)
            {
                int v;
                cin >> v;
                vec[j * 10 + k] = Item(v, j * 10 + k);
            }
        }
        for(int k = 0; k < n % 10; ++k)
        {
            int v;
            cin >> v;
            vec[(n / 10) * 10 + k] = Item(v, (n / 10) * 10 + k);
        }
        sort(vec.begin(), vec.end(), Cmp());

        // 链表
        init();
        vector<int> indexes(n);
        for(int i = 0; i < n; ++i)
        {
            int nodeidx = insert(node[tail].prev, i);
            indexes[vec[i].idx] = nodeidx;
        }

        // 枚举
        int m = (n + 1) / 2;
        cout << idx << " " << m << endl;
        vector<int> result(m);
        int median_node = head;
        for(int i = 0; i < (n + 1) / 2; ++i)
        {
            median_node = node[median_node].next;
        }
        result[m - 1] = vec[node[median_node].value].val;
        for(int i = n - 1; i >= 1; --i)
        {
            int nodeidx = indexes[i];
            if(i & 1)
            {
                if(node[nodeidx].value <= node[median_node].value)
                    median_node = node[median_node].next;
                result[(i + 1) / 2 - 1] = vec[node[median_node].value].val;
            }
            else
            {
                if(node[nodeidx].value >= node[median_node].value)
                    median_node = node[median_node].prev;
            }
            remove(nodeidx);
            indexes[i] = tail;
        }

        for(int i = 0; i < m / 10; ++i)
        {
            for(int j = 0; j < 10; ++j)
                cout << result[i * 10 + j] << " ";
            cout << endl;
        }
        if(m % 10 > 0)
        {
            for(int j = 0; j < m % 10; ++j)
                cout << result[(m / 10) * 10 + j] << " ";
            cout << endl;
        }
    }
}
