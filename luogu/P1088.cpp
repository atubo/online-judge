// https://www.luogu.org/problem/show?pid=1088
// 火星人

#include <bits/stdc++.h>
using namespace std;

int N;

void next(vector<int>& A) {
    int p = N - 2;
    while (A[p] > A[p+1]) p--;
    int q = N - 1;
    while (A[q] < A[p]) q--;
    swap(A[p], A[q]);
    sort(A.begin()+p+1, A.end());
}

int main() {
    int M;
    scanf("%d %d", &N, &M);
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    while (M--) {
        next(A);
    }
    for (int i = 0; i < N; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    return 0;
}
