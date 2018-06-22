// https://www.luogu.org/problemnew/show/P1494
// [国家集训队]小Z的袜子

#include <bits/stdc++.h>
using namespace std;


int64_t gcd(int64_t a, int64_t b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

struct Ratio {
    int64_t a, b;
};

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

    int total_ = 0;
    int64_t sameColor_ = 0;

    void move(int pos, int sign) {
        int x = elem[pos];
        int &c = cnt_[x];
        if (sign == 1) {
            total_++;
            sameColor_ += c++;
        } else {
            total_--;
            sameColor_ -= --c;
        }
    }

    void alloc() {
        queries_ = new Query[Q_]{};
        cnt_ = new int[N_+1]{};

        elem = new int[N_]{};
        ans  = new Ratio[Q_]{};
    }

    void dealloc() {
        delete[] queries_;
        delete[] cnt_;

        delete[] elem;
        delete[] ans;
    }

    Ratio reduce(int64_t a, int64_t b) {
        if (b == 0) return {0, 1};
        int64_t g = gcd(a, b);
        return {a/g, b/g};
    }

public:
    int *elem;
    Ratio *ans;

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
            ans[q.id] = reduce(sameColor_,
                               int64_t(total_)*(total_-1)/2);
        }
    }
};

int N, M;

int main() {
    scanf("%d%d", &N, &M);
    Mo mo(N, M);
    for (int i = 0; i < N; i++) {
        int c;
        scanf("%d", &c);
        mo.elem[i] = c-1;
    }
    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--;
        mo.addQuery(a, b);
    }
    mo.solve();
    for (int i = 0; i < M; i++) {
        printf("%lld/%lld\n", mo.ans[i].a, mo.ans[i].b);
    }
    return 0;
}
