// https://www.luogu.org/problemnew/show/P4559
// [JSOI2018]列队

#include <bits/stdc++.h>
using namespace std;

#define MAX(a, b) ((a) >= (b) ? a : b)
#define MIN(a, b) ((a) <= (b) ? a : b)

class Rmq {
public:
    Rmq(int *a, int n): n_(n), maxb_(log2(n)+1) {
        alloc();
        preprocess(a);
    }

    ~Rmq() {
        dealloc();
    }

    int rmq(int u, int v) const {
        int j = log_[v-u+1];
        return MAX(st_[j][u], st_[j][v+1-(1<<j)]);
    }

private:
    int n_;
    int maxb_;
    int **st_;
    int *log_;

    void alloc() {
        st_ = new int*[maxb_]{};
        for (int i = 0; i < maxb_; i++) {
            st_[i] = new int[n_]{};
        }
        log_ = new int[n_]{};
    }

    void dealloc() {
        delete[] log_;
        for (int i = 0; i < maxb_; i++) {
            delete[] st_[i];
        }
        delete[] st_;
    }

    void preprocess(int *a) {
        for (int i = 2; i < n_; i++) log_[i] = log_[i>>1] + 1;

        for (int i = 0; i < n_; i++) {
            st_[0][i] = a[i];
        }

        for (int j = 1; j < maxb_; j++) {
            for (int i = 0; i + (1<<j) - 1 < n_; i++) {
                st_[j][i] = MAX(st_[j-1][i], st_[j-1][i+(1<<(j-1))]);
            }
        }
    }
};

class Rmq2 {
public:
    Rmq2(int *a, int n): n_(n), maxb_(log2(n)+1) {
        alloc();
        preprocess(a);
    }

    ~Rmq2() {
        dealloc();
    }

    int rmq(int u, int v) const {
        int j = log_[v-u+1];
        return MIN(st_[j][u], st_[j][v+1-(1<<j)]);
    }

private:
    int n_;
    int maxb_;
    int **st_;
    int *log_;

    void alloc() {
        st_ = new int*[maxb_]{};
        for (int i = 0; i < maxb_; i++) {
            st_[i] = new int[n_]{};
        }
        log_ = new int[n_]{};
    }

    void dealloc() {
        delete[] log_;
        for (int i = 0; i < maxb_; i++) {
            delete[] st_[i];
        }
        delete[] st_;
    }

    void preprocess(int *a) {
        for (int i = 2; i < n_; i++) log_[i] = log_[i>>1] + 1;

        for (int i = 0; i < n_; i++) {
            st_[0][i] = a[i];
        }

        for (int j = 1; j < maxb_; j++) {
            for (int i = 0; i + (1<<j) - 1 < n_; i++) {
                st_[j][i] = MIN(st_[j-1][i], st_[j-1][i+(1<<(j-1))]);
            }
        }
    }
};

struct Node {
    // L and R are indices of its children
    // real left and right boundaries are not kept in the node
    // to save memory
    int L, R;
    int cnt;
    int64_t sum;
} nodes[500010*21];

class PersistentSegmentTree {
public:
    int N; // number of positions, index is 1-based
    int M; // number of weights, index is 0-based
    int *root;
    Node *T;
    int T_cnt = 1;

    PersistentSegmentTree(int N_, int M_): N(N_), M(M_) {
        root = new int[N+1]{};
        //T = new Node[(N+1) * int(log2(M)+2)]{};
        T = nodes;
    }

    ~PersistentSegmentTree() {
        delete[] root;
        //delete[] T;
    }

    // for user's convenience
    void insert(int currRootIndex, int prevRootIndex, int x, int t) {
        root[currRootIndex] = root[prevRootIndex];
        insert(root[currRootIndex], x, t, 0, M-1);
    }

    int64_t solve(int left, int right, int k, const Rmq &rmq,
                  const Rmq2 &rmq2) const {
        int l = rmq2.rmq(left, right), r = rmq.rmq(left, right);
        int a = k, b = k + right - left;
        int pivot = findPivot(root[left-1], root[right], l, r, a, b);
        int n1 = 0;
        if (l <= pivot-1) {
            n1 = query(root[left-1], root[right], pivot-1, 0, M-1);
        }
        int64_t ret = 1LL*n1*a + 1LL*n1*(n1-1)/2;
        int n2 = right - left + 1 - n1;
        ret -= 1LL*n2*(a+n1) + 1LL*n2*(n2-1)/2;
        if (pivot <= l) ret += query2(root[left-1], root[right], r, 0, M-1);
        else if (pivot <= r) {
            ret -= 2LL*query2(root[left-1], root[right], pivot-1, 0, M-1);
            ret += query2(root[left-1], root[right], r, 0, M-1);
        } else {
            ret -= query2(root[left-1], root[right], r, 0, M-1);
        }
        return ret;
    }

    int findPivot(int root1, int root2, int l, int r, int a, int b) const {
        if (l >= a) return l;
        if (r <= b) return r+1;
        return findPivot2(root1, root2, 0, M-1, a, b);
    }

    int findPivot2(int node1, int node2, int l, int r, int a, int b) const {
        if (l == r) return l;
        int mid = (l + r) >> 1;
        int L1 = T[node1].L, L2 = T[node2].L;
        int R1 = T[node1].R, R2 = T[node2].R;
        int x = T[L2].cnt - T[L1].cnt;
        if (mid < a+x-1) {
            return findPivot2(R1, R2, mid+1, r, a+x, b);
        } else {
            return findPivot2(L1, L2, l, mid, a, a+x-1);
        }
    }

private:
    // insert a new weight node x with value t
    // current range is [l, r]
    void insert(int &now, int x, int t, int l, int r) {
        T[T_cnt++] = {T[now].L, T[now].R, T[now].cnt+t, T[now].sum+x};
        now = T_cnt-1;
        if (l == r) return;
        int mid = (l + r) >> 1;
        if (x <= mid) insert(T[now].L, x, t, l, mid);
        else          insert(T[now].R, x, t, mid+1, r);
    }

    int query(int node1, int node2, int end,
               int l, int r) const {
        if (r == end) return T[node2].cnt - T[node1].cnt;
        int L1 = T[node1].L, L2 = T[node2].L;
        int R1 = T[node1].R, R2 = T[node2].R;
        int mid = (l + r) / 2;
        if (end <= mid) return query(L1, L2, end, l, mid);
        return T[L2].cnt - T[L1].cnt + query(R1, R2, end, mid+1, r);

    }

    int64_t query2(int node1, int node2, int end, int l, int r) const {
        if (r == end) return T[node2].sum - T[node1].sum;
        int L1 = T[node1].L, L2 = T[node2].L;
        int R1 = T[node1].R, R2 = T[node2].R;
        int mid = (l + r) / 2;
        if (end <= mid) return query2(L1, L2, end, l, mid);
        return T[L2].sum - T[L1].sum + query2(R1, R2, end, mid+1, r);
    }
};

const int MAXN = 500010;
int N, M;
int A[MAXN];

int main() {
    scanf("%d%d", &N, &M);
    PersistentSegmentTree pst(N, 1000001);
    for (int i = 1; i <= N; i++) {
        int a;
        scanf("%d", &a);
        A[i] = a;
        pst.insert(i, i-1, a, 1);
    }

    Rmq rmq(A, N+1);
    Rmq2 rmq2(A, N+1);

    for (int i = 0; i < M; i++) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%ld\n", pst.solve(l, r, k, rmq, rmq2));
    }

    return 0;
}
