// https://www.luogu.org/problem/show?pid=1031
// 均分纸牌

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;
int A[MAXN];
int N;

int main() {
    scanf("%d", &N);
    int avg = 0;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        avg += A[i];
    }
    avg /= N;

    int ret = 0;
    for (int i = 1; i < N; i++) {
        ret += (avg != A[i]);
        A[i+1] -= avg - A[i];
    }
    printf("%d\n", ret);
    return 0;
}
