

#include <vector>
#include <iostream>

using namespace std;

struct Thing
{
    int kind;
    int v, w;
};


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

    vector<Thing> things;

    vector<int> dp(V + 1, 0);

    for(int i = 0; i < N; ++i)
    {
        int ss = s[i], vv = v[i], ww = w[i];
        if(ss < 0) things.push_back({-1, vv, ww});
        else if(ss == 0) things.push_back({0, vv, ww});
        else
        {
            for(int k = 1; k <= ss; k *= 2)
            {
                ss -= k;
                things.push_back({-1, vv * k, ww * k});
            }
            if(ss > 0)
                things.push_back({-1, vv * ss, ww * ss});
        }
    }

    for(auto thing: things)
    {
        if(thing.kind < 0)
        {
            for(int j = V; j >= thing.v; --j)
                dp[j] = max(dp[j], dp[j - thing.v] + thing.w);
        }
        else
        {
            for(int j = thing.v; j <= V; ++j)
                dp[j] = max(dp[j], dp[j - thing.v] + thing.w);
        }
    }

    cout << dp[V] << endl;
    return 0;
}
