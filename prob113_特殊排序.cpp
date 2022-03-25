#include <algorithm>
#include <vector>

using namespace std;

// Forward declaration of compare API.
// bool compare(int a, int b);
// return bool means whether a is less than b.

class Solution {
public:
    vector<int> specialSort(int N) {
        vector<int> vec(N);
        for(int i = 1; i <= N; ++i)
            vec[i - 1] = i;
        stable_sort(vec.begin(), vec.end(), compare);
        return vec;
    }
};
