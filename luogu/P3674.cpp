// https://www.luogu.org/problemnew/show/P3674
// 小清新人渣的本愿

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

class Mo {
    struct Query {
        int op;
        int l, r, id;
        int block_id;
        int x;

        bool operator < (const Query& other) const {
            return make_pair(block_id, r) < make_pair(other.block_id, other.r);
        }
    };

private:
    int N_, Q_;
    int currId_ = 0;
    int BLOCK_SIZE;
    Query *queries_;
    int *cnt_;
    bitset<MAXN+5> now1, now2;

    void move(int pos, int sign) {
        int x = elem[pos];
        if (sign == 1) {
            cnt_[x]++;
            if (cnt_[x] == 1) {
                now1[x] = 1;
                now2[MAXN-x] = 1;
            }
        }
        else {
            cnt_[x]--;
            if (cnt_[x] == 0) {
                now1[x] = 0;
                now2[MAXN-x] = 0;
            }
        }
    }

    void alloc() {
        queries_ = new Query[Q_]{};
        cnt_ = new int[MAXN]{};

        elem = new int[N_]{};
        ans  = new int[Q_]{};
    }

    void dealloc() {
        delete[] queries_;
        delete[] cnt_;

        delete[] elem;
        delete[] ans;
    }

public:
    int *elem;
    int *ans;

    Mo(int N, int Q): N_(N), Q_(Q) {
        BLOCK_SIZE = int(ceil(pow(N_, 0.5)));
        alloc();
    }

    ~Mo() {
        dealloc();
    }

    void addQuery(int op, int l, int r, int x) {
        queries_[currId_] = {op, l, r, currId_, l/BLOCK_SIZE, x};
        currId_++;
    }

    void solve() {
        sort(queries_, queries_+Q_);

        int l = 0, r = 0;
        // put other initializations here

        for (int i = 0; i < Q_; i++) {
            const Query& q = queries_[i];
            while (l > q.l) move(--l, 1);
            while (r < q.r) move(r++, 1);
            while (l < q.l) move(l++, -1);
            while (r > q.r) move(--r, -1);
            if (q.op == 1) {
                if ((now1 & (now1 << q.x)).any()) ans[q.id] = 1;
            } else if (q.op == 2) {
                if ((now1 & (now2 >> (MAXN-q.x))).any()) ans[q.id] = 1;
            } else {
                for (int j = 1; j*j <= q.x; j++) {
                    if (q.x % j == 0) {
                        if (now1[j] && now1[q.x/j]) {
                            ans[q.id] = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
};

int N, M;

int main() {
    scanf("%d%d", &N, &M);
    Mo mo(N, M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &mo.elem[i]);
    }
    for (int i = 0; i < M; i++) {
        int op, l, r, x;
        scanf("%d%d%d%d", &op, &l, &r, &x);
        l--;
        mo.addQuery(op, l, r, x);
    }

    mo.solve();
    for (int i = 0; i < M; i++) {
        printf(mo.ans[i] ? "hana\n": "bi\n");
    }

    return 0;
}
