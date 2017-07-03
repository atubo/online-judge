// https://leetcode.com/problems/sum-of-square-numbers/#/description
// 633. Sum of Square Numbers

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool judgeSquareSum(int c) {
        for (int64_t i = 0; i <= c; i++) {
            if (i*i > c) return false;
            int x = int(sqrt(c - i*i) + 0.5);
            if (x * x == c - i*i) return true;
        }
        return false;
    }
};

int main() {
    Solution solution;
    int n;
    cin >> n;
    cout << solution.judgeSquareSum(n) << endl;
    return 0;
}
