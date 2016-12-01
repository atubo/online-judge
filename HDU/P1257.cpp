// http://acm.hdu.edu.cn/showproblem.php?pid=1257
// Simple LIS problem
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
public:
    Solution() {}

    void solve() {
        int N;
        while (scanf("%d", &N) != EOF) {
            vector<int> A(N);
            for (int i = 0; i < N; i++) {
                scanf("%d", &A[i]);
            }
            vector<int> C(N+1, INT_MAX);
            C[0] = 0;
            int ret = 0;
            for (int i = 0; i < N; i++) {
                int p = lower_bound(C.begin(), C.end(), A[i]) - C.begin() - 1;
                if (A[i] < C[p+1]) {
                    C[p+1] = A[i];
                    ret = max(ret, p+1);
                }
            }
            cout << ret << endl;
        }
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
