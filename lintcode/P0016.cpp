// https://www.lintcode.com/problem/permutations-ii/description?_from=ladder&&fromId=23
// 16. Permutations II 

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ret;
        ret.push_back(nums);
        vector<int> tmp(nums.size());
        while (nextPermutation(ret.back(), tmp)) {
               ret.push_back(tmp);
        }
        return ret;
    }

    bool nextPermutation(const vector<int> &a, vector<int> &t) {
        t = a;
        const int n = a.size();
        int p = n-2;
        while (p >= 0 && t[p] >= t[p+1]) p--;
        if (p < 0) return false;
        int q = n-1;
        while (t[q] <= t[p]) q--;
        swap(t[p], t[q]);
        sort(t.begin()+p+1, t.end());
        return true;
    }
};

int main() {
    Solution solution;
    auto A = getVector();
    auto ret = solution.permuteUnique(A);
    for (const auto &v: ret) {
        printVector(v);
    }
    return 0;
}
