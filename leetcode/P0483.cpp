// https://leetcode.com/problems/smallest-good-base/#/description
// 483. Smallest Good Base
#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int64_t f(int64_t x, int m) {
        int64_t t = 1;
        int64_t ret = 1;
        for (int i = 1; i <= m; i++) {
            t *= x;
            ret += t;
        }
        return ret;
    }

    int64_t search(int64_t n, int m) {
        if (f(1, m) >= n) return -1;
        int64_t lo = 1, hi = pow((long double)n, (long double)1.0/m) + 1;
        while (lo < hi-1) {
            int64_t mid = (lo + hi) / 2;
           if (f(mid, m) < n) lo = mid;
           else hi = mid;
        }
        return (f(hi, m) == n ? hi : -1);
    }

    string smallestGoodBase(string ns) {
        int64_t n = stoll(ns);
        int64_t res;
        for (int m = 1; m < 64; m++) {
            int64_t x = search(n, m);
            if (x >= 0) res = x;
        }
        return to_string(res);
    }
};

int main() {
    Solution solution;
    string s;
    cin >> s;
    cout << solution.smallestGoodBase(s) << endl;
    return 0;
}
