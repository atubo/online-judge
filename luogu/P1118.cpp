// https://www.luogu.org/problemnew/show/P1118
// [USACO06FEB]数字三角形Backward Digit Su…

#include <bits/stdc++.h>
using namespace std;

int N, S;
vector<int> A(13), C(12), D(12);

bool dfs(int pos, int sum) {
    if (pos == N) return (sum == S);
    if (sum >= S) return false;
    for (int q = pos; q < N; q++) {
        swap(A[pos], A[q]);
        if (dfs(pos+1, sum+A[pos]*C[pos])) return true;
    }
    for (int q = pos+1; q < N; q++) {
        swap(A[q-1], A[q]);
    }
    return false;
}

int main() {
    scanf("%d%d", &N, &S);
    C[0] = 1;
    for (int i = 1; i < N; i++) {
        D[0] = 1;
        for (int j = 1; j < N; j++) {
            D[j] = C[j-1] + C[j];
        }
        swap(C, D);
    }
    iota(A.begin(), A.end(), 1);
    if (dfs(0, 0)) {
        for (int i = 0; i < N; i++) {
            printf("%d ", A[i]);
        }
        printf("\n");
    }
    return 0;
}
