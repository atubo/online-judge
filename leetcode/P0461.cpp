// https://leetcode.com/problems/hamming-distance/
// 461. Hamming Distance

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int hammingDistance(int x, int y) {
        return __builtin_popcount(x ^ y);
    }
};

int main() {
    int x, y;
    scanf("%d%d", &x, &y);
    Solution solution;
    cout << solution.hammingDistance(x, y) << endl;
    return 0;
}
