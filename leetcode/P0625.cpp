// https://leetcode.com/problems/minimum-factorization/#/description
// 625. Minimum Factorization


#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int calc(const vector<int>& bv) {
        int64_t ret = 0;
        for (int i = bv.size()-1; i >= 0; i--) {
            ret = ret * 10 + bv[i];
        }
        return (ret > INT_MAX ? 0 : ret);
    }

    int smallestFactorization(int a) {
        if (a == 1) return 1;
        vector<int> bv;
        while (a > 1) {
            int d = 9;
            for (; d > 1; d--) {
                if (a % d == 0) break;
            }
            if (d == 1) return 0;
            bv.push_back(d);
            a /= d;
        }
        if (bv.size() > 9) return 0;
        return calc(bv);
    }
};

int main() {
    Solution solution;
    int a;
    cin >> a;
    cout << solution.smallestFactorization(a) << endl;
    return 0;
}
