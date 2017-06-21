#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int mySqrt(int x) {
        if (x <= 1) return x;
        int64_t lo = 1, hi = x;
        while (lo < hi - 1) {
            int64_t mid = (lo + hi) / 2;
            if (mid * mid <= x) lo = mid;
            else hi = mid;
        }
        return lo;
    }
};

int main() {
    Solution solution;
    int x;
    cin >> x;
    cout << solution.mySqrt(x) << endl;
    return 0;
}
