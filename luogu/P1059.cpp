// https://www.luogu.org/problemnew/show/P1059
// 明明的随机数

#include <bits/stdc++.h>
using namespace std;

int N;
int A[110];

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    sort(A, A+N);
    int *endp = unique(A, A+N);
    printf("%d\n", endp - A);
    for (int *p = A; p != endp; p++) {
        printf("%d ", *p);
    }
    return 0;
}
