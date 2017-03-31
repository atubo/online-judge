// https://www.luogu.org/problem/show?pid=1678
// 烦恼的高考志愿

#include <bits/stdc++.h>
using namespace std;

const int MAXM = 100010;
const int MAXN = 100010;
int C[MAXM], S[MAXN];
int M, N;

int main() {
    scanf("%d %d", &M, &N);
    for (int i = 0; i < M; i++) {
        scanf("%d", &C[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &S[i]);
    }
    sort(C, C+M);
    sort(S, S+N);

    int p = 0;
    int64_t ret = 0;
    for (int i = 0; i < N; i++) {
        while (p < M-1 && abs(S[i] - C[p]) >= abs(S[i] - C[p+1])) p++;
        ret += abs(S[i] - C[p]);
    }
    printf("%lld\n", ret);
    return 0;
}
