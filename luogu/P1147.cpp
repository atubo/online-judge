// https://www.luogu.org/problem/show?pid=1147
// P1147 连续自然数和

#include <inttypes.h>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
private:
    int M;
    vector<int64_t> ps;
public:
    Solution() {
        cin >> M;
        ps.resize(M+1);
    }

    void solve() {
        buildPs();

        for (int i = 1; i <= M; i++) {
            int64_t sum_r = ps[i];
            if (sum_r < M) continue;
            int l = search(sum_r - M);
            if (l >= 0 && l+1 < i) {
                printf("%d %d\n", l+1, i);
            }
        }
    }

    void buildPs() {
        for (int i = 1; i <= M; i++) {
            ps[i] = ps[i-1] + i;
        }
    }

    int search(int64_t x) {
        vector<int64_t>::const_iterator it = lower_bound(ps.begin(), ps.end(), x);
        if (it == ps.end() || *it != x) return -1;
        return it - ps.begin();
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
