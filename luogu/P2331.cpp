// https://www.luogu.org/problem/show?pid=2331
// [SCOI2005] 最大子矩阵

#include <bits/stdc++.h>
using namespace std;

int N, K;

class Solution1 {
private:
    vector<int> A;
    vector<int> S;
    vector<int> dpPrev, dpCurr;
public:
    Solution1() {
        A.resize(N+1);
        S.resize(N+1);
        for (int i = 1; i <= N; i++) {
            scanf("%d", &A[i]);
            S[i] = S[i-1] + A[i];
        }
        dpPrev.resize(N+1);
        dpCurr.resize(N+1);
    }

    void solve() {
        for (int k = 1; k <= K; k++) {
            int maxDp = 0;
            for (int i = 1; i <= N; i++) {
                maxDp = max(maxDp, dpPrev[i] - S[i]);
                dpCurr[i] = max(dpCurr[i-1], maxDp + S[i]);
            }
            swap(dpPrev, dpCurr);
        }
        printf("%d\n", dpPrev[N]);
    }
};

int main() {
    int m;
    scanf("%d %d %d", &N, &m, &K);
    if (m == 1) {
        Solution1 solution;
        solution.solve();
    } else {
        assert(0);
    }
    return 0;
}
