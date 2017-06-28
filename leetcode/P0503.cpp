// https://leetcode.com/problems/next-greater-element-ii/#/description
// 503. Next Greater Element II

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& A) {
        const int N = A.size();
        deque<int> dq;
        for (int i = N-2; i >= 0; i--) {
            int x = A[i];
            while (!dq.empty() && x >= dq.front()) dq.pop_front();
            dq.push_front(x);
        }
        vector<int> ret;
        for (int i = N-1; i >= 0; i--) {
            int x = A[i];
            while (!dq.empty() && x >= dq.front()) dq.pop_front();
            if (dq.empty()) ret.push_back(-1);
            else ret.push_back(dq.front());
            dq.push_front(x);
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};

int main() {
    Solution solution;
    auto A = getBracketedIntVector();
    auto ret = solution.nextGreaterElements(A);
    printVector(ret);
    return 0;
}
