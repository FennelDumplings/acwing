

#include <vector>
#include <iostream>

using namespace std;

int main()
{
    int N;
    int V;
    cin >> N >> V;

    vector<vector<int> > v(N, vector<int>());
    vector<vector<int> > w(N, vector<int>());

    for(int i = 0; i < N; ++i)
    {
        int s;
        cin >> s;
        for(int j = 0; j < s; ++j)
        {
            int vv, ww;
            cin >> vv >> ww;
            v[i].push_back(vv);
            w[i].push_back(ww);
        }
    }

    vector<int> dp(V + 1, 0);
    for(int i = 1; i <= N; ++i)
    {
        int s = v[i - 1].size();
        for(int j = V; j >= 0; --j)
            for(int k = 0; k < s; ++k)
                if(j >= v[i - 1][k])
                    dp[j] = max(dp[j], dp[j - v[i - 1][k]] + w[i - 1][k]);
    }

    cout << dp[V] << endl;
    return 0;
}
