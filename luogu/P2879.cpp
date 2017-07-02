// https://www.luogu.org/problem/show?pid=2879
// [USACO07JAN]区间统计Tallest Cow

#include <bits/stdc++.h>
using namespace std;


/*
 This data structure supports
 1. Range query
 2. Range update

 Requirements:
 1. range update can be characterized by a parameter d
 2. range update should be associative (not necessarily commutative)
 3. we can accumulate the updates, i.e. U(d1)U(d2)...=U(d1+d2+..)
 4. A(U(x1, x2, .. , d)) = U'(A(x1, x2, ..), d, |x1, x2,..|)

 Client should provide three lambdas:
 1. combine (get aggregate from elements)
 2. accumulate (accumulate update parameters)
 3. apply (apply the update, may depend on set size)

 Template parameters (usually they are the same type):
 V - value type
 D - parameter type
*/
// TODO: pass zero values into Node
// may need to switch to vector
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

int main() {
    int N, I, H, R;
    scanf("%d%d%d%d", &N, &I, &H, &R);
    vector<int> A(N, 0);
    SegmentTreeTD<int> st(A, 0, 0,
                          [](int a, int b) {return a + b;},
                          [](int a, int b) {return a + b;},
                          [](int v, int d, int sz) {return v + d*sz;});

    for (int i = 0; i < R; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        if (a > b) swap(a, b);
        if (a < b-1) st.update(a+1, b-1, 1);
    }

    for (int i = 0; i < N; i++) {
        printf("%d\n", H-st.query(i, i));
    }

    return 0;
}
