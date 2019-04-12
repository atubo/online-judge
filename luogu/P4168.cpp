// https://www.luogu.org/problemnew/show/P4168
// [Violet]蒲公英

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 40010;
int A[MAXN], B[MAXN];
int N, M;
int S[210][MAXN], P[210][210];
int D, BLOCK, sz;
int FREQ[MAXN];

void build() {
    BLOCK = sqrt(N);
    sz = (N + BLOCK - 1) / BLOCK;
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < D; j++) {
            S[i][j] = (i == 0 ? 0 : S[i-1][j]);
        }
        for (int j = i*BLOCK; j < min((i+1)*BLOCK, N); j++) {
            int x = A[j];
            S[i][x]++;
        }
    }

    for (int i = 0; i < sz; i++) {
        memset(FREQ, 0, sizeof(FREQ));
        int maxf = 0, maxx = -1;
        for (int k = i*BLOCK; k < min((i+1)*BLOCK, N); k++) {
            int x = A[k];
            FREQ[x]++;
            if (FREQ[x] > maxf || (FREQ[x] == maxf && x < maxx)) {
                maxf = FREQ[x];
                maxx = x;
            }
        }
        P[i][i] = maxx;
        for (int j = i+1; j < sz; j++) {
            for (int k = j*BLOCK; k < min((j+1)*BLOCK, N); k++) {
                int x = A[k];
                FREQ[x]++;
                if (FREQ[x] > maxf || (FREQ[x] == maxf && x < maxx)) {
                    maxf = FREQ[x];
                    maxx = x;
                }
            }
            P[i][j] = maxx;
        }
    }
    memset(FREQ, 0, sizeof(FREQ));
}

int brute(int l, int r) {
    int maxf = 0, maxx = -1;
    for (int i = l; i <= r; i++) {
        int x = A[i];
        FREQ[x]++;
        if (FREQ[x] > maxf || (FREQ[x] == maxf && x < maxx)) {
            maxf = FREQ[x];
            maxx = x;
        }
    }
    for (int i = l; i <= r; i++) {
        int x = A[i];
        FREQ[x] = 0;
    }
    return maxx;
}

int query(int l, int r) {
    int kl = l/BLOCK, kr = r/BLOCK;
    if (kr - kl <= 1) return brute(l, r);

    int maxx = P[kl+1][kr-1], maxf = S[kr-1][maxx] - S[kl][maxx];
    for (int i = l; i < (kl+1)*BLOCK; i++) {
        int x = A[i];
        if (FREQ[x] == 0) FREQ[x] = S[kr-1][x] - S[kl][x];
        FREQ[x]++;
        if (FREQ[x] > maxf || (FREQ[x] == maxf && x < maxx)) {
            maxf = FREQ[x];
            maxx = x;
        }
    }

    for (int i = kr*BLOCK; i <= r; i++) {
        int x = A[i];
        if (FREQ[x] == 0) FREQ[x] = S[kr-1][x] - S[kl][x];
        FREQ[x]++;
        if (FREQ[x] > maxf || (FREQ[x] == maxf && x < maxx)) {
            maxf = FREQ[x];
            maxx = x;
        }
    }

    for (int i = l; i < (kl+1)*BLOCK; i++) {
        FREQ[A[i]] = 0;
    }
    for (int i = kr*BLOCK; i <= r; i++) {
        FREQ[A[i]] = 0;
    }

    return maxx;
}


int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        B[i] = A[i];
    }
    sort(B, B+N);
    auto endp = unique(B, B+N);
    D = endp - B;
    for (int i = 0; i < N; i++) {
        A[i] = lower_bound(B, endp, A[i]) - B;
    }

    build();

    int last = 0;
    for (int i = 0; i < M; i++) {
        int l0, r0;
        scanf("%d%d", &l0, &r0);
        int l = (l0 + last - 1) % N;
        int r = (r0 + last - 1) % N;
        if (l > r) swap(l, r);
        last = B[query(l, r)];
        printf("%d\n", last);
    }

    return 0;
}
