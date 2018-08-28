// https://www.luogu.org/problemnew/show/P2154
// [SDOI2009]虔诚的墓主人

#include <bits/stdc++.h>
using namespace std;

// segment tree with single point update and range query
// 0-indexed
class SegmentTreeSPU {
    static const int NULL_VALUE = 0;
public:
    SegmentTreeSPU(int n) {
        nData_ = 1;
        while (nData_ < n) nData_ = nData_ << 1;
        int sz = 2 * nData_ + 1;
        data = new int[sz];
        for (int i = 0; i < sz; i++) data[i] = NULL_VALUE;
    }

    ~SegmentTreeSPU() {
        delete[] data;
    }

    void update(int i, int value) {
        i += nData_;
        data[i] = value;
        for (; i > 1; i >>= 1) {
            int newVal = combine(data[i], data[i^1]);
            if (data[i>>1] == newVal) break;
            data[i>>1] = newVal;
        }
    }

    void build() {
        // assume all leaf nodes are already set up
        for (int i = nData_-1; i >= 1; i--) {
            data[i] = combine(data[2*i], data[2*i+1]);
        }
    }

    int query(int a, int b) const {
        a += nData_;
        b += nData_;
        int res = NULL_VALUE;
        for (; a <= b; a = (a+1) >> 1, b = (b-1) >> 1) {
            if ((a & 1) != 0) {
                res = combine(res, data[a]);
            }
            if ((b & 1) == 0) {
                res = combine(res, data[b]);
            }
        }
        return res;
    }

    int query() const {
        return data[1];
    }
private:
    int *data;
    int nData_;
    int combine(int a, int b) const {
        return a + b;
    }
};

class ModularUtils {
public:
    // return (a * b) mod n, dealing with possible overflow
    static int64_t mul_long(int64_t x, int64_t y, int64_t mod) {
        if (y < 0) {
            x = -x;
            y = -y;
        }
        int64_t s = 0, n = y, t = x;
        while (n) {
            if (n & 1) (s += t) %= mod;
            (t += t) %= mod;
            n >>= 1;
        }
        return s;
    }


    // (g, x, y) that a*x + b*y = g
    static void ext_gcd(int64_t a, int64_t b,
                        int64_t &g, int64_t &x, int64_t &y) {
        if (b == 0) {
            g = a; x = 1; y = 0;
            return;
        }
        int64_t dp, xp, yp;
        ext_gcd(b, a % b, dp, xp, yp);
        g = dp;
        x = yp;
        y = xp - a / b * yp;
    }

    // find x that a*x = b mod n
    static int64_t mod_solve(int64_t a, int64_t b, int64_t n) {
        int64_t d, xp, yp;
        ext_gcd(a, n, d, xp, yp);
        if (b % d == 0) {
            int64_t x0 = (mul_long(xp, b/d, n) + n) % n;
            return x0;
        } else {
            abort();
        }
    }

    static int64_t gcd(int64_t a, int64_t b) {
        if (b == 0) return a;
        return gcd(b, a%b);
    }
};

const int64_t MOD = 2147483648;
const int MAXW = 100010;
int N, M, W, K;
struct Tree {
    int x, y;
} trees[MAXW];

int findId(int x, const vector<int> &sorted) {
    return lower_bound(sorted.begin(), sorted.end(), x) - sorted.begin();
}

int64_t mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

int64_t add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

int64_t binom[MAXW];

int64_t calc(int n, int k) {
    int p1 = 0, p2 = 0;
    int64_t upper = 1, lower = 1;
    for (int x = n-k+1; x <= n; x++) {
        int t = __builtin_ctz(x);
        p1 += t;
        upper = mul(upper, x >> t);
    }
    for (int x = 1; x <= k; x++) {
        int t = __builtin_ctz(x);
        p2 += t;
        lower = mul(lower, x >> t);
    }
    int64_t ret = mul(upper, ModularUtils::mod_solve(lower, 1, MOD));
    ret = mul(ret, 1<<(p1-p2));
    return ret;
}

void init(int n) {
    for (int x = K; x <= n; x++) {
        binom[x] = calc(x, K);
    }
}

int64_t combo(int n, int k) {
    return binom[n];
}

int main() {
    vector<int> sortx, sorty;
    vector<int> totx, toty;
    vector<vector<int>> lines;
    vector<int> curry;

    scanf("%d%d", &N, &M);
    scanf("%d", &W);
    for (int i = 0; i < W; i++) {
        scanf("%d%d", &trees[i].x, &trees[i].y);
        sortx.push_back(trees[i].x);
        sorty.push_back(trees[i].y);
    }
    scanf("%d", &K);
    sort(sortx.begin(), sortx.end());
    sortx.erase(unique(sortx.begin(), sortx.end()), sortx.end());
    sort(sorty.begin(), sorty.end());
    sorty.erase(unique(sorty.begin(), sorty.end()), sorty.end());

    const int nx = sortx.size(), ny = sorty.size();
    init(max(nx, ny));
    curry.resize(ny);
    totx.resize(nx);
    toty.resize(ny);
    lines.resize(nx);
    for (int i = 0; i < W; i++) {
        trees[i].x = findId(trees[i].x, sortx);
        trees[i].y = findId(trees[i].y, sorty);
        totx[trees[i].x]++;
        toty[trees[i].y]++;
        lines[trees[i].x].push_back(trees[i].y);
    }
    for (int i = 0; i < nx; i++) {
        sort(lines[i].begin(), lines[i].end());
    }

    SegmentTreeSPU st(ny);
    int64_t ans = 0;
    for (int i = 0; i < nx; i++) {
        int last = -1;
        int currx = 0;
        for (int y: lines[i]) {
            curry[y]++;
            int n1y = curry[y], n2y = toty[y] - n1y;
            int64_t cnt = mul(combo(n1y, K), combo(n2y, K));
            st.update(y, cnt);
            int64_t q = st.query(last+1, y-1) % MOD;
            last = y;
            int n1x = currx, n2x = totx[i]-n1x;
            q = mul(q, mul(combo(n1x, K), combo(n2x, K)));
            currx++;
            ans = add(ans, q);
        }
    }
    printf("%ld\n", ans);

    return 0;
}
