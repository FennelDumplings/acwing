#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 区间查询 > x 的数
struct MTNode
{
    int start, end;
    vector<int> data;
    MTNode *left, *right;
    MTNode(int s, int e, const vector<int>& nums, MTNode* l=nullptr, MTNode* r=nullptr)
        :start(s),end(e),data(nums),left(l),right(r) {}
    ~MTNode(){}
};

class MergeTree
{
public:
    MergeTree()
    {
        root = nullptr;
    }

    ~MergeTree()
    {
        if(root)
        {
            delete_sub_tree(root);
        }
    }

    void delete_sub_tree(MTNode* node)
    {
        if(node -> left)
            delete_sub_tree(node -> left);
        if(node -> right)
            delete_sub_tree(node -> right);
        delete node;
        node = nullptr;
    }

    void build(int start, int end, const vector<int>& nums)
    {
        root = _build(start, end, nums);
    }

    int query(int i, int j, int k)
    {
        if(i > j) return 0;
        int result = 0;
        _query(root, i, j, k, result);
        return result;
    }

    int get(int i)
    {
        return (root -> data)[i];
    }

private:
    MTNode *root;

    void _query(MTNode* root, int i, int j, int k, int& result)
    {
        if(root -> start == i && root -> end == j)
        {
            auto pos = upper_bound((root -> data).begin(), (root -> data).end(), k);
            result += (root -> data).end() - pos;
            return;
        }
        int mid = root -> start + (root -> end - root -> start) / 2;
        if(j <= mid)
        {
            _query(root -> left, i, j, k, result);
            return;
        }
        if(i > mid)
        {
            _query(root -> right, i, j, k, result);
            return;
        }
        _query(root -> left, i, mid, k, result);
        _query(root -> right, mid + 1, j, k, result);
    }

    MTNode* _build(int start, int end, const vector<int>& nums)
    {
        if(start == end)
        {
            return new MTNode(start, end, vector<int>({nums[start]}));
        }
        int mid = start + (end - start) / 2;
        MTNode *left = _build(start, mid, nums);
        MTNode *right = _build(mid + 1, end, nums);
        vector<int> merged((left -> data).size() + (right -> data).size());
        merge((left -> data).begin(), (left -> data).end(), (right -> data).begin(), (right -> data).end(), merged.begin());
        MTNode *cur = new MTNode(start, end, merged, left, right);
        return cur;
    }
};

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> nums(N);
    for(int i = 0; i < N; ++i)
        cin >> nums[i];

    MergeTree mergetree;
    mergetree.build(0, N - 1, nums);

    for(int i = 0; i < M; ++i)
    {
        int left = mergetree.get(0), right = mergetree.get(N - 1);
        int l, r, k;
        cin >> l >> r >> k;
        l--;
        r--;
        bool flag = false;
        while(left < right)
        {
            int mid = left + (right - left) / 2;
            int cnt = mergetree.query(l, r, mid); // > mid 的元素个数
            if(cnt == k - 1)
            {
                flag = true;
                cout << mid << endl;
                break;
            }
            else if(cnt > k - 1)
                left = mid + 1;
            else
                right = mid;
        }
        if(flag)
            cout << left << endl;
    }
}
