#include <iostream>
#include <cstdlib>

using namespace std;

const int INF = 1e9;

struct TreapNode
{
    int val;
    int size;
    int cnt;
    int w;
    TreapNode *left, *right;
    TreapNode():size(1),cnt(1),w(rand()),left(nullptr),right(nullptr){}
};

class Treap
{
public:
    Treap():root(nullptr){}
    ~Treap()
    {
        delete_sub_tree(root);
    }

    void insert(int val)
    {
        insert(val, root);
    }

    void remove(int val)
    {
        remove(val, root);
    }

    int lessthan(int val)
    {
        return lessthan(val, root);
    }

    int get_value(int rank)
    {
        return get_value(rank, root);
    }

    int get_successor(int val)
    {
        // 大于 val 的最小的
        TreapNode *ans = nullptr;
        TreapNode *p = root;
        while(p)
        {
            if(val == p -> val)
            {
                if(p -> right)
                {
                    p = p -> right;
                    while(p -> left)
                        p = p -> left;
                    ans = p;
                }
                break;
            }
            if(p -> val > val && (!ans || p -> val < ans -> val))
                ans = p;
            if(val > p -> val)
                p = p -> right;
            else
                p = p -> left;
        }
        if(!ans)
            return INF;
        return ans -> val;
    }

    int get_precursor(int val)
    {
        // 小于 val 的最大的
        TreapNode *ans = nullptr;
        TreapNode *p = root;
        while(p)
        {
            if(val == p -> val)
            {
                if(p -> left)
                {
                    p = p -> left;
                    while(p -> right)
                        p = p -> right;
                    ans = p;
                }
                break;
            }
            if(p -> val < val && (!ans || p -> val > ans -> val))
                ans = p;
            if(val < p -> val)
                p = p -> left;
            else
                p = p -> right;
        }
        if(!ans)
            return -INF;
        return ans -> val;
    }

private:
    TreapNode *root;

    TreapNode* find(int val, TreapNode* p)
    {
        // 大于等于 val 的最小值
        if(!p)
            return nullptr;
        if(p -> val == val)
            return p;
        if(p -> val > val)
            return find(val, p -> left);
        return find(val, p -> right);
    }

    void update_size(TreapNode* p)
    {
        // 用当前节点的 cnt 和左右子树的 size 更新当前子树的 size
        p -> size = p -> cnt;
        if(p -> left)
            p -> size += p -> left -> size;
        if(p -> right)
            p -> size += p -> right -> size;
    }

    void zig(TreapNode*& p)
    {
        // 右旋
        TreapNode *tmp = p -> left;
        p -> left = tmp -> right;
        tmp -> right = p;
        p = tmp;
        update_size(p -> right);
        update_size(p);
    }

    void zag(TreapNode*& p)
    {
        // 左旋
        TreapNode *tmp = p -> right;
        p -> right = tmp -> left;
        tmp -> left = p;
        p = tmp;
        update_size(p -> left);
        update_size(p);

    }

    void insert(int val, TreapNode*& p)
    {
        if(p == nullptr)
        {
            p = new TreapNode();
            p -> val = val;
            return;
        }
        if(p -> val == val)
            ++(p -> cnt);
        else if(p -> val < val)
        {
            insert(val, p -> right);
            if(p -> w < p -> right -> w)
                zag(p);
        }
        else
        {
            insert(val, p -> left);
            if(p -> w < p -> left -> w)
                zig(p);
        }
        update_size(p);
    }

    void remove(int val, TreapNode*& p)
    {
        if(p == nullptr)
            return;
        if(val == p -> val)
        {
            if(p -> cnt > 1)
            {
                --(p -> cnt);
                update_size(p);
                return;
            }
            if(p -> left || p -> right)
            {
                // 不是叶节点，向下旋转
                if(!p -> right || (p -> left && p -> left -> w > p -> right -> w))
                {
                    zig(p);
                    remove(val, p -> right);
                }
                else
                {
                    zag(p);
                    remove(val, p -> left);
                }
            }
            else
            {
                // 叶节点
                delete p;
                p = nullptr;
            }
            return;
        }
        if(val < p -> val)
            remove(val, p -> left);
        else
            remove(val, p -> right);
        update_size(p);

    }

    int lessthan(int val, TreapNode* p)
    {
        if(p == nullptr)
            return 0;
        if(val == p -> val)
        {
            int ans = 0;
            if(p -> left)
                ans += p -> left -> size;
            return ans;
        }
        if(val < p -> val)
            return lessthan(val, p -> left);
        if(val > p -> val)
        {
            int ans = p -> cnt;
            ans += lessthan(val, p -> right);
            if(p -> left)
                ans += p -> left -> size;
            return ans;
        }
    }

    int get_value(int rank, TreapNode* p)
    {
        if(p == nullptr)
            return INF;
        if(p -> left && p -> left -> size >= rank)
            return get_value(rank, p -> left);
        int s = p -> cnt;
        if(p -> left)
            s += p -> left -> size;
        if(s >= rank)
            return p -> val;
        return get_value(rank - s, p -> right);
    }

    void delete_sub_tree(TreapNode* p)
    {
        if(p -> left)
            delete_sub_tree(p -> left);
        if(p -> right)
            delete_sub_tree(p -> right);
        delete p;
        p = nullptr;
    }
};

int main()
{
    int n;
    cin >> n;
    Treap treap = Treap();
    for(int i = 0; i < n; ++i)
    {
        int opt, x;
        cin >> opt >> x;
        switch(opt)
        {
        case 1:
            treap.insert(x);
            break;
        case 2:
            treap.remove(x);
            break;
        case 3:
            cout << treap.lessthan(x) + 1 << endl;
            break;
        case 4:
            cout << treap.get_value(x) << endl;
            break;
        case 5:
            cout << treap.get_precursor(x) << endl;
            break;
        case 6:
            cout << treap.get_successor(x) << endl;
            break;
        }
    }
}
