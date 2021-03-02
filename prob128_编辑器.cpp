

#include <vector>
#include <iostream>

using namespace std;

int main()
{
    int Q;
    cin >> Q;
    vector<int> st_l, st_r;
    vector<int> sums;
    vector<int> max_sums;
    for(int i = 0; i < Q; ++i)
    {
        char s;
        cin >> s;
        if(s == 'I')
        {
            int x;
            cin >> x;
            st_l.push_back(x);
            int cur = st_l.size() - 1;
            // sums[cur], max_sums[cur]
            if((int)sums.size() - 1 < cur)
            {
                sums.push_back(st_l[cur]);
                max_sums.push_back(sums[cur]);
            }
            sums[cur] = st_l[cur];
            if(cur > 0)
                sums[cur] += sums[cur - 1];
            max_sums[cur] = sums[cur];
            if(cur > 0)
                max_sums[cur] = max(sums[cur], max_sums[cur - 1]);
        }
        else if(s == 'D')
        {
            if(!st_l.empty())
                st_l.pop_back();
        }
        else if(s == 'L')
        {
            if(!st_l.empty())
            {
                st_r.push_back(st_l.back());
                st_l.pop_back();
            }
        }
        else if(s == 'R')
        {
            if(!st_r.empty())
            {
                st_l.push_back(st_r.back());
                st_r.pop_back();
                int cur = st_l.size() - 1;
                if((int)sums.size() - 1 < cur)
                {
                    sums.push_back(st_l[cur]);
                    max_sums.push_back(sums[cur]);
                }
                sums[cur] = st_l[cur];
                if(cur > 0)
                    sums[cur] += sums[cur - 1];
                max_sums[cur] = sums[cur];
                if(cur > 0)
                    max_sums[cur] = max(sums[cur], max_sums[cur - 1]);
            }
        }
        else
        {
            int k;
            cin >> k;
            cout << max_sums[k - 1] << endl;
        }
    }
}
