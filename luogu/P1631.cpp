// https://www.luogu.org/problem/show?pid=1631
// 序列合并

#include <bits/stdc++.h>
using namespace std;
using TI = tuple<int, int, int>;

const int MAXN = 100010;
int A[MAXN], B[MAXN];
int N;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &B[i]);
    }

    priority_queue<TI, vector<TI>, greater<TI>> pq;
    for (int i = 0; i < N; i++) {
        pq.push(make_tuple(A[i]+B[0], i, 0));
    }

    for (int k = 0; k < N; k++) {
        int s, i, j;
        tie(s, i, j) = pq.top();
        printf("%d ", s);
        pq.pop();
        if (j < N-1) pq.push(make_tuple(A[i]+B[j+1], i, j+1));
    }
    printf("\n");
    return 0;
}
