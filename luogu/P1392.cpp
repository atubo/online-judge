// https://www.luogu.org/problem/show?pid=1392
// 取数

#include <bits/stdc++.h>
using namespace std;

int h;

struct Node {
    int x, r, c;
    Node():x(0), r(0), c(0) {}
    Node(int x_, int r_, int c_):x(x_), r(r_), c(c_) {}
} q[805];

void up(int x) {
    while (x > 1) {
        if (q[x].x < q[x>>1].x) {
            swap(q[x], q[x>>1]);
            x>>=1;
        } else break;
    }
}

void down(int x) {
    x <<= 1;
    while (x <= h) {
        if (x < h && q[x+1].x < q[x].x) x++;
        if (q[x].x < q[x>>1].x) {
            swap(q[x>>1], q[x]);
            x <<= 1;
        } else break;
    }
}

typedef priority_queue<Node> PQ;

vector<int> topK(const vector<int>& a, const vector<int>& b, int k) {
    h = 0;
    for (int i = 0; i < k; i++) {
        q[++h] = Node(a[i]+b[0], i, 0);
        up(h);
    }

    vector<int> ret;
    while (true) {
        int x, r, c;
        Node node = q[1];
        q[1] = q[h--]; down(1);
        x = node.x;
        r = node.r;
        c = node.c;
        ret.push_back(x);
        if ((int)ret.size() == k) break;
        q[++h] = Node(a[r]+b[c+1], r, c+1);
        up(h);
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
