// https://leetcode.com/problems/beautiful-arrangement/
// 526. Beautiful Arrangement

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countArrangement(int N) {
        vector<vector<int>> legal(N+1);
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (i%j == 0 || j%i == 0) legal[i].push_back(j);
            }
        }
        int ret = 0;
        dfs(N, legal, (1<<(N+1))-1, ret);
        return ret;
    }
private:
    void dfs(int p, const vector<vector<int>> &legal, int mask, int &ret) {
        if (p == 0) {
            ret++;
            return;
        }
        for (int x: legal[p]) {
            if (mask & (1<<x)) {
                dfs(p-1, legal, mask & (~(1U<<x)), ret);
            }
        }
    }
};

int main() {
    int n;
    cin >> n;
    Solution solution;
    cout << solution.countArrangement(n) << endl;
    return 0;
}
