// https://www.luogu.org/problemnew/show/P4462
// [CQOI2018]异或序列

#include <bits/stdc++.h>
using namespace std;

int K;

class Mo {
    struct Query {
        int l, r, id;
        int block_id;

        bool operator < (const Query& other) const {
            return make_pair(block_id, r) < make_pair(other.block_id, other.r);
        }
    };

private:
    int N_, Q_;
    int currId_ = 0;
    int BLOCK_SIZE;
    Query *queries_;
    int64_t currAns_ = 0;
    int *cnt_;

    void move(int pos, int sign) {
        int x = elem[pos];
        if (sign == 1) {
            currAns_ += cnt_[x ^ K];
            cnt_[x]++;
        } else {
            int cnt = cnt_[x ^ K];
            currAns_ -= (cnt - (K == 0));
            cnt_[x]--;
        }
    }

    void alloc() {
        queries_ = new Query[Q_]{};
        cnt_ = new int[1<<15]{};

        elem = new int[N_]{};
        ans  = new int64_t[Q_]{};
    }

    void dealloc() {
        delete[] queries_;
        delete[] cnt_;

        delete[] elem;
        delete[] ans;
    }

public:
    int *elem;
    int64_t *ans;

    Mo(int N, int Q): N_(N), Q_(Q) {
        BLOCK_SIZE = int(ceil(pow(N_, 0.5)));
        alloc();
    }

    ~Mo() {
        dealloc();
    }

    void addQuery(int l, int r) {
        queries_[currId_] = {l, r, currId_, l/BLOCK_SIZE};
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
            ans[q.id] = currAns_;
        }
    }
};

int N, M;

int main() {
    scanf("%d%d%d", &N, &M, &K);
    Mo mo(N+1, M);
    mo.elem[0] = 0;
    for (int i = 1; i <= N; i++) {
        int x;
        scanf("%d", &x);
        mo.elem[i] = x ^ mo.elem[i-1];
    }
    for (int i = 0; i < M; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        l--;
        mo.addQuery(l, r+1);
    }
    mo.solve();
    for (int i = 0; i < M; i++) {
        printf("%lld\n", mo.ans[i]);
    }
    return 0;
}
