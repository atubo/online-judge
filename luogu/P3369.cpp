// https://www.luogu.org/problemnew/show/P3369
// 【模板】普通平衡树

#include <bits/stdc++.h>
using namespace std;

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
        if (t == 0) return INT_MIN;
        if (key_[t] >= x) return pred(sons_[t][0], x);
        return max(key_[t], pred(sons_[t][1], x));
    }

    int succ(int t, int x) const {
        if (t == 0) return INT_MAX;
        if (key_[t] <= x) return succ(sons_[t][1], x);
        return min(key_[t], succ(sons_[t][0], x));
    }
};

int N;

int main() {
    scanf("%d", &N);
    Sbt sbt(N);
    for (int i = 0; i < N; i++) {
        int op, x;
        scanf("%d%d", &op, &x);
        if (op == 1) {
            sbt.insert(x);
        } else if (op == 2) {
            sbt.del(x);
        } else if (op == 3) {
            printf("%d\n", sbt.rank(x)+1);
        } else if (op == 4) {
            printf("%d\n", sbt.findByOrder(x-1));
        } else if (op == 5) {
            printf("%d\n", sbt.pred(x));
        } else {
            printf("%d\n", sbt.succ(x));
        }
    }

    return 0;
}
