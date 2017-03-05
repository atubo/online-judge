// https://www.luogu.org/problem/show?pid=1392
// 取数

#include <bits/stdc++.h>
using namespace std;

typedef tuple<int, int, int> TIII;
typedef priority_queue<TIII, vector<TIII>, greater<TIII> > PQ;

vector<int> topK(const vector<int>& a, const vector<int>& b, int k) {
    PQ pq;
    for (int i = 0; i < k; i++) {
        pq.push(make_tuple(a[i] + b[0], i, 0));
    }

    vector<int> ret;
    while (true) {
        int x, r, c;
        tie(x, r, c) = pq.top();
        pq.pop();
        ret.push_back(x);
        if ((int)ret.size() == k) break;
        pq.push(make_tuple(a[r]+b[c+1], r, c+1));
    }
    return ret;
}

int main() {
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);
    vector<vector<int> > A(N);
    for (int i = 0; i < N; i++) {
        A[i].resize(M);
        for (int j = 0; j < M; j++) {
            scanf("%d", &A[i][j]);
        }
        sort(A[i].begin(), A[i].end());
    }

    vector<int> a = A[0];
    for (int i = 1; i < N; i++) {
        a = topK(a, A[i], K);
    }

    for (int i = 0; i < K; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
