#include <sostream>
#include <vector>
#include <string>

using namespace std;



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
