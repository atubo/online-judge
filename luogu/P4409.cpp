// https://www.luogu.org/problemnew/show/P4409
// [ZJOI2006]皇帝的烦恼

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20010;
int N;
int A[MAXN], ma[MAXN], mi[MAXN];

bool check(int x) {
    ma[1] = mi[1] = A[1];
    for (int i = 2; i <= N; i++) {
        ma[i] = min(A[i], A[1] - mi[i-1]);
        mi[i] = max(0, A[1] + A[i-1] - ma[i-1] + A[i] - x);
    }
    return mi[N] == 0;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
    int lo = 0, hi = 2e9;
    for (int i = 1; i <= N; i++) {
        lo = max(lo, A[i] + A[(i%N)+1]);
    }
    lo--;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else lo = mid;
    }
    printf("%d", hi);
    return 0;
}
