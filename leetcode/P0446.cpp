// 446. Arithmetic Slices II - Subsequence
#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        const int N = A.size();
        vector<unordered_map<int64_t, int>> diff2cnt(N);
        int ret = 0;
        for (int i = 1; i < N; i++) {
            for (int j = 0; j < i; j++) {
                int64_t d = (int64_t)A[i] - A[j];
                int x = diff2cnt[j].count(d) == 0 ? 0 : diff2cnt[j][d];
                ret += x;
                diff2cnt[i][d] += 1 + x;
            }
        }
        return ret;
    }
};

int main() {
    Solution solution;
    auto A = getVector();
    cout << solution.numberOfArithmeticSlices(A) << endl;
    return 0;
}
