#include <iostream>
#include <cstdlib>

using namespace std;

const int SIZE = 100005;

struct TreapNode
{
    int l, r;
    int val;
    int w; // 权值
    int cnt; // 副本数
    int size; // 子树大小
};

TreapNode a[SIZE];

int tot, root, n, INF = 0x7fffffff;

int New(int val)
{
    a[++tot].val = val;
    a[tot].w = rand();
    a[tot].cnt = 1;
    a[tot].size = 1;
    return tot;
}

void update_size(int p)
{
    // 用当前节点的 cnt 和左右子树的 size 更新当前子树的 size
    a[p].size = a[a[p].l].size + a[a[p].r].size + a[p].cnt;
}

void init()
{
    New(-INF);
    New(INF);
    root = 1;
    a[1].r = 2;
    update_size(root);
}

void zig(int& p)
{
    // 调用方保证 a[p].l 不为 0
    int tmp = a[p].l;
    a[p].l = a[tmp].r;
    a[tmp].r = p;
    p = tmp;
    update_size(a[p].r);
    update_size(p);
}

void zag(int& p)
{
    // 调用方保证 a[p].r 不为 0
    int tmp = a[p].r;
    a[p].r = a[tmp].l;
    a[tmp].l = p;
    p = tmp;
    update_size(a[p].l);
    update_size(p);
}

void insert(int& p, int val)
{
    if(p == 0)
    {
        p = New(val);
        return;
    }
    if(val == a[p].val)
    {
        ++a[p].cnt;
        update_size(p);
        return;
    }
    if(val < a[p].val)
    {
        // 往左子树插入
        insert(a[p].l, val);
        if(a[p].w < a[a[p].l].w)
            zig(p); // p 的左子节点违反堆性质 右旋
    }
    else
    {
        // 往右子树插入
        insert(a[p].r, val);
        if(a[p].w < a[a[p].r].w)
            zag(p); // p 的右子节点违反堆性质 左旋
    }
    update_size(p);
}

void insert(int val)
{
    insert(root, val);
}

void remove(int& p, int val)
{
    if(p == 0)
        return;
    if(val == a[p].val)
    {
        if(a[p].cnt > 1)
        {
            --a[p].cnt;
            update_size(p);
            return;
        }
        if(a[p].l > 0 || a[p].r > 0)
        {
            // 不是叶子节点，向下旋转
            if(a[p].r == 0 || a[a[p].l].w > a[a[p].r].w)
            {
                zig(p);
                remove(a[p].r, val);
            }
            else
            {
                zag(p);
                remove(a[p].l, val);
            }
            update_size(p);
        }
        else
        {
            // 叶子节点，删除
            p = 0;
        }
        return;
    }
    if(val < a[p].val)
        remove(a[p].l, val);
    else
        remove(a[p].r, val);
    update_size(p);
}

void remove(int val)
{
    remove(root, val);
}

int get_successor(int val)
{
    // 后继: 大于 val 的最小的数
    int ans = 2; // a[2].val = INF
    int p = root;
    while(p != 0)
    {
        if(val == a[p].val)
        {
            if(a[p].r > 0)
            {
                p = a[p].r;
                while(a[p].l > 0)
                    p = a[p].l;
                ans = p;
            }
            break;
        }
        if(a[p].val > val && a[p].val < a[ans].val)
            ans = p;
        if(a[p].val < val)
            p = a[p].r;
        else
            p = a[p].l;
    }
    return a[ans].val;
}

int get_precursor(int val)
{
    // 前驱: 小于 val 的最大的数
    int ans = 1; // a[1].val = -INF
    int p = root;
    while(p != 0)
    {
        if(val == a[p].val)
        {
            if(a[p].l > 0)
            {
                p = a[p].l;
                while(a[p].r > 0)
                    p = a[p].r;
                ans = p;
            }
            break;
        }
        if(a[p].val < val && a[p].val > a[ans].val)
            ans = p;
        if(val < a[p].val)
            p = a[p].l;
        else
            p = a[p].r;
    }
    return a[ans].val;
}

int lessthan(int p, int val)
{
    if(p == 0)
        return 0;
    if(val == a[p].val)
        return a[a[p].l].size + 1;
    if(val < a[p].val)
        return lessthan(a[p].l, val);
    return lessthan(a[p].r, val) + a[a[p].l].size + a[p].cnt;
}

int lessthan(int val)
{
    // 小于 val 的个数, -INF 去掉
    return lessthan(root, val) - 1;
}

int get_value(int p, int rank)
{
    if(p == 0)
        return INF;
    if(a[a[p].l].size >= rank)
        return get_value(a[p].l, rank);
    if(a[a[p].l].size + a[p].cnt >= rank)
        return a[p].val;
    return get_value(a[p].r, rank - a[a[p].l].size - a[p].cnt);
}

int get_value(int rank)
{
    // 根据 rank 返回值, 要把 -INF 占的名额去掉
    return get_value(root, rank + 1);
}

int main()
{
    init();
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        int opt, x;
        cin >> opt >> x;
        switch(opt)
        {
        case 1:
            insert(x);
            break;
        case 2:
            remove(x);
            break;
        case 3:
            cout << lessthan(x) << endl;
            break;
        case 4:
            cout << get_value(x) << endl;
            break;
        case 5:
            cout << get_precursor(x) << endl;
            break;
        case 6:
            cout << get_successor(x) << endl;
            break;
        }
    }
}
