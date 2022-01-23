#include <iostream>
#include <string>
#include <vector>

using namespace std;

int forward(int j, int x, const vector<string>& op, const vector<int>& t)
{
    int n = op.size();
    for(int i = 0; i < n; ++i)
    {
        if(op[i] == "AND")
            x = x & (t[i] >> j & 1);
        else if(op[i] == "OR")
            x = x | (t[i] >> j & 1);
        else
            x = x ^ (t[i] >> j & 1);
    }
    return x;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<string> op(n);
    vector<int> t(n);
    for(int i = 0; i < n; ++i)
        cin >> op[i] >> t[i];
    bool flag = false;
    int ans = 0;
    for(int j = 31; j >= 0; --j)
    {
        if(!flag)
        {
            if((m >> j & 1) == 0)
            {
                int x0 = forward(j, 0, op, t);
                ans = ans | (x0 << j);
            }
            else
            {
                int x0 = forward(j, 0, op, t);
                int x1 = forward(j, 1, op, t);
                if((x0 ^ x1) == 0 || x0 == 1)
                {
                    ans = ans | (x0 << j);
                    flag = true;
                }
                else
                    ans = ans | (x1 << j);
            }
        }
        else
        {
            int x0 = forward(j, 0, op, t);
            int x1 = forward(j, 1, op, t);
            if(x0 == 1)
                ans = ans | (x0 << j);
            else
                ans = ans | (x1 << j);
        }
    }
    cout << ans << endl;
}
