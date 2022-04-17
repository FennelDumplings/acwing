#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    int sum = 0;
    for(int i = 0; i < N; ++i)
    {
        cin >> A[i];
        sum += A[i];
    }
    int M = sum / N;
    int extra = 0;
    int ans = 0;
    for(int i = 0; i < N - 1; ++i)
    {
        if(A[i] > M + extra)
        {
            ++ans;
            A[i + 1] += A[i] - (M + extra);
            extra = 0;
        }
        else if(A[i] < M + extra)
        {
            ++ans;
            extra += M - A[i];
        }
        else
            extra = 0;
    }
    cout << ans << endl;
}
