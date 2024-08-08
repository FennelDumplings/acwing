#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool check(const string& s, int l1, int r1, int l2, int r2)
{
    for(int k = 0; k < r1 - l1 + 1; ++k)
        if(s[l1 + k] != s[l2 + k])
            return false;
    return true;
}

int main()
{
    string s;
    cin >> s;

    using ull = unsigned long long;
    const ull p = 1610612741;

    int n = s.size();
    vector<ull> prefix_hash(n + 1), pp(n + 1, 1);
    for(int i = 1; i <= n; ++i)
    {
        prefix_hash[i] = prefix_hash[i - 1] * p + (ull)s[i - 1];
        pp[i] = pp[i - 1] * p;
    }

    int m;
    cin >> m;
    for(int i = 0; i < m; ++i)
    {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        ull hash1 = prefix_hash[r1] - prefix_hash[l1 - 1] * pp[r1 - l1 + 1];
        ull hash2 = prefix_hash[r2] - prefix_hash[l2 - 1] * pp[r2 - l2 + 1];
        if(hash1 != hash2)
            cout << "No" << endl;
        else
        {
            if(check(s, l1, r1, l2, r2))
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }
    }
}
