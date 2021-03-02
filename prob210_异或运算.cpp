#include <vector>
#include <iostream>

using namespace std;

using ULL = unsigned long long;

int main()
{
    int T;
    cin >> T;
    for(int C = 1; C <= T; ++C)
    {
        int N;
        cin >> N;
        vector<ULL> a(N + 1);
        for(int i = 1; i <= N; ++i)
            cin >> a[i];

        vector<ULL> b; // 异或空间的基

        int dim = 0;
        bool zero = false; // 标记简化阶梯型矩阵是否有全零行
        for(int i = 1; i <= N; ++i) // 处理第 i 行
        {
            // 选行，选 dim + 1 位为 1 的
            // 状态压缩的情况下，可以直接选数值最大的
            for(int j = i + 1; j <= N; ++j)
            {
                if(a[j] > a[i])
                    swap(a[i], a[j]);
            }
            if(a[i] == 0) // 此后都是全零行了
            {
                zero = true;
                break;
            }
            ++dim;
            // 消
            for(int k = 63; k >= 0; --k)
                if(a[i] >> k & 1)
                {
                    for(int j = 1; j <= N; ++j)
                    {
                        if(i == j) continue;
                        if(a[j] >> k & 1)
                            a[j] ^= a[i];
                    }
                    break;
                }
        }
        // 阶梯型矩阵 a 的前 dim 行是基 a[1 ~ dim]

        // 处理询问
        int Q;
        cin >> Q;
        cout << "Case #" << C << ":" << endl;
        while(Q--)
        {
            ULL k;
            cin >> k;
            if(zero) --k;
            ULL ans = 0;
            if(k >= (ULL)1 << dim)
                cout << "-1" << endl;
            else
            {
                for(int i = dim - 1; i >= 0; --i)
                {
                    if(k >> i & 1)
                        ans ^= a[dim - i];
                }
                cout << ans << endl;
            }
        }
    }
}
