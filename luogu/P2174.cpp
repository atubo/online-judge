// https://www.luogu.org/problemnew/show/P2174
// 小Z的神奇数列

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6+10;
const int MAXM = 1e6+10;
const int MOD = 317847191;
int N, M;

struct Query {
    int op, x;
} Q[MAXM];
int ans[MAXM];
int A[MAXN], B[MAXN];

int qpow(int64_t x, int n) {
    int64_t ret = 1;
    while (n) {
        if (n & 1) ret = (ret * x) % MOD;
        x = (x * x) % MOD;
        n >>= 1;
    }
    return ret;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int n1 = 0;
    for (int i = 0; i < M; i++) {
        int x;
        char cmd[5];
        scanf("%s", cmd);
        if (cmd[0] == 'D') {
            scanf("%d", &x);
            Q[i] = {0, x};
            B[n1++] = x;
        } else if (cmd[0] == 'B') {
            Q[i] = {1, -1};
        } else if (cmd[0] == 'S') {
            Q[i] = {2, -1};
        } else if (cmd[0] == 'M') {
            Q[i] = {3, -1};
        } else {
            Q[i] = {4, -1};
        }
    }

    sort(A, A+N);
    sort(B, B+n1);

    int curr = 1;
    int mi = INT_MAX, mx = INT_MIN;
    int p = 0, q = 0;
    while (true) {
        while (p < N && q < n1 && A[p] == B[q]) {
            p++;
            q++;
        }
        if (q == n1) {
            while (p < N) {
                curr = (1LL * curr * A[p]) % MOD;
                mi = min(mi, A[p]);
                mx = max(mx, A[p]);
                p++;
            }
            break;
        }
        while (A[p] < B[q]) {
            curr = (1LL * curr * A[p]) % MOD;
            mi = min(mi, A[p]);
            mx = max(mx, A[p]);
            p++;
        }
    }

    for (int i = M-1; i >= 0; i--) {
        if (Q[i].op == 0) {
            int x = Q[i].x;
            curr = (1LL * curr * x) % MOD;
            ans[i] = -1;
            mx = max(mx, x);
            mi = min(mi, x);
        } else if (Q[i].op == 1) {
            ans[i] = mx;
        } else if (Q[i].op == 2) {
            ans[i] = mi;
        } else if (Q[i].op == 3) {
            int x = mx;
            int n = mi;
            ans[i] = qpow(x, n);
        } else {
            ans[i] = curr;
        }
    }

    for (int i = 0; i < M; i++) {
        if (ans[i] != -1) printf("%d\n", ans[i]);
    }

    return 0;
}
