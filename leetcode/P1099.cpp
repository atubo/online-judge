// https://leetcode.com/problems/two-sum-less-than-k/
// 1099. Two Sum Less Than K

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int twoSumLessThanK(vector<int> &A, int K) {
        sort(A.begin(), A.end());
        int ans = -1;
        for (int i = 0; i < (int)A.size(); i++) {
            int x = A[i];
            if (2*x >= K) break;
            auto it = lower_bound(A.begin(), A.end(), K-x);
            if (it == A.begin()) break;
            --it;
            if (it-A.begin() <= i) break;
            ans = max(ans, *it+x);
        }
        return ans;
    }
};

int main() {
    Solution solution;
    return 0;
}
