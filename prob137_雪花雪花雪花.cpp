#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;
const int P = 99991;

int H(const vector<int>& a)
{
    int ans1 = 0;
    int ans2 = 1;
    for(int j = 0; j < 6; ++j)
    {
        ans1 = ((ll)ans1 + a[j]) % P;
        ans2 = ((ll)ans2 * a[j]) % P;
    }
    return ((ll)ans1 + ans2) % P;
}

int get_min_representation(const vector<int>& s)
{
    int N = s.size();
    int i = 0, j = 1;
    while(i < N && j < N)
    {
        int k = 0;
        while(k < N && s[(i + k) % N] == s[(j + k) % N])
            k++;
        if(k == N)
            break;
        if(s[(i + k) % N] < s[(j + k) % N])
        {
            j += k + 1;
            if(i == j)
                j++;
        }
        else
        {
            i += k + 1;
            if(i == j)
                i++;
        }
    }
    return min(i, j);
}

bool equal(const vector<int>& a1, const vector<int>& a2, int min1, int min2)
{
    for(int k = 0; k < 6; ++k)
    {
        if(a1[(min1 + k) % 6] != a2[(min2 + k) % 6])
            return false;
    }
    return true;
}

bool check(vector<int>& a1, const vector<int>& a2)
{
    // 最小表示法比较 a1 与 a2 是否同构
    reverse(a1.begin(), a1.end());
    int min1_reversed = get_min_representation(a1);
    int min2 = get_min_representation(a2);
    if(equal(a1, a2, min1_reversed, min2))
        return true;
    reverse(a1.begin(), a1.end());
    int min1 = get_min_representation(a1);
    if(equal(a1, a2, min1, min2))
        return true;
    return false;
}

int main()
{
    int N;
    cin >> N;
    vector<vector<int>> a(N, vector<int>(6));
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < 6; ++j)
            cin >> a[i][j];
    }
    unordered_map<int, vector<vector<int>>> mapping;
    for(int i = 0; i < N; ++i)
    {
        int h = H(a[i]);
        if(mapping.count(h) > 0)
        {
            for(vector<int>& item: mapping[h])
            {
                if(check(item, a[i]))
                {
                    cout << "Twin snowflakes found." << endl;
                    return 0;
                }
            }
        }
        mapping[h].push_back(a[i]);
    }
    cout << "No two snowflakes are alike." << endl;
}
