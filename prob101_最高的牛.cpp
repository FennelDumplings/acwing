#include <iostream>
#include <unordered_set>

using namespace std;

const int MAX_N = 1e4 + 5;
int B[MAX_N];

int key(int i, int j)
{
    return i * MAX_N + j;
}

int main()
{
    int N, P, H, M;
    cin >> N >> P >> H >> M;
    // 初始时 [1..N] 均为 H
    B[1] = H;
    unordered_set<int> setting;
    for(int m = 0; m < M; ++m)
    {
        int a, b;
        cin >> a >> b;
        int i = min(a, b);
        int j = max(a, b);
        if(setting.count(key(i, j)) > 0)
            continue;
        // 区间 [i+1, j-1] 减 1
        B[i + 1] -= 1;
        B[j] += 1;
        setting.insert(key(i, j));
    }
    int pre_sum = 0;
    for(int i = 1; i <= N; ++i)
    {
        pre_sum += B[i];
        cout << pre_sum << endl;
    }
}
