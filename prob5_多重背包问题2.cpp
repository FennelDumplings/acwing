
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


    for(int i = 0; i < N; ++i)
    {
        int ss = s[i];
        ss -= 1;
        for(int k = 2; k <= ss; k *= 2)
        {
            ss -= k;
            v.push_back(v[i] * k);
            w.push_back(w[i] * k);
        }
        if(ss > 0)
        {
            v.push_back(v[i] * ss);
            w.push_back(w[i] * ss);
        }
    }



    vector<int> dp(V + 1, 0);

    N = v.size();
    for(int i = 1; i <= N; ++i)
        for(int j = V; j >= v[i - 1]; --j)
            dp[j] = max(dp[j], dp[j - v[i - 1]] + w[i - 1]);


    cout << dp[V] << endl;
    return 0;
}
