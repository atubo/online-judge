#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<int> curr;
        vector<vector<int>> res;
        dfs(candidates, 0, target, curr, res);
        sort(res.begin(), res.end());
        res.erase(unique(res.begin(), res.end()), res.end());
        return res;
    }

    void dfs(const vector<int>& A, int p, int t,
             vector<int>& curr, vector<vector<int>>& res) {
        if (t == 0) {
            res.push_back(curr);
            return;
        }
        if (p >= (int)A.size()) return;

        dfs(A, p+1, t, curr, res);
        if (t - A[p] >= 0) {
            curr.push_back(A[p]);
            dfs(A, p+1, t-A[p], curr, res);
            curr.pop_back();
        }
    }
};

int main() {
    Solution solution;
    int t;
    cin >> t;
    auto A = getVector();
    auto res = solution.combinationSum2(A, t);
    for (const auto& v: res) {
        printVector(v);
    }
    return 0;
}
