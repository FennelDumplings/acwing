#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for(int i = 0; i < N; ++i)
        cin >> A[i];

    double ans_and = 0; // 记录 and 和的期望
    double ans_or = 0; // 记录 or 和的期望
    double ans_xor = 0; // 记录 xor 和的期望

    for(int k = 0; k < 31; ++k)
    {
        // 枚举到第 k 位
        for(int i = 0; i < N; ++i)
        {
            // l = r 的部分
            if((A[i] >> k) & 1)
            {
                ans_and += (double)pow(2, k) / N / N;
                ans_or += (double)pow(2, k) / N / N;
                ans_xor += (double)pow(2, k) / N / N;
            }
        }
        // c[0] 对应算法中的 c1
        // c[1] 对应算法中的 c2
        vector<int> c(2, 0);
        vector<int> last{-1, -1};
        for(int r = 0; r < N; ++r)
        {
            // l < r 的部分
            if((A[r] >> k) & 1)
            {
                ans_and += (double)pow(2, k) * ((r - 1) - (last[0] + 1) + 1) * 2 / N / N;
                ans_or += (double)pow(2, k) * r * 2 / N / N;
                ans_xor += (double)pow(2, k) * c[0] * 2 / N / N;
                last[1] = r;
                c[0] += 1;
                swap(c[0], c[1]);
            }
            else
            {
                ans_or += (double)pow(2, k) * (last[1] + 1) * 2 / N / N;
                ans_xor += (double)pow(2, k) * c[1] * 2 / N / N;
                last[0] = r;
                c[0] += 1;
            }
        }
    }
    cout << std::fixed << std::setprecision(3);
    cout << ans_xor << " " << ans_and << " " << ans_or << endl;
}
