// https://www.luogu.org/problem/show?pid=1508
// Likecloud-吃、吃、吃

#include <bits/stdc++.h>
using namespace std;

vector<int> dpPrev, dpCurr;
vector<vector<int> > A;
int M, N;

int main() {
    scanf("%d %d", &M, &N);
    dpPrev.resize(N, INT_MIN);
    dpCurr.resize(N, INT_MIN);

    A.resize(M);
    for (int i = 0; i < M; i++) {
        A[i].resize(N);
        for (int j = 0; j < N; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    dpPrev[N/2] = 0;
    for (int i = M-1; i >= 0; i--) {
        for (int j = 0; j < N; j++) {
            dpCurr[j] = INT_MIN;
            if (dpPrev[j] != INT_MIN) {
                dpCurr[j] = dpPrev[j];
            }
            if (j > 0 && dpPrev[j-1] != INT_MIN) {
                dpCurr[j] = max(dpCurr[j], dpPrev[j-1]);
            }
            if (j < N-1 && dpPrev[j+1] != INT_MIN) {
                dpCurr[j] = max(dpCurr[j], dpPrev[j+1]);
            }
            if (dpCurr[j] != INT_MIN) {
                dpCurr[j] += A[i][j];
            }
        }
        swap(dpPrev, dpCurr);
    }

    int ans = INT_MIN;
    for (int i = 0; i < N; i++) {
        ans = max(ans, dpPrev[i]);
    }
    printf("%d\n", ans);
    return 0;
}
