// https://www.luogu.org/problemnew/show/P3759
// [TJOI2017]不勤劳的图书管理员

#include <bits/stdc++.h>
using namespace std;

using PII = pair<int, int>;

const int MOD = 1000000007;

int add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

int sub(int64_t a, int64_t b) {
    return (a + MOD - b) % MOD;
}

int mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

struct ChairmanInFenwick {
    int N;  // number of positions, index is 1-based
    int M;  // number of weights, index is 0-based
    int T_cnt;
    int *root;
    int *val;
    int *lc, *rc;
    int16_t *cnt;

    // cap is the number of elements to be added
    ChairmanInFenwick(int N_, int M_, int cap): N(N_), M(M_), T_cnt(1) {
        root = new int[N+1]{};
        const int numOfNodes = cap * int(log2(N)+2) * int(log2(M)+2);
        val = new int[numOfNodes]{};
        lc = new int[numOfNodes]{};
        rc = new int[numOfNodes]{};
        cnt = new int16_t[numOfNodes]{};
    }

    ~ChairmanInFenwick() {
        delete[] root;
        delete[] val;
        delete[] lc;
        delete[] rc;
        delete[] cnt;
    }

    // add value t to weight node w at position x
    void add(int x, int w, int t) {
        for (int i = x; i <= N; i += lowbit(i)) {
            update(root[i], w, t, 0, M-1);
        }
    }

    // weight sum [l, r] for position [1, k]
    PII query(int k, int l, int r) {
        if (l > r) return make_pair(0, 0);
        int sum = 0;
        int c = 0;
        for (int j = k; j; j -= lowbit(j)) {
            auto p = querySingleTree(root[j], 0, M-1, l, r);
            sum = ::add(sum, p.first);
            c += p.second;
        }
        return make_pair(sum, c);
    }

private:
    int lowbit(int x) {return x & -x;}

    void update(int &now, int w, int t, int l, int r) {
        if (!now) now = T_cnt++;
        if (t > 0) {
            val[now] = ::add(val[now], t);
            cnt[now]++;
        } else {
            val[now] = sub(val[now], -t);
            cnt[now]--;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (w <= mid) update(lc[now], w, t, l, mid);
        else          update(rc[now], w, t, mid+1, r);
    }

    PII querySingleTree(int node, int L, int R, int l, int r) {
        if (L >= l && R <= r) return make_pair(val[node], cnt[node]);
        if (L > r || R < l) return make_pair(0, 0);
        int sum = 0, c = 0;
        int mid = (L + R) / 2;
        if (l <= mid) {
            auto p = querySingleTree(lc[node], L, mid, l, r);
            sum = ::add(sum, p.first);
            c += p.second;
        }
        if (mid < r) {
            auto p = querySingleTree(rc[node], mid+1, R, l, r);
            sum = ::add(sum, p.first);
            c += p.second;
        }
        return make_pair(sum, c);
    }
};

const int MAXN = 50010;
int N, M;
int V[MAXN];
int pos[MAXN]; // book->position
int book[MAXN]; // position->book
int64_t res;

void update(ChairmanInFenwick &cf, int x, int y, int lo, int hi,
            int b, int f) {
   auto p = cf.query(y, lo, hi);
   auto q = cf.query(x, lo, hi);
   int d = sub(p.first, q.first);
   int c = p.second - q.second;
   int up = add(d, mul(c, b));
   if (f == 1) {
       res = add(res, up);
   } else {
       res = sub(res, up);
   }
}


void solve(ChairmanInFenwick &cf, int x, int y) {
    if (x == y) {
        printf("%lld\n", res);
        return;
    }
    int bx = book[x];
    int by = book[y];
    int vx = V[bx];
    int vy = V[by];

    update(cf, x-1, y-1, 1, bx-1, vx, -1);
    update(cf, x-1, y-1, bx+1, N, vx, 1);
    update(cf, x, y-1, by+1, N, vy, -1);
    update(cf, x, y-1, 1, by-1, vy, 1);
    if (bx < by) {
        res = add(res, vx + vy);
    } else {
        res = sub(res, vx + vy);
    }
    cf.add(x, bx, -vx);
    cf.add(y, by, -vy);
    cf.add(x, by, vy);
    cf.add(y, bx, vx);
    swap(pos[bx], pos[by]);
    swap(book[x], book[y]);
    printf("%lld\n", res);
}

void tally(ChairmanInFenwick &cf, int x) {
    int bx = book[x];
    auto p = cf.query(x-1, bx+1, N);
    res += p.first + p.second * V[bx];
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        int a, v;
        scanf("%d%d", &a, &v);
        V[a] = v;
        pos[a] = i;
        book[i] = a;
    }
    ChairmanInFenwick cf(N, N+1, N+M);
    for (int i = 1; i <= N; i++) {
        cf.add(pos[i], i, V[i]);
    }
    for (int i = 1; i <= N; i++) {
        tally(cf, i);
    }
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (x > y) swap(x, y);
        solve(cf, x, y);
    }
    return 0;
}
