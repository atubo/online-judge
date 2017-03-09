// https://www.luogu.org/problem/show?pid=1966
// 火柴排队

#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 99999997;

int64_t add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

int64_t mergeSort(vector<int>& a, int lo, int hi, vector<int>& tmp) {
    if (lo >= hi - 1) return 0;
    int mid = (lo + hi) / 2;
    int64_t ret = mergeSort(a, lo, mid, tmp);
    ret = add(ret, mergeSort(a, mid, hi, tmp));

    int i = lo, j = mid, k = lo;
    while (i < mid && j < hi) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        } else {
            tmp[k++] = a[j++];
            ret = add(ret, mid - i);
        }
    }

    while (i < mid) tmp[k++] = a[i++];
    while (j < hi)  tmp[k++] = a[j++];

    for (i = lo; i < hi; i++) {
        a[i] = tmp[i];
    }
    return ret;
}


int main() {
    int N;
    scanf("%d", &N);
    vector<int> A(N), B(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &B[i]);
    }

    vector<int> ap = A;
    sort(ap.begin(), ap.end());

    vector<int> bp = B;
    sort(bp.begin(), bp.end());

    for (int i = 0; i < N; i++) {
        A[i] = lower_bound(ap.begin(), ap.end(), A[i]) - ap.begin();
        B[i] = lower_bound(bp.begin(), bp.end(), B[i]) - bp.begin();
    }

    for (int i = 0; i < N; i++) {
        ap[A[i]] = i;
    }

    for (int i = 0; i < N; i++) {
        bp[i] = ap[B[i]];
    }

    printf("%lld\n", mergeSort(bp, 0, N, ap));
    return 0;
}
