// http://codeforces.com/problemset/problem/242/E

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
#include <limits>
#include <vector>

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
        Node(): value(0), update(1),count(0) {}
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
        M.resize(msize);
        for (int i = 1; i < msize; i++) M[i].update = zeroUpdate;
        initialize(1, 0, N-1, A);
    }

    ~SegmentTreeTD() {
        //delete[] M;
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
    V query(int i, int j) {
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

    //Node* M;
    vector<Node> M;

    V eval(const Node& node) const {
        return apply(node.value, node.update, node.count);
    }

    V eval(const Node& node, D d, int count) const {
        return apply(node.value, d, count);
    }

    V query(int node, int b, int e, int i, int j) {
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


class Solution {
    using SegmentTree = SegmentTreeTD<int, int>;
private:
    int N;
    vector<int> A;
    vector<SegmentTree> segForest;
public:
    Solution() {
        cin >> N;
        A.resize(N);
        READ_ARRAY(N, A);
    }

    void solve() {
        auto comb = [](int a, int b) {return a + b;};
        auto accu = [](int a, int b) {return a * b;};
        auto appl = [](int v, int d, int n) {return (d == 1 ? v : n-v);};
        for (int i = 0; i < 32; i++) {
            vector<int> b(N);
            for (int j = 0; j < N; j++) {
                b[j] = (A[j] >> i) & 1;
            }
            segForest.push_back(SegmentTree(b, 0, 1, comb, accu, appl));
        }

        int M;
        cin >> M;
        for (int i = 0; i < M; i++) {
            int t, left, right;
            cin >> t >> left >> right;
            left--; right--;
            if (t == 1) {
                cout << query(left, right) << endl;
            } else {
                int x;
                cin >> x;
                update(left, right, x);
            }
        }
    }

    int64_t query(int left, int right) {
        int64_t ret = 0;
        int64_t carry = 0;
        for (int d = 0; d < 32; d++) {
            int64_t s = segForest[d].query(left, right) + carry;
            ret = ret | ((s & 1) << d);
            carry = (s >> 1);
        }
        ret = ret | (carry << 32);
        return ret;
    }

    void update(int left, int right, int x) {
        for (int d = 0; d < 32; d++) {
            segForest[d].update(left, right, ((x >> d) & 1) == 1 ? -1 : 1);
        }
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
