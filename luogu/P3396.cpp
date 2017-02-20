// https://www.luogu.org/problem/show?pid=3396
// 哈希冲突

#include <bits/stdc++.h>
using namespace std;
const int SZ1 = 75078;
const int SZ2 = SZ1 * 388;
int stat[SZ2];

short A[150010];
int N, M;
int BLOCKSIZE;

int& statRef(int b, int p, int k) {
    return stat[b*SZ1 + p*(p-1)/2 + k];
}

void preprocess() {
    for (int i = 0; i < N; i++) {
        int blockId = i / BLOCKSIZE;
        for (int p = 1; p < BLOCKSIZE; p++) {
            statRef(blockId, p, (i+1)%p) += A[i];
        }
    }
}

int solve(int p, int k) {
    int ans = 0;
    if (p >= BLOCKSIZE) {
        for (int i = k-1; i < N; i += p) {
            ans += A[i];
        }
    } else {
        for (int i = 0; i <= (N-1)/BLOCKSIZE; i++) {
            ans += statRef(i, p, k);
        }
    }
    return ans;
}

void update(int k, int x) {
    int blockId = (k-1) / BLOCKSIZE;
    for (int p = 1; p < BLOCKSIZE; p++) {
        statRef(blockId, p, k%p) += (x - A[k-1]);
    }
    A[k-1] = x;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%hd", &A[i]);
    }

    BLOCKSIZE = (int)sqrt((double)N);
    preprocess();

    char str[10];
    int x, y;
    for (int i = 0; i < M; i++) {
        scanf("%s %d %d", str, &x, &y);
        if (str[0] == 'A') {
            printf("%d\n", solve(x, y));
        } else {
            update(x, y);
        }
    }
    return 0;
}
