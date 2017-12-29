// https://www.luogu.org/problemnew/show/P2617
// Dynamic Ranking

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10010, INF = 1e9+10;
int N, M, D, ND;
int A[MAXN], B[MAXN], tmp[MAXN];

bool above(int l, int r, int k, int x) {
    int lb = l/D, rb = r/D;
    int cnt = 0;
    for (int i = l; i < (lb+1)*D; i++) {
        if (A[i] < x) cnt++;
    }
    for (int i = lb+1; i < rb; i++) {
        int *b = B + i*D, *e = B + (i+1)*D;
        int *p = lower_bound(b, e, x);
        cnt += p - b;
    }
    for (int i = rb*D; i <= r; i++) {
        if (A[i] < x) cnt++;
    }
    return cnt >= k;
}

int query(int l, int r, int k) {
    int lb = l/D, rb = r/D;
    if (lb == rb) {
        for (int i = l; i <= r; i++) {
            tmp[i] = A[i];
        }
        sort(tmp + l, tmp + r + 1);
        return tmp[l+k-1];
    } else {
        int lo = -INF, hi = INF;
        while (lo < hi - 1) {
            int mid = (lo + hi) / 2;
            if (above(l, r, k, mid)) hi = mid;
            else                     lo = mid;
        }
        return lo;
    }
}

void update(int p, int t) {
    int pb = p/D;
    A[p] = t;
    if (pb == ND-1) {
        for (int i = pb*D; i < N; i++) {
            B[i] = A[i];
        }
        sort(B+pb*D, B+N);
    } else {
        for (int i = pb*D; i < (pb+1)*D; i++) {
            B[i] = A[i];
        }
        sort(B+pb*D, B+(pb+1)*D);
    }
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        B[i] = A[i];
    }

    D = sqrt(N) + 0.001;
    ND = (N-1)/D + 1;
    for (int i = 0; i < ND-1; i++) {
        sort(B+i*D, B+(i+1)*D);
    }
    sort(B+(ND-1)*D, B+N);

    char cmd[10];
    for (int i = 0; i < M; i++) {
        int a, b, c;
        scanf("%s", cmd);
        if (cmd[0] == 'Q') {
            scanf("%d%d%d", &a, &b, &c);
            a--; b--;
            printf("%d\n", query(a, b, c));
        } else {
            scanf("%d%d", &a, &b);
            a--;
            update(a, b);
        }
    }
    return 0;
}
