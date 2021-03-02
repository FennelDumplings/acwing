
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
    vector<int> deq(V + 1);

    for(int i = 1; i <= N; ++i)
    {
        int vv = v[i - 1];
        int ss = s[i - 1];
        int ww = w[i - 1];
        for(int q = 0; q < vv; ++q) // 枚举余数
        {
            // 建立单调队列
            int l = 0, r = -1;
            // 将初始候选集合(p = maxp 时)插入队列
            int maxp = (V - q) / vv;
            for(int k = maxp - 1; k >= max(maxp - ss, 0); --k)
            {
                while(l <= r && dp[q + deq[r] * vv] - deq[r] * ww <= dp[q + k * vv] - k * ww)
                    --r;
                deq[++r] = k;
            }
            // 倒序枚举状态
            for(int p = maxp; p >= 0; --p)
            {
                // 排除过时决策
                while(l <= r && deq[l] > p - 1)
                    ++l;

                // 取队头进行状态转移
                if(l <= r)
                    dp[q + p * vv] = max(dp[q + p * vv], dp[q + deq[l] * vv] - deq[l] * ww + p * ww);

                // 插入新决策，同时维护单调性
                if(p - ss - 1 >= 0)
                {
                    while(l <= r && dp[q + deq[r] * vv] - deq[r] * ww <= dp[q + (p - ss - 1) * vv] - (p - ss - 1) * ww)
                        --r;
                    deq[++r] = p - ss - 1;
                }
            }
        }
    }

    cout << dp[V] << endl;
    return 0;
}
