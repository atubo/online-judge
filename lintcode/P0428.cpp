// https://www.lintcode.com/problem/powx-n/description?_from=ladder&&fromId=23
// 428. Pow(x, n)

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    double myPow(double x, int n) {
        double ret = fastPow(x, abs(int64_t(n)));
        if (n < 0) ret = 1.0/ret;
        return ret;
    }

    double fastPow(double x, int64_t n) {
        double ret = 1.0;
        while (n) {
            if (n & 1) ret *= x;
            x *= x;
            n >>= 1;
        }
        return ret;
    }
};

int main() {
    Solution solution;
    double x;
    int n;
    cin >> x >> n;
    cout << solution.myPow(x, n) << endl;
    return 0;
}
