// https://www.luogu.org/problemnew/show/P4137
// Rmq Problem / mex

#include <bits/stdc++.h>
using namespace std;

class PersistentSegmentTree {
public:
    struct Node {
        // L and R are indices of its children
        // real left and right boundaries are not kept in the node
        // to save memory
        int L, R;
        int last;

        Node(): L(0), R(0), last(0) {}
    };

    int N; // number of positions, index is 1-based
    int M; // number of weights, index is 0-based
    int *root;
    Node *T;
    int T_cnt = 1;

    PersistentSegmentTree(int N_, int M_): N(N_), M(M_) {
        root = new int[N+1]{};
        T = new Node[(N+1) * int(log2(M)+2)]{};
    }

    ~PersistentSegmentTree() {
        delete[] root;
        delete[] T;
    }

    // for user's convenience
    void insert(int currRootIndex, int prevRootIndex, int x, int t) {
        root[currRootIndex] = root[prevRootIndex];
        insert(root[currRootIndex], x, t, 0, M-1);
    }

    void solve(int l, int r) {
        Node node = T[root[r]];
        int left = 0, right = M-1;
        while (left < right) {
            int mid = (left + right) / 2;
            if (T[node.L].last < l) {
                right = mid;
                node = T[node.L];
            } else {
                left = mid + 1;
                node = T[node.R];
            }
        }
        printf("%d\n", left);
    }

private:
    // insert a new weight node x with value t
    // current range is [l, r]
    void insert(int &now, int x, int t, int l, int r) {
        T[T_cnt++] = T[now];
        now = T_cnt-1;
        if (l == r) {
            T[now].last = t;
            return;
        }
        int mid = (l + r) / 2;
        if (x <= mid) insert(T[now].L, x, t, l, mid);
        else          insert(T[now].R, x, t, mid+1, r);
        T[now].last = min(T[T[now].L].last, T[T[now].R].last);
    }
};

const int MAXN = 200010;
int N, M;

int main() {
    scanf("%d%d", &N, &M);
    PersistentSegmentTree pst(N, N+1);
    for (int i = 1; i <= N; i++) {
        int x;
        scanf("%d", &x);
        x = min(x, N);
        pst.insert(i, i-1, x, i);
    }

    for (int i = 0; i < M; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        pst.solve(l, r);
    }

    return 0;
}
