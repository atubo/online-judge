// https://www.luogu.org/problemnew/show/P1177
// 【模板】快速排序

#include <bits/stdc++.h>
using namespace std;

int N;
int A[100010];

void reverse(int begin, int end) {
    int p = begin, q = end - 1;
    while (p < q) swap(A[p++], A[q--]);
}

void quicksort(int begin, int end) {
    if (end - begin <= 1) return;
    int pivot = double(rand())/RAND_MAX * (end - begin - 1) + begin;
    int x = A[pivot];
    swap(A[begin], A[pivot]);
    int p = begin+1, q = end-1;
    int r = p;
    while (p <= q) {
        if (A[q] == x) {
            swap(A[p], A[q]);
            swap(A[r++], A[p++]);
        } else if (A[q] < x) {
            swap(A[p++], A[q]);
        } else {
            q--;
        }
    }
    reverse(begin, p);
    quicksort(begin, begin + p - r);
    quicksort(p, end);
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d",  &A[i]);
    }
    quicksort(0, N);
    for (int i = 0; i < N-1; i++) {
        printf("%d ", A[i]);
    }
    printf("%d\n", A[N-1]);
    return 0;
}
