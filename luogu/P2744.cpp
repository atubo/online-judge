// https://www.luogu.org/problemnew/show/P2744
// [USACO5.3]量取牛奶Milk Measuring

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;
const int MAXQ = 20010;
int Q, P;
int DMAX;
int A[MAXN];
bool B[MAXQ], last[MAXN][MAXQ];
int sol[MAXN];

void save(int x) {
    for (int i = 0; i <= Q; i++) {
        last[x][i] = B[i];
    }
}

void restore(int x) {
    for (int i = 0;i <= Q; i++) {
        B[i] = last[x][i];
    }
}

bool dfs(int d, int p) {
    if (d > DMAX) return false;
    if (B[Q]) return true;
    if (d == DMAX) return false;
    for (int i = p+1; i < P; i++) {
        save(d);
        int x = A[i];
        for (int j = 0; j <= Q; j++) {
            if (B[j]) {
                for (int y = j; y <= Q; y += x) {
                    B[y] = true;
                }
            }
        }
        sol[d+1] = i;
        if (dfs(d+1, i)) return true;
        restore(d);
    }
    return false;
}


int main() {
    scanf("%d%d", &Q, &P);
    for (int i = 0; i < P; i++) {
        scanf("%d", &A[i]);
    }
    sort(A, A+P);
    P = unique(A, A+P) - A;
    while (A[P-1] > Q) P--;
    B[0] = true;
    int ans = 0;
    for (DMAX = 1; DMAX <= 100; DMAX++) {
        if (dfs(0, -1)) {
            ans = DMAX;
            break;
        }
    }

    printf("%d ", ans);
    for (int i = 1; i <= ans; i++) {
        printf("%d ", A[sol[i]]);
    }

    return 0;
}
