// https://www.luogu.org/problem/show?pid=1908
// 逆序对

#include <bits/stdc++.h>
using namespace std;

int N;
int A[40010], B[40010];

int merge_sort(int i, int j) {
    if (j - i <= 1) return 0;
    int k = (i + j) / 2;
    int ret = merge_sort(i, k);
    ret += merge_sort(k, j);
    int p = i, q = k, r = i;
    while (p < k && q < j) {
        if (A[p] <= A[q]) {
            B[r++] = A[p++];
        } else {
            B[r++] = A[q++];
            ret += k - p;
        }
    }
    while (p < k) {
        B[r++] = A[p++];
    }
    while (q < j) {
        B[r++] = A[q++];
    }
    for (p = i; p < j; p++) {
        A[p] = B[p];
    }
    return ret;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int ret = merge_sort(0, N);
    printf("%d\n", ret);
    return 0;
}
