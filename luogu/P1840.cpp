// https://www.luogu.org/problem/show?pid=1840
// Color the Axis_NOI导刊2011提高（05）

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
    SegmentTreeTD(const vector<V>& A, V zero_, D zeroUpdate_):
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
        return (node.update ? node.update * node.count : node.value);
    }

    V query(int node, int b, int e, int i, int j) const {
        assert(b <= e);
        if (i > e || j < b) {
            return zero;
        }

        if (M[node].update != zeroUpdate) {
            M[node].value = eval(M[node]);
            if (b != e) {
                M[2*node].update = M[node].update;
                M[2*node+1].update = M[node].update;
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
            M[node].update = d;
            return;
        }
        if (M[node].update != zeroUpdate) {
            M[2*node].update = M[node].update;
            M[2*node+1].update = M[node].update;
        }

        update(2*node, b, (b+e)/2, i, j, d);
        update(2*node+1, (b+e)/2+1, e, i, j, d);
        M[node].value = eval(M[2*node]) + eval(M[2*node+1]);
        M[node].update = zeroUpdate;
    }
};

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    vector<int> A(N, 0);
    SegmentTreeTD<int, int> st(A, 0, 0);

    for (int i = 0; i < M; i++) {
        int p, q;
        scanf("%d%d", &p, &q);
        st.update(p-1, q-1, 1);
        printf("%d\n", N - st.query(0, N-1));
    }
    return 0;
}
