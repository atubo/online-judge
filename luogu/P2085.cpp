// https://www.luogu.org/problem/show?pid=2085
// 最小函数值(minval)

#include <bits/stdc++.h>
using namespace std;
using Tp = tuple<int, int, int>;

const int MAXN = 10010;
int A[MAXN], B[MAXN], C[MAXN];
int N, M;

int f(int i, int x) {
    return A[i]*x*x + B[i]*x + C[i];
}

Tp init(int i) {
    return make_tuple(f(i, 1), i, 1);
}

Tp next(int i, int x) {
    return make_tuple(f(i, x+1), i, x+1);
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d%d%d", &A[i], &B[i], &C[i]);
    }
    priority_queue<Tp, vector<Tp>, greater<Tp>> pq;
    for (int i = 0; i < N; i++) {
        pq.push(init(i));
    }

    while (M--) {
        int y, i, x;
        tie(y, i, x) = pq.top();
        printf("%d ", y);
        pq.pop();
        pq.push(next(i, x));
    }
    printf("\n");
    return 0;
}
