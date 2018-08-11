// https://www.lintcode.com/problem/sum-of-square-numbers/description
// 697. Sum of Square Numbers

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool checkSumOfSquareNumbers(int num) {
        for (int64_t x = 0; x * x <= num; x++) {
            int y = num - x*x;
            int z = sqrt(y) + 0.5;
            if (z*z == y) return true;
        }
        return false;
    }
};

int main() {
    Solution solution;
    int n;
    cin >> n;
    cout << solution.checkSumOfSquareNumbers(n) << endl;
    return 0;
}
