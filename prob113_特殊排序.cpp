#include <algorithm>
#include <vector>

using namespace std;

// Forward declaration of compare API.
// bool compare(int a, int b);
// return bool means whether a is less than b.

class Solution {
public:
    vector<int> specialSort(int N) {
        vector<int> vec;
        vec.push_back(1);
        for(int i = 2; i <= N; ++i)
        {
            int left = 0, right = vec.size();
            while(left < right)
            {
                int mid = (left + right) / 2;
                int j = vec[mid];
                if(compare(i, j))
                {
                    // i < j
                    right = mid;
                }
                else
                {
                    // j < i
                    left = mid + 1;
                }
            }
            vec.insert(vec.begin() + left, i);
        }
        return vec;
    }
};
