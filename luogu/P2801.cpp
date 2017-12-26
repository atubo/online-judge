// https://www.luogu.org/problemnew/show/P2801
// 教主的魔法

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;
int N, Q, D, M;
int A[MAXN], B[MAXN], S[1010];

void sync(int m) {
    int last = min(N, (m+1) * D);
    for (int i = m*D; i < last; i++) {
        B[i] = A[i];
    }
    sort(B + m*D, B + last);
}

void update(int L, int R, int W) {
    int m1 = L/D, m2 = R/D;
    if (m1 == m2) {
        for (int i = L; i <= R; i++) {
            A[i] += W;
        }
        sync(m1);
    } else {
        for (int i = L; i < (m1+1) * D; i++) {
            A[i] += W;
        }
        sync(m1);
        for (int i = m2*D; i <= R; i++) {
            A[i] += W;
        }
        sync(m2);
        for (int i = m1+1; i < m2; i++) {
            S[i] += W;
        }
    }
}

void query(int L, int R, int C) {
    int ans = 0;
    int m1 = L/D, m2 = R/D;
    if (m1 == m2) {
        for (int i = L; i <= R; i++) {
            if (A[i] + S[m1] >= C) ans++;
        }
    } else {
        for (int i = L; i < (m1+1) * D; i++) {
            if (A[i] + S[m1] >= C) ans++;
        }
        for (int i = m2*D; i <= R; i++) {
            if (A[i] + S[m2] >= C) ans++;
        }
        for (int i = m1+1; i < m2; i++) {
            ans += B+(i+1)*D - lower_bound(B+i*D, B+(i+1)*D, C-S[i]);
        }
    }
    printf("%d\n", ans);
}

int main() {
    scanf("%d%d", &N, &Q);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        B[i] = A[i];
    }

    D = sqrt(N) + 0.001;
    M = N/D;
    for (int i = 0; i < M; i++) {
        sort(B + i*D, B + (i+1)*D);
    }
    sort(B + M*D, B + N);

    char cmd[10];
    int L, R, C;
    for (int i =  0; i < Q; i++) {
        scanf("%s%d%d%d", cmd, &L, &R, &C);
        if (cmd[0] == 'M') update(L-1, R-1, C);
        else               query(L-1, R-1, C);
    }

    return 0;
}
