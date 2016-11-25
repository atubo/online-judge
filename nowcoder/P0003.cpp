// 懂二进制
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countBitDiff(int m, int n) {
        int x = m ^ n;
        int ret = 0;
        while (x != 0) {
            x &= (x - 1);
            ret++;
        }
        return ret;
    }
};

int main() {
    int m, n;
    cin >> m >> n;
    Solution solution;
    cout << solution.countBitDiff(m, n) << endl;
    return 0;
}
