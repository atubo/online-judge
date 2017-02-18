// https://www.luogu.org/problem/show?pid=1316
// 丢瓶盖

#include <bits/stdc++.h>
using namespace std;

int A, B;
int X[100010];

bool feasible(int d) {
    int x = X[0];
    int i = 1;
    int count = 1;
    while (true) {
        while (i < A && X[i] - x < d) i++;
        if (i == A) break;
        count++;
        x = X[i++];
    }
    return count >= B;
}

int main() {
    scanf("%d %d", &A, &B);
    for (int i = 0; i < A; i++) {
        scanf("%d", &X[i]);
    }

    sort(X, X+A);
    int lo = 0, hi = X[A-1]-X[0]+1;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (feasible(mid)) lo = mid;
        else hi = mid;
    }
    printf("%d\n", lo);
    return 0;
}
