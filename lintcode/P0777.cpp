// https://www.lintcode.com/problem/valid-perfect-square/description
// 777. Valid Perfect Square

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPerfectSquare(int num) {
        if (num < 0) return false;
        if (num < 2) return true;
        int lo = 1, hi = num;
        while (lo < hi - 1) {
            int mid = (lo + hi) / 2;
            if (1LL * mid * mid <= num) lo = mid;
            else hi = mid;
        }
        return 1LL * lo * lo == num;
    }
};

int main() {
    Solution solution;
    int n;
    cin >> n;
    cout << solution.isPerfectSquare(n) << endl;
    return 0;
}
