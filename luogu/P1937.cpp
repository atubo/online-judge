// https://www.luogu.org/problem/show?pid=1937
// [USACO10MAR]仓配置Barn Allocation

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
            M[node].value = min(eval(M[2*node]), eval(M[2*node+1]));
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
        return node.value + node.update;
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

        return min(p1, p2);
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
        M[node].value = min(eval(M[2*node]), eval(M[2*node+1]));
        M[node].update = zeroUpdate;
    }
};

using PII = pair<int, int>;

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    vector<int> C(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &C[i]);
    }
    SegmentTreeTD<int> st(C, INT_MAX/4, 0);

    vector<PII> A(M);
    for (int i = 0; i < M; i++) {
        scanf("%d%d", &A[i].second, &A[i].first);
        A[i].second--;
        A[i].first--;
    }
    sort(A.begin(), A.end());

    int ret = 0;
    for (const PII& a: A) {
        if (st.query(a.second, a.first) > 0) {
            st.update(a.second, a.first, -1);
            ret++;
        }
    }

    printf("%d\n", ret);
    return 0;
}
