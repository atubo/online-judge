// https://www.luogu.org/problemnew/show/P3730
// 曼哈顿交易

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int A[MAXN], B[MAXN];
int TOTD;

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
    int *ft_;
    int *freq_;

    void move(int pos, int sign) {
        int x = A[pos];
        int f = freq_[x];
        if (sign == 1) {
            ft_[f]--;
            freq_[x]++;
        } else {
            ft_[f-1]++;
            freq_[x]--;
        }
    }

    int search(int x) {
        if (ft_[N_] - ft_[0] < x) return -1;
        int lo = 0, hi = N_;
        while (lo < hi - 1) {
            int mid = (lo + hi) / 2;
            if (ft_[mid] - ft_[0] >= x) hi = mid;
            else lo = mid;
        }
        return hi;
    }

    void alloc() {
        queries_ = new Query[Q_]{};
        ft_ = new int[N_+1]{};
        freq_ = new int[N_+1]{};

        elem = new int[N_]{};
        ans  = new int[Q_]{};
    }

    void dealloc() {
        delete[] queries_;
        delete[] ft_;
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
        for (int i = 0; i <= N_; i++) {
            ft_[i] = TOTD;
        }

        for (int i = 0; i < Q_; i++) {
            const Query& q = queries_[i];
            while (l > q.l) move(--l, 1);
            while (r < q.r) move(r++, 1);
            while (l < q.l) move(l++, -1);
            while (r > q.r) move(--r, -1);
            ans[q.id] = search(q.x);
        }
    }
};

int N, M;

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        B[i] = A[i];
    }
    sort(B, B+N);
    TOTD = unique(B, B+N) - B;
    for (int i = 0; i < N; i++) {
        A[i] = lower_bound(B, B+TOTD, A[i]) - B;
    }

    Mo mo(N, M);
    for (int i = 0; i < M; i++) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        l--;
        mo.addQuery(l, r, k);
    }
    mo.solve();
    for (int i = 0; i < M; i++) {
        printf("%d\n", mo.ans[i]);
    }
    return 0;
}
