#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Plalindrome {
public:
    int longestPalindrome(string s) {
        int n = s.size();
        // prefix_hash[i] 为 s[0..i-1] 的哈希值
        prefix_hash = vector<ull>(n + 1, 0);
        // prefix_hash[i] 为 s[i..n-1] 的哈希值
        suffix_hash = vector<ull>(n + 1, 0);
        pp = vector<ull>(n + 1, 1);
        for(int i = 1; i <= n; ++i)
        {
            prefix_hash[i] = prefix_hash[i - 1] * p + (ull)s[i - 1];
            suffix_hash[n - i] = suffix_hash[n - i + 1] * p + (ull)s[n - i];
            pp[i] = pp[i - 1] * p;
        }

        // 奇数长度的回文串
        int left = 1, right = (n + 1) / 2;
        int start_odd = 0;
        while(left < right)
        {
            int mid = (left + right + 1) / 2;
            int k = check_odd(s, mid);
            if(k != -1)
            {
                start_odd = k;
                left = mid;
            }
            else
                right = mid - 1;
        }
        int len_odd = left * 2 - 1;

        // 偶数长度的回文串
        left = 0, right = (n + 1) / 2;
        int start_even = 0;
        while(left < right)
        {
            int mid = (left + right + 1) / 2;
            int k = check_even(s, mid);
            if(k != -1)
            {
                start_even = k;
                left = mid;
            }
            else
                right = mid - 1;
        }
        int len_even = left * 2;
        return max(len_even, len_odd);
    }

private:
    using ull = unsigned long long;
    const ull p = 201326611;
    vector<ull> prefix_hash, suffix_hash, pp;

    int check_odd(const string& s, int mid)
    {
        // 有没有半径为 mid 的奇数长回文子串
        int n = s.size();
        int r = mid;
        for(int k = r - 1; k <= n - r; ++k)
        {
            // s[k-r+1..k] 与 s[k..k+r-1]
            ull hash_left = prefix_hash[k + 1] - prefix_hash[k - r + 1] * pp[r];
            ull hash_right = suffix_hash[k] - suffix_hash[k + r] * pp[r];
            if(hash_left == hash_right)
                if(check_conflict(s, k, k, r))
                    return k - r + 1;
        }
        return -1;
    }

    int check_even(const string& s, int mid)
    {
        // 有没有半径为 mid 的偶数长回文子串
        int n = s.size();
        int r = mid;
        for(int k = r - 1; k <= n - r - 1; ++k)
        {
            // s[k-r+1..k] 与 s[k+1..k+r]
            ull hash_left = prefix_hash[k + 1] - prefix_hash[k - r + 1] * pp[r];
            ull hash_right = suffix_hash[k + 1] - suffix_hash[k + r + 1] * pp[r];
            if(hash_left == hash_right)
                if(check_conflict(s, k, k + 1, r))
                    return k - r + 1;
        }
        return -1;
    }

    bool check_conflict(const string& s, int l, int r, int len)
    {
        // s[l-len+1..l] 与 s[r..r+len-1] 是否对称
        for(int i = 0; i < len; ++i)
        {
            if(s[l - i] != s[r + i])
                return false;
        }
        return true;
    }
};

int main()
{
    Plalindrome plalindrome;
    string s;
    int i = 1;
    while(cin >> s && s != "END")
    {
        int len = plalindrome.longestPalindrome(s);
        cout << "Case " << i << ": " << len << endl;
        i++;
    }
}
