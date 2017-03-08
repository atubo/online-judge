// https://www.luogu.org/problem/show?pid=1712
// 区间

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
    SegmentTreeTD(const vector<V>& A, V zero_, D zeroUpdate_,
                  function<V(V, V)> combine_,
                  function<D(D, D)> accu_,
                  function<V(V, D, int)> apply_):
        N(A.size()), zero(zero_), zeroUpdate(zeroUpdate_),
        combine(combine_), accu(accu_), apply(apply_) {
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
            M[node].value = combine(eval(M[2*node]), eval(M[2*node+1]));
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

    function<V(V, V)> combine;
    function<D(D, D)> accu;
    function<V(V, D, int)> apply;

    Node* M;

    V eval(const Node& node) const {
        return apply(node.value, node.update, node.count);
    }

    V query(int node, int b, int e, int i, int j) const {
        assert(b <= e);
        if (i > e || j < b) {
            return zero;
        }

        if (M[node].update != zeroUpdate) {
            M[node].value = eval(M[node]);
            if (b != e) {
                M[2*node].update = accu(M[node].update, M[2*node].update);
                M[2*node+1].update = accu(M[node].update, M[2*node+1].update);
            }
            M[node].update = zeroUpdate;
        }

        if (b >= i && e <= j) {
            return M[node].value;
        }

        V p1 = query(2*node, b, (b+e)/2, i, j);
        V p2 = query(2*node+1, (b+e)/2+1, e, i, j);

        return combine(p1, p2);
    }

    void update(int node, int b, int e, int i, int j, D d) {
        if (i > e || j < b) {
            return;
        }
        if (b >= i && e <= j) {
            M[node].update = accu(d, M[node].update);
            return;
        }
        if (M[node].update != zeroUpdate) {
            M[2*node].update = accu(M[node].update, M[2*node].update);
            M[2*node+1].update = accu(M[node].update, M[2*node+1].update);
        }

        update(2*node, b, (b+e)/2, i, j, d);
        update(2*node+1, (b+e)/2+1, e, i, j, d);
        M[node].value = combine(eval(M[2*node]), eval(M[2*node+1]));
        M[node].update = zeroUpdate;
    }
};

struct Interval {
    int id;
    int length;
    int left, right;

    bool operator < (const Interval& other) const {
        if (length < other.length) return true;
        if (length > other.length) return false;
        return (id < other.id);
    }
} intervals[500010];

int N, M;

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        intervals[i].id = i;
        intervals[i].left = a;
        intervals[i].right = b;
        intervals[i].length = b - a;
    }

    sort(intervals, intervals + N);

    vector<int> B(2*N);
    for (int i = 0; i < N; i++) {
        B[2*i] = intervals[i].left;
        B[2*i+1] = intervals[i].right;
    }
    sort(B.begin(), B.end());
    B.erase(unique(B.begin(), B.end()), B.end());

    int L = 0;
    for (int i = 0; i < N; i++) {
        intervals[i].left = lower_bound(B.begin(), B.end(), intervals[i].left) -
                            B.begin();
        intervals[i].right = lower_bound(B.begin(), B.end(), intervals[i].right) -
                             B.begin();
        L = max(L, max(intervals[i].left, intervals[i].right));
    }

    vector<int> C(L+1, 0);
    auto combine = [](int a, int b) {return max(a, b);};
    auto accu = [](int a, int b) {return a + b;};
    auto apply = [](int a, int b, int n) {return a + b;};

    SegmentTreeTD<int> st(C, 0, 0, combine, accu, apply);
    
    int p = 0, q = -1, ret = INT_MAX;
    while (true) {
        while (q < N && st.query(0, L) < M) {
            const auto& itv = intervals[++q];
            st.update(itv.left, itv.right, 1);
        }
        if (q == N) break;
        while (st.query(0, L) >= M) {
            ret = min(ret, intervals[q].length - intervals[p].length);
            st.update(intervals[p].left, intervals[p].right, -1);
            p++;
        }
    }

    printf("%d\n", ret == INT_MAX ? -1 : ret);
    return 0;
}
