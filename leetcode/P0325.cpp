// https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/description/
// 325. Maximum Size Subarray Sum Equals k

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSubArrayLen(vector<int>& A, int k) {
        unordered_map<int, int> pos;
        pos[0] = -1;
        int ps = 0;
        int ret = 0;
        for (int i = 0; i < (int)A.size(); i++) {
            ps += A[i];
            if (pos.count(ps - k) > 0) {
                ret = max(ret, i - pos.at(ps-k));
            }
            if (pos.count(ps) == 0) {
                pos[ps] = i;
            }
        }
        return ret;
    }
};

int main() {
    return 0;
}
