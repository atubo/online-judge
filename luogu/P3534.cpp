// https://www.luogu.org/problemnew/show/P3534
// [POI2012]STU-Well

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6+10;
int N;
int64_t M;
int A[MAXN], B[MAXN];
int L[MAXN], R[MAXN];
int64_t S[MAXN];
int K;

bool feasible(int dmax) {
    memcpy(B, A, (N+1)*sizeof(int));
    int64_t e = 0;
    for (int i = 2; i <= N; i++) {
        if (B[i] - B[i-1] > dmax) {
            e += B[i] - B[i-1] - dmax;
            B[i] = B[i-1] + dmax;
        }
    }
    for (int i = N-1; i >= 1; i--) {
        if (B[i] - B[i+1] > dmax) {
            e += B[i] - B[i+1] - dmax;
            B[i] = B[i+1] + dmax;
        }
    }
    if (e > M) return false;

    L[1] = R[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (B[i] > (i-1)*dmax) R[1] = i;
        else break;
    }

    for (int i = 2; i <= N; i++) {
        L[i] = i;
        for (int j = L[i-1]; j <= i; j++) {
            if (B[j] > (i-j)*dmax) {
                L[i] = j;
                break;
            }
        }
        R[i] = R[i-1];
        for (int j = R[i-1]+1; j <= N; j++) {
            if (B[j] > (j-i)*dmax) {
                R[i] = j;
            } else {
                break;
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        S[i] = S[i-1] + B[i];
    }

    K = 0;
    for (int i = 1; i <= N; i++) {
        int64_t e2 = B[i] + S[i-1] - S[L[i]-1];
        int d = i - L[i];
        e2 -= 1LL*d*(d+1)*dmax/2;
        e2 += S[R[i]] - S[i];
        d = R[i] - i;
        e2 -= 1LL*d*(d+1)*dmax/2;
        if (e + e2 <= M) {
            K = i;
            break;
        }
    }

    return K > 0;
}


int main() {
    scanf("%d%ld", &N, &M);
    int maxh = 0;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        maxh = max(maxh, A[i]);
    }

    if (feasible(0)) {
        printf("%d %d\n", K, 0);
        return 0;
    }
    int lo = 0, hi = maxh;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (feasible(mid)) hi = mid;
        else lo = mid;
    }
    feasible(hi);
    printf("%d %d\n", K, hi);
    return 0;
}
