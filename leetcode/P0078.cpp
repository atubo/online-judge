// 78. Subsets

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ret;
        ret.push_back(vector<int>());
        dfs(nums, 0, ret);
        return ret;
    }

    void dfs(const vector<int>& A, int p, vector<vector<int>>& ret) {
        if (p == (int)A.size()) return;
        int N = ret.size();
        for (int i = 0; i < N; i++) {
            vector<int> v = ret[i];
            v.push_back(A[p]);
            ret.push_back(v);
        }
        dfs(A, p+1, ret);
    }
};

int main() {
    Solution solution;
    auto A = getVector();
    auto ret = solution.subsets(A);
    for (auto v: ret) {
        printVector(v);
    }
    return 0;
}
