// https://www.luogu.org/problem/P3721
// [AH2017/HNOI2017]单旋

#include <bits/stdc++.h>
using namespace std;

// note it's 1-indexed
class SegmentTree {
    int N;
    int64_t *val;
    int *lazy;

public:
    SegmentTree(int N_): N(N_) {
        val = new int64_t[4*N+1]{};
        lazy = new int[4*N+1]{};
    }

    ~SegmentTree() {
        delete[] val;
        delete[] lazy;
    }
    // add t to range [a, b]
    void update(int t, int a, int b) {
        update(1, t, 1, N, a, b);
    }

    void set(int t, int a) {
        int prev = query(a);
        update(t-prev, a, a);
    }

    int64_t query(int a) {
        if (a == 0) return 0;
        return query(1, 1, N, a);
    }

private:
    // add t to range [a, b], current node range is [l, r]
    void update(int k, int t, int l, int r, int a, int b) {
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            val[k] += t * (r-l+1);
            lazy[k] += t;
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   t, l, mid, a, b);
        if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
        val[k] = val[2*k] + val[2*k+1];
    }

    void pushDown(int k, int l, int r) {
        if (!lazy[k] || l == r) return;
        lazy[2*k] += lazy[k];
        lazy[2*k+1] += lazy[k];
        int mid = (l + r) / 2;
        val[2*k] += (mid - l + 1) * lazy[k];
        val[2*k+1] += (r - mid) * lazy[k];
        lazy[k] = 0;
    }

    int64_t query(int k, int l, int r, int a) {
        pushDown(k, l, r);
        if (l == r) return val[k];
        int mid = (l + r) / 2;
        if (a <= mid) return query(2*k, l, mid, a);
        return query(2*k+1, mid+1, r, a);
    }
};


class Sbt {
public:
    Sbt(int n): n_(n+1) {
        alloc();
    }

    ~Sbt() {
        dealloc();
    }

    void insert(int v) {
        insert(root_, v);
    }

    void del(int key) {
        del(root_, key);
    }

    int first() const {
        return findByOrder(0);
    }

    int last() const {
        return findByOrder(size_[root_]-1);
    }


    int rank(int v) const {
        return rank(root_, v);
    }

    int findByOrder(int k) const {
        return findByOrder(root_, k);
    }

    int pred(int x) const {
        // find predecessor
        return pred(root_, x);
    }

    int succ(int x) const {
        // find successor
        return succ(root_, x);
    }

private:
    int n_;
    int *key_;
    int *size_;
    int **sons_;
    int tail_ = 0;
    int root_ = 0;

    void alloc() {
        key_ = new int[n_]{};
        size_ = new int[n_]{};
        sons_ = new int*[n_]{};
        for (int i = 0; i < n_; i++) sons_[i] = new int[2]{};
    }

    void dealloc() {
        delete[] key_;
        delete[] size_;
        for (int i = 0; i < n_; i++) delete[] sons_[i];
        delete[] sons_;
    }

    void rotate(int &t, int w) {
        int k = sons_[t][1-w];
        if (!k) return;
        sons_[t][1-w] = sons_[k][w];
        sons_[k][w] = t;
        size_[k] = size_[t];
        size_[t] = size_[sons_[t][0]] + size_[sons_[t][1]] + 1;
        t = k;
    }

    void maintain(int &t, bool flag) {
        if (!t) return;
        if (!flag) {
            if (size_[sons_[sons_[t][0]][0]] > size_[sons_[t][1]]) {
                rotate(t, 1);
            } else if (size_[sons_[sons_[t][0]][1]] > size_[sons_[t][1]]) {
                rotate(sons_[t][0], 0);
                rotate(t, 1);
            } else {
                return;
            }
        } else {
            if (size_[sons_[sons_[t][1]][1]] > size_[sons_[t][0]]) {
                rotate(t, 0);
            } else if (size_[sons_[sons_[t][1]][0]] > size_[sons_[t][0]]) {
                rotate(sons_[t][1], 1);
                rotate(t, 0);
            } else {
                return;
            }
        }

        maintain(sons_[t][0], false);
        maintain(sons_[t][1], true);
        maintain(t, false);
        maintain(t, true);
    }

    void insert(int &t, int v) {
        if (!size_[t]) {
            int pos = ++tail_;
            key_[pos] = v;
            size_[pos] = 1;
            sons_[pos][0] = sons_[pos][1] = 0;
            t = pos;
        } else {
            size_[t]++;
            if (v < key_[t]) insert(sons_[t][0], v);
            else insert(sons_[t][1], v);
            maintain(t, v>=key_[t]);
        }
    }

    int rank(int t, int v) const {
        // if there are duplicates, return the minimum rank
        if (t == 0) return 0;
        if (v <= key_[t]) return rank(sons_[t][0], v);
        return 1 + size_[sons_[t][0]] + rank(sons_[t][1], v);
    }

    int findByOrder(int t, int k) const {
        // k starts from 0
        int sl = size_[sons_[t][0]];
        if (k == sl) return key_[t];
        if (k < sl) return findByOrder(sons_[t][0], k);
        return findByOrder(sons_[t][1], k-sl-1);
    }

    int del(int &t, int v) {
        size_[t]--;
        if (v == key_[t] || (v < key_[t] && sons_[t][0] == 0) ||
            (v > key_[t] && sons_[t][1] == 0)) {
            int ret = key_[t];
            if (sons_[t][0] == 0 || sons_[t][1] == 0) {
                t = sons_[t][0] + sons_[t][1];
            } else {
                key_[t] = del(sons_[t][0], key_[t]+1);
            }
            return ret;
        } else {
            if (v < key_[t]) return del(sons_[t][0], v);
            else return del(sons_[t][1], v);
        }
    }

    int pred(int t, int x) const {
        if (t == 0) return 0;
        if (key_[t] >= x) return pred(sons_[t][0], x);
        return max(key_[t], pred(sons_[t][1], x));
    }

    int succ(int t, int x) const {
        if (t == 0) return n_;
        if (key_[t] <= x) return succ(sons_[t][1], x);
        return min(key_[t], succ(sons_[t][0], x));
    }
};

const int MAXM = 100010;
int M;
struct Op {
    int c, key;
} op[MAXM];

class SpalyTree {
    int n_;
    Sbt sbt_;
    SegmentTree st_;
    int *fa_;
    int *ch_[2];
    int root_ = 0;

    void alloc() {
        fa_ = new int[n_+2]{};
        for (int i = 0; i < 2; i++) {
            ch_[i] = new int[n_+2];
        }
    }

    void dealloc() {
        delete[] fa_;
        for (int i = 0; i < 2; i++) {
            delete[] ch_[i];
        }
    }

    int add(int key, int f, int c) {
        fa_[key] = f;
        if (f) ch_[c][f] = key;
        sbt_.insert(key);
        int d = st_.query(f);
        st_.set(d+1, key);
        return d+1;
    }

    void connect(int y, int x, int c) {
        ch_[c][x] = y;
        if (y) fa_[y] = x;
    }

    void cutRoot(int c) {
        int x = ch_[c][root_];
        root_ = x;
        fa_[root_] = 0;
    }

public:
    SpalyTree(int n): n_(n), sbt_(n_), st_(n_) {
        alloc();
    }

    ~SpalyTree() {
        dealloc();
    }

    int insert(int key) {
        if (root_ == 0) {
            root_ = key;
            add(key, 0, 1);
            return 1;
        }
        int prev = sbt_.pred(key);
        int next = sbt_.succ(key);
        int ret = 0;
        int dp = prev == 0 ? 0 : st_.query(prev);
        int dn = next == n_+1 ? 0 : st_.query(next);
        if (dn > dp) {
            ret = add(key, next, 0);
        } else {
            ret = add(key, prev, 1);
        }
        return ret;
    }

    int spalyMin() {
        int x = sbt_.first();
        int ret = st_.query(x);
        int r = root_;
        if (x == r) return ret;
        int y = ch_[1][x];
        int f = fa_[x];
        st_.update(1, f, n_);
        root_ = x;
        st_.set(1, x);
        connect(y, f, 0);
        connect(r, x, 1);
        return ret;
    }

    int spalyMax() {
        int x = sbt_.last();
        int ret = st_.query(x);
        int r = root_;
        if (x == r) return ret;
        int y = ch_[0][x];
        int f = fa_[x];
        st_.update(1, 1, f);
        root_ = x;
        st_.set(1, x);
        connect(y, f, 1);
        connect(r, x, 0);
        return ret;
    }

    int delMin() {
        int ret = spalyMin();
        int a = sbt_.first();
        int b = sbt_.last();
        int r = root_;
        st_.update(-1, a, b);
        cutRoot(1);
        sbt_.del(r);
        return ret;
    }

    int delMax() {
        int ret = spalyMax();
        int a = sbt_.first();
        int b = sbt_.last();
        int r = root_;
        st_.update(-1, a, b);
        cutRoot(0);
        sbt_.del(r);
        return ret;
    }
};


int main() {
    scanf("%d", &M);
    vector<int> sorted;

    for (int i = 0; i < M; i++) {
        int c, key;
        scanf("%d", &c);
        op[i].c = c;
        if (c == 1) {
            scanf("%d", &key);
            op[i].key = key;
            sorted.push_back(key);
        }
    }

    sort(sorted.begin(), sorted.end());
    for (int i = 0; i < M; i++) {
        if (op[i].c == 1) {
            op[i].key = lower_bound(sorted.begin(),
                                    sorted.end(),
                                    op[i].key)
                - sorted.begin() + 1;
        }
    }

    SpalyTree st(M);
    for (int i = 0; i < M; i++) {
        int ret;
        switch (op[i].c) {
            case 1:
                ret = st.insert(op[i].key);
                break;
            case 2:
                ret = st.spalyMin();
                break;
            case 3:
                ret = st.spalyMax();
                break;
            case 4:
                ret = st.delMin();
                break;
            case 5:
                ret = st.delMax();
                break;
        }
        printf("%d\n", ret);
    }

    return 0;
}
