#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

int f[100050];
int main()
{
    int N;
    cin >> N;
    vector<int> A(N + 1);
    for(int i = 1; i <= N; ++i)
        cin >> A[i];

    double ans_and = 0; // 记录 and 和的期望
    double ans_or = 0; // 记录 or 和的期望
    double ans_xor = 0; // 记录 xor 和的期望

    for(int k = 0; k < 31; ++k)
    {
        // 枚举到第 k 位
        for(int i = 1; i <= N; ++i)
        {
            // l = r 的部分
            if((A[i] >> k) & 1)
            {
                ans_and += (double)pow(2, k) / (N * N);
                ans_or += (double)pow(2, k) / (N * N);
                ans_xor += (double)pow(2, k) / (N * N);
            }
        }
        vector<int> last{0, 0};
        for(int i=1;i<=N;i++){
            if((A[i] >> k) & 1){
                ans_and+=(double)((i-1)-(last[0]+1)+1)/N/N*(1<<k)*2.0;
                ans_or+=(double)(i-1)/N/N*(1<<k)*2.0;
                f[i]=i-1-f[i-1]-(A[i-1] >> k & 1);
                last[1] = i;
            }
            else {
                ans_or+=(double)last[1]/N/N*(1<<k)*2.0;
                f[i]=f[i-1]+(A[i-1] >> k & 1);
                last[0] = i;
            }
            ans_xor+=f[i]*2.0/N/N*(1<<k);
        }//puts("");
    }
    printf("%.3lf %.3lf %.3lf",ans_xor,ans_and,ans_or);
}
