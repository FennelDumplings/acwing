
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for(int i = 0; i < N; ++i)
        cin >> A[i];
    A.insert(A.end(), A.begin(), A.end());
    int ans = 0;
    deque<int> deq;
    deq.push_back(0);
    for(int j = 1; j < N * 2; ++j)
    {
        // 对每个 j 找 j - N /2 <= i <= j - 1 中 A[i] - i 的最大值
        // 此时 deq 中是 [j - N / 2, j - 1]

        // 更新答案
        ans = max(ans, A[j] + j + A[deq.front()] - deq.front());

        // 插入 j 保持单调性
        while(!deq.empty() && A[deq.back()] - deq.back() <= A[j] - j)
            deq.pop_back();
        deq.push_back(j);

        // 弹出 <= j - N / 2 的保持区间合法性
        if(!deq.empty() && deq.front() <= j - N / 2)
            deq.pop_front();
    }
    cout << ans << endl;
}
