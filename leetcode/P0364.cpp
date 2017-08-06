// https://leetcode.com/problems/nested-list-weight-sum-ii/description/
// 364. Nested List Weight Sum II

#include <bits/stdc++.h>
using namespace std;

 class NestedInteger {
   public:
     // Constructor initializes an empty nested list.
     NestedInteger();

     // Constructor initializes a single integer.
     NestedInteger(int value);

     // Return true if this NestedInteger holds a single integer, rather than a nested list.
     bool isInteger() const;

     // Return the single integer that this NestedInteger holds, if it holds a single integer
     // The result is undefined if this NestedInteger holds a nested list
     int getInteger() const;

     // Set this NestedInteger to hold a single integer.
     void setInteger(int value);

     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
     void add(const NestedInteger &ni);

     // Return the nested list that this NestedInteger holds, if it holds a nested list
     // The result is undefined if this NestedInteger holds a single integer
     const vector<NestedInteger> &getList() const;
 };

class Solution {
public:
    int depthSumInverse(vector<NestedInteger>& nestedList) {
        int dmax = calcDepth(nestedList);
        int ret = traverse(nestedList, 0, dmax);
        return ret;
    }

    int calcDepth(const vector<NestedInteger>& nl) {
        if (nl.empty()) return 0;
        int ret = 1;
        for (const auto& item: nl) {
            if (!item.isInteger()) {
                ret = max(ret, 1 + calcDepth(item.getList()));
            }
        }
        return ret;
    }

    int traverse(const vector<NestedInteger>& nl, int d, int dmax) {
        int ret = 0;
        for (const auto& item: nl) {
            if (item.isInteger()) {
                ret += item.getInteger() * (dmax - d);
            } else {
                ret += traverse(item.getList(), d+1, dmax);
            }
        }
        return ret;
    }
};

int main() {
    return 0;
}

