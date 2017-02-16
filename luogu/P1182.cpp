// https://www.luogu.org/problem/show?pid=1182
// 数列分段Section II

#include <bits/stdc++.h>
using namespace std;

int N, M;
int A[100010];
int IMAX = 1e9;

bool feasible(int k) {
    int nseg = 1;
    int s = 0;
    for (int i = 0; i < N; i++) {
        if (A[i] > k) return false;
        if (s + A[i] > k) {
            s = A[i];
            nseg++;
            if (nseg > M) return false;
        } else {
            s += A[i];
        }
    }
    return true;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int lo = -1, hi = IMAX;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (feasible(mid)) hi = mid;
        else lo = mid;
    }
    printf("%d\n", hi);
    return 0;
}
