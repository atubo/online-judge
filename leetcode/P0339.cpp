// https://leetcode.com/problems/nested-list-weight-sum/description/
// 339. Nested List Weight Sum

#include <bits/stdc++.h>
using namespace std;

class NestedInteger {
public:
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
};

class Solution {
public:
    int depthSum(vector<NestedInteger>& nestedList) {
        return calc(nestedList, 1);
    }

    int calc(const vector<NestedInteger>& nestedList, int depth) {
        int ret = 0;
        for (const auto& item: nestedList) {
            if (item.isInteger()) {
                ret += item.getInteger() * depth;
            } else {
                ret += calc(item.getList(), depth+1);
            }
        }
        return ret;
    }
};

int main() {
    return 0;
}
