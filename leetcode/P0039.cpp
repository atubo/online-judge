#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <strings.h>
#include <algorithm>
#include <cassert>
#include <climits>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> curr;
        vector<vector<int>> res;
        dfs(candidates, 0, target, curr, res);
        return res;
    }

    void dfs(const vector<int>& A, int i, int t,
             vector<int>& curr, vector<vector<int>>& res) {
        if (t == 0) {
            res.push_back(curr);
            return;
        }
        if (i >= (int)A.size()) return;

        dfs(A, i+1, t, curr, res);
        while (t - A[i] >= 0) {
            curr.push_back(A[i]);
            t -= A[i];
            dfs(A, i+1, t, curr, res);
        }
        while (!curr.empty() && curr.back() == A[i]) curr.pop_back();
    }
};

int main() {
    Solution solution;
    int t;
    cin >> t;
    vector<int> A = getVector();
    vector<vector<int>> res = solution.combinationSum(A, t);
    for (const auto& v: res) {
        printVector(v);
    }
    return 0;
}
