// http://codeforces.com/problemset/problem/292/E

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define READ_ARRAY(N, A) \
    for (int i = 0; i < N; i++) {\
        cin >> A[i];\
    }

template <typename T>
void printVector(const vector<T>& A) {
    for (const T& x: A) {
        cout << x << " ";
    }
    cout << endl;
}

#include <cassert>
#include <functional>
#include <inttypes.h>
#include <climits>
#include <vector>

using namespace std;

vector<int> SRC, DST;

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
                  function<D(D, D)> accu_):
        N(A.size()), zero(zero_), zeroUpdate(zeroUpdate_),
        accu(accu_) {
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
            M[node].value = INT_MAX;
            M[node].count = M[2*node].count + M[2*node+1].count;
        }
    }

    // i, j inclusive
    V query(int i) const {
        return query(1, 0, N-1, i, i);
    }

    void update(int i, int j, D d) {
        update(1, 0, N-1, i, j, d);
    }

private:
    const int N;
    const V zero;   // zero element for combine
    const D zeroUpdate; // zero for update

    function<D(D, D)> accu;

    Node* M;

    V query(int node, int b, int e, int i, int j) const {
        assert(b <= e);
        assert(i == j);
        if (i > e || j < b) {
            return zero;
        }

        if (M[node].update != zeroUpdate) {
            if (b != e) {
                M[2*node].update = accu(M[node].update, M[2*node].update);
                M[2*node+1].update = accu(M[node].update, M[2*node+1].update);
                M[node].update = zeroUpdate;
            }
        }

        if (b >= i && e <= j) {
            assert(b == e);
            return M[node].update == zeroUpdate ?
                DST.at(M[node].value) :
                SRC.at(M[node].value + M[node].update);
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
            M[node].update = accu(d, M[node].update);
            return;
        }
        if (M[node].update != zeroUpdate) {
            M[2*node].update = accu(M[node].update, M[2*node].update);
            M[2*node+1].update = accu(M[node].update, M[2*node+1].update);
        }

        update(2*node, b, (b+e)/2, i, j, d);
        update(2*node+1, (b+e)/2+1, e, i, j, d);
        M[node].update = zeroUpdate;
    }
};

class Solution {
private:
    int N, M;
public:
    Solution() {
        cin >> N >> M;
        SRC.resize(N);
        DST.resize(N);
        READ_ARRAY(N, SRC);
        READ_ARRAY(N, DST);
    }

    void solve() {
        using SegmentTree = SegmentTreeTD<int, int>;

        auto accu = [](int a, int b) {return a;};
        vector<int> idx(N);
        iota(idx.begin(), idx.end(), 0);
        SegmentTree st(idx, 0, INT_MAX, accu);

        for (int m = 0; m < M; m++) {
            int t;
            cin >> t;
            if (t == 1) {
                int x, y, k;
                cin >> x >> y >> k;
                x--; y--;
                st.update(y, y+k-1, x-y);
            } else {
                int x;
                cin >> x;
                cout << st.query(x-1) << endl;
            }
        }
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
