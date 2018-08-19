// https://www.lintcode.com/problem/can-i-win/description
// 985. Can I Win

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canIWin(int n, int target) {
        if (n*(n+1)/2 < target) return false;
        vector<bool> mex(1<<n), vis(1<<n);
        return solve((1<<n)-1, n, target, mex, vis);
    }

    bool solve(int mask, int n, int target,
               vector<bool> &mex, vector<bool> &vis) {
        if (vis[mask]) return mex[mask];
        if (mask == 0 || target <= 0) return false;
        bool ok = false;
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) {
                ok |= !solve(mask & (~(1<<i)), n, target-i-1,
                             mex, vis);
            }
        }
        mex[mask] = ok;
        vis[mask] = true;
        return mex[mask];
    }
};

int main() {
    int n, target;
    cin >> n >> target;
    Solution solution;
    cout << solution.canIWin(n, target) << endl;
    return 0;
}
