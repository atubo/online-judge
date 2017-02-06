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

class Solution2 {
private:
    vector<int> A, B;
    vector<int> S, T;
    vector<vector<int> > dpPrev, dpCurr;
public:
    Solution2() {
        A.resize(N+1);
        B.resize(N+1);
        S.resize(N+1);
        T.resize(N+1);
        for (int i = 1; i <= N; i++) {
            scanf("%d %d", &A[i], &B[i]);
            S[i] = S[i-1] + A[i];
            T[i] = T[i-1] + B[i];
        }
        dpPrev.resize(N+1);
        dpCurr.resize(N+1);
        for (int i = 0; i <= N; i++) {
            dpPrev[i].resize(N+1);
            dpCurr[i].resize(N+1);
        }
    }

    void solve() {
        for (int k = 1; k <= K; k++) {
            vector<int> maxDpb(N+1);
            int maxDpc = 0;
            for (int b = 1; b <= N; b++) {
                int maxDpa = 0;
                for (int a = 1; a <= N; a++) {
                    maxDpa = max(maxDpa, dpPrev[a][b] - S[a]);
                    maxDpb[a] = max(maxDpb[a], dpPrev[a][b] - T[b]);
                    dpCurr[a][b] = max(dpCurr[a-1][b], dpCurr[a][b-1]);
                    dpCurr[a][b] = max(dpCurr[a][b], S[a] + maxDpa);
                    dpCurr[a][b] = max(dpCurr[a][b], T[b] + maxDpb[a]);

                    if (a == b) {
                        maxDpc = max(maxDpc, dpPrev[a][b] - S[a] - T[b]);
                        dpCurr[a][b] = max(dpCurr[a][b], maxDpc + S[a] + T[b]);
                    }
                }
            }
            swap(dpPrev, dpCurr);
        }
        printf("%d\n", dpPrev[N][N]);
    }
};

int main() {
    int m;
    scanf("%d %d %d", &N, &m, &K);
    if (m == 1) {
        Solution1 solution;
        solution.solve();
    } else {
        Solution2 solution;
        solution.solve();
    }
    return 0;
}
