// https://www.luogu.org/problemnew/show/P3709
// 大爷的字符串题

#include <bits/stdc++.h>
using namespace std;

class Mo {
    struct Query {
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
    int *freq_;
    int maxFreq_ = 0;

    void move(int pos, int sign) {
        int x = elem[pos];
        int &c = cnt_[x];
        if (sign == 1) {
            freq_[c+1]++;
            if (c > 0) freq_[c]--;
            if (maxFreq_ == c) maxFreq_++;
            c++;
        } else {
            freq_[c]--;
            if (c > 1) freq_[c-1]++;
            if (freq_[c] == 0 && maxFreq_ == c) maxFreq_--;
            c--;
        }
    }

    void alloc() {
        queries_ = new Query[Q_]{};
        cnt_ = new int[N_+1]{};
        freq_ = new int[N_+1]{};

        elem = new int[N_]{};
        ans  = new int[Q_]{};
    }

    void dealloc() {
        delete[] queries_;
        delete[] cnt_;
        delete[] freq_;

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

    void addQuery(int l, int r, int x) {
        queries_[currId_] = {l, r, currId_, l/BLOCK_SIZE, x};
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
            ans[q.id] = maxFreq_;
        }
    }
};

const int MAXN = 200010;
int N, M;
int A[MAXN], B[MAXN];

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        B[i] = A[i];
    }
    sort(B, B+N);
    int *endp = unique(B, B+N);

    Mo mo(N, M);
    for (int i = 0; i < N; i++) {
        mo.elem[i] = lower_bound(B, endp, A[i]) - B;
    }
    for (int i = 0; i < M; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        l--;
        mo.addQuery(l, r, 0);
    }
    mo.solve();
    for (int i = 0; i < M; i++) {
        printf("%d\n", -mo.ans[i]);
    }


    return 0;
}
