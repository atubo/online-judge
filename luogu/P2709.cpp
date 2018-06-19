// https://www.luogu.org/problemnew/show/P2709
// 小B的询问

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
    int *cnt_;

    void move(int pos, int sign) {
        int &c = cnt_[elem[pos]];
        if (sign == 1) {
            currAns_ += 2*c+1;
            c++;
        } else {
            currAns_ -= 2*c-1;
            c--;
        }
    }

    void alloc() {
        queries_ = new Query[Q_]{};
        cnt_ = new int[K+1]{};

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
    int64_t currAns_ = 0;

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
    Mo mo(N, M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &mo.elem[i]);
    }

    for (int i = 0; i < M; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        l--;
        mo.addQuery(l, r);
    }
    mo.solve();
    for (int i = 0; i < M; i++) {
        printf("%lld\n", mo.ans[i]);
    }
    return 0;
}
