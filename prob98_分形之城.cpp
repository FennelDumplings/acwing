#include <iostream>
#include <cmath>

using namespace std;

using ll = long long;

struct Point
{
    ll x, y;
    Point(){}
    Point(ll x, ll y):x(x),y(y){}
};

double dist(const Point& p1, const Point& p2)
{
    double ans  = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
    return sqrt(ans);
}

Point solve(const ll N, const ll M)
{
    if(N == 1)
    {
        if(M == 0)
            return Point(0, 0);
        else if(M == 1)
            return Point(0, 1);
        else if(M == 2)
            return Point(1, 1);
        else
            return Point(1, 0);
    }
    ll len = pow(2, N - 1); // 一个角的边长
    ll sub_cnt = len * len; // 一个角的点个数
    Point p = solve(N - 1, M % sub_cnt);
    Point ans;
    if(M < sub_cnt)
    {
        ans.x = p.y;
        ans.y = p.x;
    }
    else if(M < sub_cnt * 2)
    {
        ans.x = p.x;
        ans.y = p.y;
        ans.y += len;
    }
    else if(M < sub_cnt * 3)
    {
        ans.x = p.x;
        ans.y = p.y;
        ans.x += len;
        ans.y += len;
    }
    else
    {
        ans.x = (len - 1 - p.y);
        ans.y = (len - 1 - p.x);
        ans.x += len;
    }
    return ans;
}

int main()
{
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        ll N, A, B;
        cin >> N >> A >> B;
        Point p1 = solve(N, A - 1);
        Point p2 = solve(N, B - 1);
        ll ans = round(10 * dist(p1, p2));
        cout << ans << endl;
    }
}
