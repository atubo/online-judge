// https://www.luogu.org/problem/show?pid=2023
// [AHOI2009]维护序列
#include <stdint.h>
#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;

typedef pair<int64_t, int64_t> PII;
typedef int64_t V;
typedef PII D;

int N;
int64_t P;

int64_t add(int64_t a, int64_t b) {
    return (a + b) % P;
}

int64_t mul(int64_t a, int64_t b) {
    return (a * b) % P;
}

PII accu(const PII& p1, const PII& p2) {
    int64_t p = mul(p2.first, p1.first);
    int64_t q = add(mul(p2.second, p1.first), p1.second);
    return make_pair(p, q);
}


class SegmentTreeTD {
    struct Node {
        Node(): value(0), update(1, 0),count(0) {}
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
            M[node].value = add(eval(M[2*node]), eval(M[2*node+1]));
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
        return add(mul(node.value, node.update.first),
                   mul(node.count, node.update.second));
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

        return add(p1, p2);
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
        M[node].value = add(eval(M[2*node]), eval(M[2*node+1]));
        M[node].update = zeroUpdate;
    }
};

int main() {
    scanf("%d %lld", &N, &P);
    vector<int64_t> A(N);
    for (int i = 0; i < N; i++) {
        scanf("%lld", &A[i]);
    }
    SegmentTreeTD st(A, 0, make_pair(1, 0));
    int M;
    scanf("%d", &M);
    int op, a, b, c;
    while (M--) {
        scanf("%d %d %d", &op, &a, &b);
        a--; b--;
        if (op == 1) {
            scanf("%d", &c);
            st.update(a, b, make_pair(c, 0));
        } else if (op == 2) {
            scanf("%d", &c);
            st.update(a, b, make_pair(1, c));
        } else {
            printf("%lld\n", st.query(a, b));
        }
    }

    return 0;
}
