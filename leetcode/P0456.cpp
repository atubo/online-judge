// https://leetcode.com/problems/132-pattern/#/description
// 456. 132 Pattern

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    using PII = pair<int, int>;
public:
    bool find132pattern(vector<int>& A) {
        deque<PII> dq;
        int lo = INT_MAX;
        for (int x: A) {
            while (!dq.empty() && dq.front().first <= x) dq.pop_front();
            if (!dq.empty() && dq.front().second < x) return true;
            dq.push_front(make_pair(x, lo));
            lo = min(lo, x);
        }
        return false;
    }
};

int main() {
    Solution solution;
    auto A = getBracketedIntVector();
    cout << solution.find132pattern(A) << endl;
    return 0;
}
