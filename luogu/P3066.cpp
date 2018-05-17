// https://www.luogu.org/problemnew/show/P3066
// [USACO12DEC]逃跑的BarnRunning Away From…

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to;
    };

    vector<int> head;
    int eidx;
    int N, M;

    Edge *E;

    Graph(int N_, int M_):N(N_), M(M_) {
        head.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }

        E = new Edge[M]{};
    }

    ~Graph() {
        delete[] E;
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};

class MergeTree {
private:
    int N;
    const vector<int64_t>& A;
    vector<vector<int64_t> > sorted;

    void build(int depth, int left, int right) {
        if (left == right) {
            sorted[depth][left] = A[left];
            return;
        }

        int mid = (left + right) / 2;
        build(depth+1, left, mid);
        build(depth+1, mid+1, right);

        int i = left, j = mid + 1, k = left;
        while (i <= mid && j <= right) {
            if (sorted[depth+1][i] <= sorted[depth+1][j]) {
                sorted[depth][k++] = sorted[depth+1][i++];
            } else {
                sorted[depth][k++] = sorted[depth+1][j++];
            }
        }
        while (i <= mid) sorted[depth][k++] = sorted[depth+1][i++];
        while (j <= right) sorted[depth][k++] = sorted[depth+1][j++];
    }

    // find number of elements < key
    int query(int depth, int left, int right, int qleft, int qright, int64_t key) {
        if (qright < left || qleft > right) return 0;
        if (qleft <= left && right <= qright) {
            auto b = sorted[depth].begin() + left;
            auto e = sorted[depth].begin() + right + 1;
            return lower_bound(b, e, key) - b;
        }

        int mid = (left + right) / 2;
        return query(depth+1, left, mid, qleft, qright, key) +
               query(depth+1, mid+1, right, qleft, qright, key);
    }

public:
    MergeTree(const vector<int64_t>& A_): A(A_) {
        N = A.size();
        int depth = 1, len = 1;
        while (len < 2*N) {
            depth++;
            len <<= 1;
        }
        sorted.resize(depth);
        for (int i = 0; i < depth; i++) {
            sorted[i].resize(N);
        }

        build(0, 0, N-1);
    }

    // find number of elements < key
    int order_of_key(int qleft, int qright, int64_t key) {
        return query(0, 0, N-1, qleft, qright, key);
    }
};

const int MAXN = 200010;
int N;
int dfn[MAXN], out[MAXN];
int curr;
int64_t L;
int64_t dist[MAXN];

void dfs(const Graph &g, int u) {
    dfn[u] = curr++;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        dfs(g, v);
    }
    out[u] = curr - 1;
}

int main() {
    scanf("%d%lld", &N, &L);
    Graph g(N, N-1);
    for (int i = 1; i < N; i++) {
        int p;
        int64_t l;
        scanf("%d%lld", &p, &l);
        p--;
        g.addEdge(p, i);
        dist[i] = dist[p] + l;
    }
    dfs(g, 0);

    vector<int64_t> d2(N);
    for (int i = 0; i < N; i++) {
        d2[dfn[i]] = dist[i];
    }
    MergeTree mt(d2);
    for (int i = 0; i < N; i++) {
        int64_t x = dist[i] + L + 1;
        printf("%d\n", mt.order_of_key(dfn[i], out[i], x));
    }

    return 0;
}
