// https://www.lintcode.com/problem/unlock-problem/description
// 934. Unlock Problem

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int unlock(int n, int m) {
        bool *a = new bool[m+1]{};

        for (int i = 1; i <= min(n, m); i++) {
            for (int j = i; j <= m; j += i) {
                a[j] = 1 ^ a[j];
            }
        }

        int ans = 0;
        for (int i = 1; i <= m; i++) {
            ans += a[i];
        }

        delete [] a;
        return ans;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    Solution solution;
    cout << solution.unlock(n, m) << endl;
    return 0;
}
