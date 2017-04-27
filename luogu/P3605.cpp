// https://www.luogu.org/problem/show?pid=3605
// [USACO17JAN]Promotion Counting晋升者计数

#include <bits/stdc++.h>
using namespace std;

class Graph {
    static const int MAXM = 250000;
public:
    struct Edge {
        int next, to;
    } E[MAXM];

    vector<int> head;
    int eidx;
    int N;

    Graph(int N_):N(N_) {
        head.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};

const int MAXN = 100010;
int P[MAXN];

class DfsOrder {
public:
    vector<int> A;
    int first[MAXN], last[MAXN];
    int order;

    DfsOrder() {
        order = 0;
    }

    void dfs(const Graph &g, int u, int f) {
        first[u] = order++;
        A.push_back(P[u]);
        for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (v != f) dfs(g, v, u);
        }
        last[u] = order++;
        A.push_back(INT_MAX);
    }
};

class MergeTree {
private:
    int N;
    const vector<int>& A;
    vector<vector<int> > sorted;

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
    int query(int depth, int left, int right, int qleft, int qright, int key) {
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
    MergeTree(const vector<int>& A_): A(A_) {
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
    int order_of_key(int qleft, int qright, int key) {
        return query(0, 0, N-1, qleft, qright, key);
    }

    // k-the element in [qleft, qright], counting from 0
    int find_by_order(int qleft, int qright, int k) {
        int lo = 0, hi = N;
        while (lo < hi - 1) {
            int mid = (lo + hi) / 2;
            int cnt = order_of_key(qleft, qright, sorted[0][mid]);
            if (cnt <= k) lo = mid;
            else hi = mid;
        }
        return sorted[0][lo];
    }
};

class Solution {
private:
    int N;
    Graph *graph;
public:
    Solution() {
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &P[i]);
        }

        graph = new Graph(N);
        for (int i = 1; i < N; i++) {
            int u;
            scanf("%d", &u);
            u--;
            graph->addEdge(i, u);
            graph->addEdge(u, i);
        }
    }

    void solve() {
        DfsOrder dfn;
        dfn.dfs(*graph, 0, -1);

        MergeTree mt(dfn.A);

        for (int i = 0; i < N; i++) {
            int k = mt.order_of_key(dfn.first[i]+1, dfn.last[i]-1, P[i]);
            int m = (dfn.last[i] - dfn.first[i] - 1) / 2;
            printf("%d\n", m - k);
        }
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
