#include <iostream>
#include <fstream>
#include <cmath>
#include <unordered_map>
#include <cstdlib>
#include <vector>

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

    void show(ofstream& fout)
    {
        unordered_map<TreapNode*, int> x_mapping; // 节点指针 -> 行号(从0开始)
        int max_depth = 0;
        dfs1(root, x_mapping, 0, max_depth); // 得到最大深度 max_depth(从 0 开始的最大行号)，以及 x_mapping(节点 -> 行号)

        // 也就是 root 的 y 值范围为 [-pow(2, max_depth) + 1, pow(2, max_depth) - 1]
        // 如果当前节点 node 的范围为 [l, r]，则
        //     当前节点的 y 值为 (l + r) / 2
        //     node -> left 对应的范围为 [l, (l + r)/2 - 1]
        //     node -> right 对应的范围为 [(l + r)/2 + 1, r]
        // 两层节点之间增加 3 行，用于画连接线，因此 visual_board 总行数为 4 * max_depth + 1，行号 (0 ~ 4 * max_depth)
        // 列数 pow(2, max_depth + 1) - 1 (列号 0 ~ pow(2, max_depth + 1) - 1)
        vector<vector<string>> visual_board(4 * max_depth + 1, vector<string>(pow(2, max_depth + 1) - 1, "    "));
        dfs2(root, x_mapping, 0, pow(2, max_depth + 1) - 2, visual_board);
        for(int i = 0; i <= max_depth + 3 * max_depth; ++i)
        {
            for(int j = 0; j <= pow(2, max_depth + 1) - 2; ++j)
                fout << visual_board[i][j];
            fout << endl;
        }
        fout << endl;
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

    void dfs1(TreapNode* node, unordered_map<TreapNode*, int>& x_mapping, int depth, int& max_depth)
    {
        x_mapping[node] = depth;
        max_depth = max(max_depth, depth);
        if(node -> left)
            dfs1(node -> left, x_mapping, depth + 1, max_depth);
        if(node -> right)
            dfs1(node -> right, x_mapping, depth + 1, max_depth);
    }

    void dfs2(TreapNode* node, unordered_map<TreapNode*, int>& x_mapping, int l, int r, vector<vector<string>>& visual_board)
    {
        int y = (l + r) / 2;
        int x = x_mapping[node];
        visual_board[x * 4][y] = to_string(node -> val) + ',' + to_string(node -> size) + string(2 - len(node -> size), ' ') + string(2 - len(node -> val), ' ');
        if(!node -> left && !node -> right)
            return;
        if(node -> right)
        {
            visual_board[x * 4 + 1][y] = "|   ";
            visual_board[x * 4 + 2][y] = "----";
        }
        else
        {
            visual_board[x * 4 + 1][y] = "   |";
            visual_board[x * 4 + 2][y] = "----";
        }
        if(node -> left)
        {
            for(int j = (l + (l + r) / 2 - 1) / 2; j < y; ++j)
                visual_board[x * 4 + 2][j] = "----";
            visual_board[x * 4 + 3][(l + (l + r) / 2 - 1) / 2] = "|   ";
            dfs2(node -> left, x_mapping, l, (l + r) / 2 - 1, visual_board);
        }
        if(node -> right)
        {
            for(int j = y; j <= ((l + r) / 2 + 1 + r) / 2; ++j)
                visual_board[x * 4 + 2][j] = "----";
            visual_board[x * 4 + 3][((l + r) / 2 + 1 + r) / 2] = "   |";
            dfs2(node -> right, x_mapping, (l + r) / 2 + 1, r, visual_board);
        }
    }

    int len(int x)
    {
        int ans = 0;
        while(x > 0)
        {
            ++ans;
            x /= 10;
        }
        return ans;
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
                update_size(p);
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
        // val > p -> val
        int ans = p -> cnt;
        ans += lessthan(val, p -> right);
        if(p -> left)
            ans += p -> left -> size;
        return ans;
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
        // rank > s
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
    srand((unsigned)time(0));
    Treap treap = Treap();
    ofstream fout("out.txt");
    int j = 0;
    for(int i = 0; i < n; ++i)
    {
        int opt, x;
        cin >> opt >> x;
        switch(opt)
        {
        case 1:
            treap.insert(x);
            fout << i << ": insert(" << x << ")" << endl;
            treap.show(fout);
            break;
        case 2:
            treap.remove(x);
            fout << i << ": remove(" << x << ")" << endl;
            treap.show(fout);
            break;
        case 3:
            cout << treap.lessthan(x) + 1 << endl;
            fout << i << ": lessthan(" << x << ") + 1" << endl;
            fout << "output " << ++j << ": " << treap.lessthan(x) + 1 << endl;
            break;
        case 4:
            cout << treap.get_value(x) << endl;
            fout << i << ": get_value(" << x << ")" << endl;
            fout << "output " << ++j << ": " << treap.get_value(x) << endl;
            break;
        case 5:
            cout << treap.get_precursor(x) << endl;
            fout << i << ": get_precursor(" << x << ")" << endl;
            fout << "output " << ++j << ": " << treap.get_precursor(x) << endl;
            break;
        case 6:
            cout << treap.get_successor(x) << endl;
            fout << i << ": get_successor(" << x << ")" << endl;
            fout << "output " << ++j << ": " << treap.get_successor(x) << endl;
            break;
        }
    }
}
