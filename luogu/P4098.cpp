// https://www.luogu.org/problemnew/show/P4098
// [HEOI2013]ALO

#include <bits/stdc++.h>
using namespace std;

class SparseTableRMQ {
public:
    SparseTableRMQ(int *a, int n): n_(n), maxb_(log2(n)+1) {
        alloc();
        preCompute(a);
    }

    ~SparseTableRMQ() {
        dealloc();
    }

    // RMQ for range [u, v]
    int rmq(int u, int v) const {
        int j = log_[v-u+1];
        return max(st_[u][j], st_[v+1-(1<<j)][j]);
    }
private:
    int n_;
    int maxb_;
    int **st_;
    int *log_;

    void alloc() {
        st_ = new int*[n_]{};
        for (int i = 0; i < n_; i++) {
            st_[i] = new int[maxb_]{};
            for (int j = 0; j < maxb_; j++) {
                st_[i][j] = INT_MIN;
            }
        }
        log_ = new int[n_]{};
    }

    void dealloc() {
        delete[] log_;
        for (int i = 0; i < n_; i++) {
            delete[] st_[i];
        }
        delete[] st_;
    }

    void preCompute(int *a) {
        for (int i = 2; i < n_; i++) log_[i] = log_[i>>1] + 1;

        for (int i = 0; i < n_; i++) {
            st_[i][0] = a[i];
        }

        for (int j = 1; j < maxb_; j++) {
            for (int i = 0; i + (1 << j) - 1 < n_; i++) {
                st_[i][j] = max(st_[i][j-1], st_[i+(1<<(j-1))][j-1]);
            }
        }
    }

};

class PersistentBinaryTrie {
public:
    struct Node {
        int children[2];
        int count;
        Node() {
            children[0] = children[1] = 0;
            count = 0;
        }
    };

    PersistentBinaryTrie(int n, int nd): n_(n), nd_(nd) {
        root_ = new int[n_+1]{};
        nodes_ = new Node[(n_+1) * (nd_+1)]{};
    }

    ~PersistentBinaryTrie() {
        delete[] root_;
        delete[] nodes_;
    }

    void insert(int currRootIndex, int prevRootIndex, int x) {
        root_[currRootIndex] = root_[prevRootIndex];
        doInsert(root_[currRootIndex], x, nd_);
    }

    int traverse(int l, int r, int x) {
        Node left = nodes_[root_[l]];
        Node right = nodes_[root_[r]];
        int ret = 0;
        for (int d = 31; d >= 0; d--) {
            int b = (x >> d) & 1;
            int ll = left.children[0], lr = left.children[1];
            int rl = right.children[0], rr = right.children[1];
            if (b == 0) {
                if (nodes_[rr].count > nodes_[lr].count) {
                    left = nodes_[lr];
                    right = nodes_[rr];
                    ret |= (1 << d);
                } else {
                    left = nodes_[ll];
                    right = nodes_[rl];
                }
            } else {
                if (nodes_[rl].count > nodes_[ll].count) {
                    left = nodes_[ll];
                    right = nodes_[rl];
                    ret |= (1 << d);
                } else {
                    left = nodes_[lr];
                    right = nodes_[rr];
                }
            }
        }
        return ret;
    }

private:
    int n_; // number of positions, index is 1-based
    int nd_;    // number of digits
    int *root_;
    Node *nodes_;
    int currIdx_ = 1;

    void doInsert(int &now, int x, int d) {
        nodes_[currIdx_++] = nodes_[now];
        now = currIdx_ - 1;
        nodes_[now].count++;
        if (d == 0) return;
        d--;
        int t = (x >> d) & 1;
        doInsert(nodes_[now].children[t], x, d);
    }
};

const int MAXN = 50010;
int N;
int A[MAXN];
int L1[MAXN], L2[MAXN], R1[MAXN], R2[MAXN];

int searchLeft(int p, int x, const SparseTableRMQ &rmq) {
    if (p <= 1) return 0;
    if (rmq.rmq(1, p-1) < x) return 0;
    if (A[p-1] > x) return p-1;
    int lo = 1, hi = p-1;
    while (lo < hi-1) {
        int mid = (lo + hi) / 2;
        if (rmq.rmq(mid, p-1) > x) lo = mid;
        else hi = mid;
    }
    return lo;
}

int searchRight(int p, int x, const SparseTableRMQ &rmq) {
    if (p >= N) return N+1;
    if (rmq.rmq(p+1, N) < x) return N+1;
    int lo = p, hi = N;
    while (lo < hi-1) {
        int mid = (lo + hi) / 2;
        if (rmq.rmq(p+1, mid) > x) hi = mid;
        else lo = mid;
    }
    return hi;
}

void solve() {
    stack<int> st;
    for (int i = 1; i <= N; i++) {
        while (!st.empty() && A[i] > A[st.top()]) st.pop();
        L1[i] = (st.empty() ? 0 : st.top());
        st.push(i);
    }
    while (!st.empty()) st.pop();
    for (int i = N; i >= 1; i--) {
        while (!st.empty() && A[i] > A[st.top()]) st.pop();
        R1[i] = (st.empty() ? N+1 : st.top());
        st.push(i);
    }

    SparseTableRMQ rmq(A, N+1);

    for (int i = 1; i <= N; i++) {
        L2[i] = searchLeft(L1[i], A[i], rmq);
        R2[i] = searchRight(R1[i], A[i], rmq);
    }

    PersistentBinaryTrie trie(N, 32);
    for (int i = 1; i <= N; i++) {
        trie.insert(i, i-1, A[i]);
    }

    int ans = INT_MIN;
    for (int i = 1; i <= N; i++) {
        if (L1[i] == 0 && R1[i] == N+1) continue;
        ans = max(ans, trie.traverse(L2[i], R1[i]-1, A[i]));
        ans = max(ans, trie.traverse(L1[i], R2[i]-1, A[i]));
    }
    printf("%d\n", ans);
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
    solve();

    return 0;
}
