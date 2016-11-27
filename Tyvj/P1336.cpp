// http://www.tyvj.cn/p/1336
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int N;
public:
    Solution() {
        cin >> N;
    }

    bool stackLegit(const vector<int>& v) {
        stack<int> st;
        int lo = 0;
        for (int x: v) {
            if (st.empty() || x > st.top()) {
                for (lo = lo+1; lo <= x-1; lo++) {
                    st.push(lo);
                }
            } else if (x == st.top()) {
                st.pop();
            } else {
                return false;
            }
        }
        return true;
    }

    void doperm(int p, int n, vector<int>& curr, vector<vector<int>>& result) {
        if (p == n-1) {
            result.push_back(curr);
            return;
        }
        doperm(p+1, n, curr, result);
        for (int q = p+1; q < n; q++) {
            swap(curr[p], curr[q]);
            doperm(p+1, n, curr, result);
            swap(curr[p], curr[q]);
        }
    }

    vector<vector<int>> permutations(int n) {
        vector<vector<int>> ret;
        vector<int> curr(n);
        iota(curr.begin(), curr.end(), 1);
        doperm(0, n, curr, ret);
        sort(ret.begin(), ret.end());
        return ret;
    }

    vector<vector<int>> build(int n) {
        auto perm = permutations(n);
        vector<vector<int>> ret;
        for (const auto& v: perm) {
            if (stackLegit(v)) {
                ret.push_back(v);
            }
        }
        return ret;
    }

    void solve() {
        if (N == 0) return;
        auto legit = build(min(N, 5));
        if (N >= 5) {
            for (int i = 0; i < 20; i++) {
                for (int j = 1; j <= N-5; j++) {
                    cout << j;
                }
                for (int j = 0; j < 5; j++) {
                    cout << legit[i][j] + N - 5;
                }
                cout << endl;
            }
        } else {
            for (const auto& v: legit) {
                for (int x: v) {
                    cout << x;
                }
                cout << endl;
            }
        }
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
