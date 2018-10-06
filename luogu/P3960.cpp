// https://www.luogu.org/problemnew/show/P3960
// 列队

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag,
        tree_order_statistics_node_update> ordered_set;

// internal arrays are 1-based
// assume no duplicated elements
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

    int rank(int v) const {
        return rank(root_, v);
    }

    inline bool check(int t, int k, int c) const {
        return key_[t] - (k + size_[sons_[t][0]] + 1) >= c;
    }

    int search(int c) const {
        if (size_[root_] == 0) return c;
        int t = root_;
        int k = 0;
        while (t) {
            if (!check(t, k, c)) {
                k += size_[sons_[t][0]] + 1;
                t = sons_[t][1];
            } else {
                t = sons_[t][0];
            }
        }
        return c + k;
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
        if (t == 0) return 0;
        if (v == key_[t]) return size_[sons_[t][0]];
        if (v < key_[t]) return rank(sons_[t][0], v);
        return 1 + size_[sons_[t][0]] + rank(sons_[t][1], v);
    }
};

const int MAXQ = 300010;
int N, M, Q;
vector<vector<int64_t>> tails;
vector<int64_t> back;
struct Query {
    int x, y;
} queries[MAXQ];

int64_t id(int x, int y) {
    return 1LL*x*M + (y+1);
}

int64_t pushLastCol(int x, int64_t nid, Sbt &sbt) {
    int x2 = sbt.search(x);
    int64_t ret = (x2 < N ? id(x2, M-1) : back[x2-N]);
    back.push_back(nid);
    sbt.insert(x2);
    return ret;
}

int64_t rotateLastCol(int x, Sbt &sbt) {
    int x2 = sbt.search(x);
    int64_t ret = (x2 < N ? id(x2, M-1) : back[x2-N]);
    back.push_back(ret);
    sbt.insert(x2);
    return ret;
}

int64_t solve(int x, int y, Sbt *sbtx, Sbt &sbty) {
    int64_t ret = -1;
    if (y == M-1) {
        ret = rotateLastCol(x, sbty);
    } else {
        int y2 = sbtx->search(y);
        ret = (y2 < M-1 ? id(x, y2) : tails[x][y2-M+1]);
        tails[x].push_back(pushLastCol(x, ret, sbty));
        sbtx->insert(y2);
    }
    return ret;
}

int main() {
    scanf("%d%d%d", &N, &M, &Q);
    tails.resize(N);
    Sbt sbty(Q);
    vector<int> cnt(N);
    for (int i = 0; i < Q; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--; y--;
        queries[i] = {x, y};
        if (y != M-1) cnt[x]++;
    }
    vector<Sbt*> sbtx(N);
    for (int i = 0; i < N; i++) {
        if (cnt[i] > 0) sbtx[i] = new Sbt(cnt[i]);
    }
    for (int i = 0; i < Q; i++) {
        int x = queries[i].x, y = queries[i].y;
        int64_t ret = solve(x, y, sbtx[x], sbty);
        printf("%ld\n", ret);
    }
    return 0;
}
