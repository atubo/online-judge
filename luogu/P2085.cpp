// https://www.luogu.org/problem/show?pid=2085
// 最小函数值(minval)

#include <bits/stdc++.h>
using namespace std;
using Tp = tuple<int, int, int, double>;

const int MAXN = 10010;
int A[MAXN], B[MAXN], C[MAXN];
int N, M;

int next(int x, double mid) {
    if (x < mid) {
        x = ceil(2*mid - x);
    } else {
        x = floor(2*mid - x);
    }
    return x;
}

Tp init(int i) {
    double mid = - (double)B[i]/(2.0*A[i]);
    int f = floor(mid);
    int x;
    if (mid - f == 0.5) mid -= 0.00001;
    if (mid - f < 0.5) {
        x = f;
    } else {
        x = f + 1;
    }
    while (x <= 0) x = next(x, mid);
    int y = A[i]*x*x + B[i]*x + C[i];
    return make_tuple(y, i, x, mid);
}

Tp next(int i, int x, double mid) {
    do {
        x = next(x, mid);
    } while (x <= 0);
    return make_tuple(A[i]*x*x + B[i]*x + C[i], i, x, mid);
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
        double mid;
        tie(y, i, x, mid) = pq.top();
        printf("%d ", y);
        pq.pop();
        pq.push(next(i, x, mid));
    }
    printf("\n");
    return 0;
}
