// https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/
// 862. Shortest Subarray with Sum at Least K

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int shortestSubarray(vector<int>& A, int K) {
        int ret = INT_MAX;
        vector<pair<int, int>> q;
        q.push_back({0, -1});
        int x = 0;
        for (int i = 0; i < (int)A.size(); i++) {
            x += A[i];
            auto it = upper_bound(q.begin(), q.end(), make_pair(x-K, INT_MAX));
            if (it != q.begin()) {
                it--;
                ret = min(ret, i-it->second);
            }
            while (!q.empty() && q.back().first >= x) q.pop_back();
            q.push_back({x, i});
        }
        return (ret == INT_MAX ? -1 : ret);
    }
};

int main() {
    vector<int> A{84, -37, 32, 40, 95};
    Solution solution;
    cout << solution.shortestSubarray(A, 167) << endl;
    return 0;
}
