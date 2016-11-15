// http://codeforces.com/problemset/problem/383/C
#include <bits/stdc++.h>
using namespace std;

template<typename V, typename D=V>
class SegmentTreeTD {
    struct Node {
        Node(): value(0), update(0),count(0) {}
        V value;
        D update;
        int count;
    };

public:
    SegmentTreeTD(const vector<V>& A, V zero_, D zeroUpdate_) :
        N(A.size()), zero(zero_), zeroUpdate(zeroUpdate_) {
        int nlog = 0;
        int n = N;
        while (n > 0) {
            n = (n >> 1);
            nlog++;
        }
        int msize = 2 * (1 << (nlog+1)) + 1;
        M = new Node[msize];
        for (int i = 1; i < msize; i++) M[i].update = zeroUpdate;
        initialize(1, 0, N-1, A);
    }

    ~SegmentTreeTD() {
        delete[] M;
    }

    void initialize(int node, int b, int e, const vector<V>& A) {
        if (b == e) {
            M[node].value = A[b];
            M[node].count = 1;
        }
        else {
            initialize(2*node, b, (b+e)/2, A);
            initialize(2*node+1, (b+e)/2+1, e, A);
            M[node].value = eval(M[2*node]) + eval(M[2*node+1]);
            M[node].count = M[2*node].count + M[2*node+1].count;
        }
    }

    // i, j inclusive
    V query(int i, int j) const {
        return query(1, 0, N-1, i, j);
    }

    void update(int i, int j, D d) {
        update(1, 0, N-1, i, j, d);
    }

private:
    const int N;
    const V zero;   // zero element for combine
    const D zeroUpdate; // zero for update

    Node* M;

    V eval(const Node& node) const {
        return node.value + node.update * node.count;
    }

    V query(int node, int b, int e, int i, int j) const {
        assert(b <= e);
        if (i > e || j < b) {
            return zero;
        }

        if (M[node].update != zeroUpdate) {
            M[node].value = eval(M[node]);
            if (b != e) {
                M[2*node].update = M[node].update + M[2*node].update;
                M[2*node+1].update = M[node].update + M[2*node+1].update;
            }
            M[node].update = zeroUpdate;
        }

        if (b >= i && e <= j) {
            return M[node].value;
        }

        V p1 = query(2*node, b, (b+e)/2, i, j);
        V p2 = query(2*node+1, (b+e)/2+1, e, i, j);

        return p1 + p2;
    }

    void update(int node, int b, int e, int i, int j, D d) {
        if (i > e || j < b) {
            return;
        }
        if (b >= i && e <= j) {
            M[node].update = d + M[node].update;
            return;
        }
        if (M[node].update != zeroUpdate) {
            M[2*node].update = M[node].update + M[2*node].update;
            M[2*node+1].update = M[node].update + M[2*node+1].update;
        }

        update(2*node, b, (b+e)/2, i, j, d);
        update(2*node+1, (b+e)/2+1, e, i, j, d);
        M[node].value = eval(M[2*node]) + eval(M[2*node+1]);
        M[node].update = zeroUpdate;
    }
};

class Solution {
    using Adj = vector<vector<int>>;
    using PII = pair<int, int>;
private:
    int N, M;
    vector<int> A;
    Adj adj;
    vector<int> idx;
    vector<PII> range;
    vector<int> depth;
    int count;
public:
    Solution() {
        cin >> N >> M;
        A.resize(N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i]);
        }

        adj.resize(N);
        for (int i = 0; i < N-1; i++) {
            int v, u;
            scanf("%d %d", &v, &u);
            v--; u--;
            adj[v].push_back(u);
            adj[u].push_back(v);
        }

        idx.resize(N);
        range.resize(N);
        depth.resize(N);
        count = 0;
        vector<bool> visited(N, false);
        dfs(0, 0, visited);
    }

    void dfs(int u, int d, vector<bool>& visited) {
        int before = count;
        visited[u] = true;
        depth[u] = d;
        for (int v: adj[u]) {
            if (!visited[v]) {
                dfs(v, d+1, visited);
            }
        }
        idx[u] = count;
        int after = count;
        range[u] = make_pair(before, after);
        count++;
    }

    void solve() {
        vector<int> a(N);
        for (int i = 0; i < N; i++) {
            a[idx[i]] = A[i];
        }

        SegmentTreeTD<int, int> st(a, 0, 0);

        for (int i = 0; i < M; i++) {
            int t, x, val;
            scanf("%d", &t);
            if (t == 1) {
                scanf("%d %d", &x, &val);
                x--;
                if (depth[x] & 1) val = -val;
                st.update(range[x].first, range[x].second, val);
            } else {
                scanf("%d", &x);
                x--;
                int64_t v = st.query(idx[x], idx[x]);
                if (depth[x] & 1) {
                    v = int64_t(2) * A[x] - v;
                }
                cout << v << endl;
            }
        }
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
