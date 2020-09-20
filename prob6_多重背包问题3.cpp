
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    int N;
    int V;
    cin >> N >> V;
    vector<int> v(N, 0);
    vector<int> w(N, 0);
    vector<int> s(N, 0);
    for(int i = 0; i < N; ++i)
        cin >> v[i] >> w[i] >> s[i];

    vector<int> dp(V + 1, 0);
    vector<int> dp_pre(V + 1, 0);
    vector<int> q(V + 1, 0);

    for(int i = 1; i <= N; ++i)
    {
        dp_pre.clear();
        dp_pre = dp;
        int vv = v[i - 1];
        int ss = s[i - 1];
        int ww = w[i - 1];
        for(int j = 0; j < vv; ++j)
        {
            int head = 0, tail = -1;
            for(int k = j; k <= V; k += vv) // 枚举余数
            {
                if(head <= tail && k - ss * vv > q[head])
                    ++head;

                while(head <= tail && dp_pre[q[tail]] - (q[tail] - j) / vv * ww <= dp_pre[k] - (k - j) / vv * ww)
                    --tail;

                if(head <= tail)
                    dp[k] = max(dp[k], dp_pre[q[head]] + (k - q[head]) / vv * ww);

                q[++tail] = k;
            }
        }
    }


    cout << dp[V] << endl;
    return 0;
}
