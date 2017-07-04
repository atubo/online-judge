// https://leetcode.com/problems/4sum-ii/#/description
// 454. 4Sum II

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    using Map = unordered_map<int, int>;
public:
    int fourSumCount(vector<int>& A, vector<int>& B,
                     vector<int>& C, vector<int>& D) {
        auto m1 = build(A, B);
        auto m2 = build(C, D);
        return calc(m1, m2);
    }

    Map build(const vector<int>& A, const vector<int>& B) {
        Map m;
        for (int x: A) {
            for (int y: B) {
                m[x+y]++;
            }
        }
        return m;
    }

    int calc(const Map& m1, const Map& m2) {
        int ret = 0;
        for (const auto& pr: m1) {
            int x = pr.first, c = pr.second;
            if (m2.count(-x) > 0) {
                ret += c * m2.at(-x);
            }
        }
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
