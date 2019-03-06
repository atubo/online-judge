// https://www.luogu.org/problemnew/show/P2329
// [SCOI2005]栅栏

#include <bits/stdc++.h>
using namespace std;

const int MAXM = 52;
const int MAXN = 1024;
int M, N;
int A[MAXM], B[MAXN], ps[MAXN];

bool dfs(int x, int available, int last) {
    if (x == 0) return true;
    int waste = 0;
    for (int i = 1; i <= M; i++) {
        if (A[i] < B[1]) waste += A[i];
    }
    if (ps[x] > available - waste) return false;
    int t = (B[x] == B[x+1] ? last : 0);
    for (int i = t; i <= M; i++) {
        if (A[i] >= B[x]) {
            A[i] -= B[x];
            bool ok = dfs(x-1, available - B[x], i);
            A[i] += B[x];
            if (ok) return true;
        }
    }
    return false;
}

bool check(int mid, int tot) {
    bool ok = dfs(mid, tot, 1);
    return ok;
}

int main() {
    scanf("%d", &M);
    int tot = 0;
    for (int i = 1; i <= M; i++) {
        scanf("%d", &A[i]);
        tot += A[i];
    }
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &B[i]);
    }
    sort(B+1, B+N+1);
    for (int i = 1; i <= N; i++) {
        ps[i] = ps[i-1] + B[i];
    }

    sort(A+1, A+M+1);

    int lo = 0, hi = N+1;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (check(mid, tot)) lo = mid;
        else hi = mid;
    }
    printf("%d\n", lo);

    return 0;
}
