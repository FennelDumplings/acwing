#include <sostream>
#include <vector>
#include <string>

using namespace std;
using ll = long long;

ll solve(const vector<string>sentences, int L, int P)
{
    //
}

int main()
{
    int T;
    cin >> T;
    vector<string> sentences;
    for(int i = 0; i < T; ++i)
    {
        int N, L, P;
        cin >> N >> L >> P;
        sentences.clear();
        for(int j = 0; j < N; ++j)
        {
            string s;
            getline(cin, s);
            sentences.push_back(s);
        }
        solve(sentences, L, P);
    }
}
