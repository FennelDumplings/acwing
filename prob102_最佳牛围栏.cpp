#include <iostream>
#include <vector>

using namespace std;

const double EPS = 1e-8;

int N, F;
vector<int> vec;

bool check(const double mid)
{
    // vec 中是否有长度不小于 F 的子段，平均值不小于 mid
    // 对于每个 i, 以 i 结尾的子段最短需要有 F 长度，对应子段 [i - F + 1, i]
    //     左端点 j 可以取 [0..i-F+1]
    //     对于特定 j 问: sum(vec[j] - mid) 是否不小于 0
    // 对于 i，我们可以实时维护一个前后前缀和 sums = sum(vec[0..i] + mid)
    // 问 sum(vec[0..j] + mid) ，其中 j 取 [0..i - F]，前缀和最小是多少, 记为 min_prev
    // 如果 sums - min_prev >= 0，则返回 true
    // 在维护 min_prev 的时候，我们还需要一个 prev_sums 表示 [0..i-F] 的前缀和
    double sums = 0;
    for(int i = 0; i < F; ++i)
        sums += vec[i] - mid;
    if(sums > -EPS)
        return true;
    // sums < 0
    double prev_sums = 0.0;
    double min_prev = prev_sums;
    for(int i = F; i < N; ++i)
    {
        prev_sums += vec[i - F] - mid;
        min_prev = min(min_prev, prev_sums);
        sums += vec[i] - mid;
        if(sums - min_prev > -EPS)
            return true;
    }
    return false;
}

int main()
{
    cin >> N >> F;
    vec.assign(N, 0);
    double left = 0.0;
    double right = 0.0;
    for(int i = 0; i < N; ++i)
    {
        cin >> vec[i];
        right = max(right, (double)vec[i]);
    }
    while(right - left > EPS)
    {
        double mid = (right + left) / 2;
        if(check(mid))
            left = mid;
        else
            right = mid;
    }
    /* 当我们用实数二分求一个值的时候，这个值会趋近于答案，比如答案是6500，而l等于6499.99999，r等于6500.00001，随着精度的提高，这两边会越来越趋近于6500，这就是实数二分的特点。
     * 因为它趋近于6500，所以我们知道其实答案就是6500，而答案6500向下取整就是6500，所以我们必须用r向下取整来得到答案（因为r比答案要大一点点）。
     * 同理，如果题目要求最终答案向上取整，就必须用l向上取整来得到最终答案（因为l比答案小一点点）。
     */
    double ans = right * 1000;
    cout << (int)ans << endl;
}
