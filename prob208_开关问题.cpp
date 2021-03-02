#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int K;
    cin >> K;
    while(K--)
    {
        int N;
        cin >> N;

        // 状态压缩后的增广矩阵
        vector<int> a(N + 1);
        for(int i = 1; i <= N; ++i)
            cin >> a[i];
        for(int i = 1; i <= N; ++i)
        {
            int x;
            cin >> x;
            a[i] ^= x;
        }

        int I, J;
        do{
            cin >> I;
            cin >> J;
            a[J] |= 1 << I; // a[J][I] = 1
        }while(I != 0 && J != 0);
        for(int i = 1; i <= N; ++i)
            a[i] |= 1 << i; // a[i][i] = 1

        // 高斯消元
        int ans = 1;
        for(int i = 1; i <= N; ++i)
        {
            // 第 i 个元 x[i]
            for(int j = i + 1; j <= N; ++j)
            {
                if(a[j] > a[i])
                    swap(a[i], a[j]);
            }

            // 判断系数是否全都为 0 : a[i] <= 1
            if(a[i] == 1) // 判断是否出现 0 = 1 的方程
            {
                // 出现 0 = 1 方程，无解
                ans = 0;
                break;
            }
            if(a[i] == 0)
            {
                // 出现 0 = 0 的方程
                ans = 1 << (N - i + 1);
                break;
            }

            // a[i] 最高位的 1 为主元，消去其它方程该位的系数
            for(int k = N; k >= 1; --k)
            {
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
        }
        if(ans == 0)
            cout << "Oh,it's impossible~!!" << endl;
        else
            cout << ans << endl;
    }
}
