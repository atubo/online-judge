// https://www.luogu.org/problemnew/show/P3813
// [FJOI2017]矩阵填数

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7;
const int MAXN = 12;
int T;
int H, W, M, N;

struct Submatrix {
    int x1, y1, x2, y2, v;
} submatrix[MAXN];

struct Range {
    int lo, hi;
    bool operator < (const Range &other) const {
        assert(*this == other ||
               lo > other.hi || hi < other.lo);
        return lo < other.lo;
    }
    bool operator == (const Range &other) const {
        return lo == other.lo && hi == other.hi;
    }
};

void sortuniq(vector<Range> &a) {
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
}

void fillspace(vector<Range> &a) {
    vector<Range> t;
    t.push_back(a[0]);
    for (int i = 1; i < (int)a.size(); i++) {
        if (a[i].lo > a[i-1].hi+1) t.push_back({a[i-1].hi+1, a[i].lo-1});
        t.push_back(a[i]);
    }
    a.swap(t);
}

int add(int64_t a, int64_t b) {
    return (a + b) % MOD;
}

int mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

int qpow(int64_t a, int n) {
    int ret = 1;
    while (n) {
        if (n & 1) ret = mul(ret, a);
        a = mul(a, a);
        n >>= 1;
    }
    return ret;
}

int solve(int mask, const vector<Range> &sortx,
          const vector<Range> &sorty) {
    const int nh = sortx.size();
    const int nw = sorty.size();
    vector<vector<int>> matrix(nh, vector<int>(nw, M));
    for (int i = 0; i < N; i++) {
        int x1 = submatrix[i].x1;
        int y1 = submatrix[i].y1;
        int x2 = submatrix[i].x2;
        int y2 = submatrix[i].y2;
        int v = submatrix[i].v;
        int h1 = lower_bound(sortx.begin(), sortx.end(), Range{x1, x1})
            - sortx.begin();
        int h2 = lower_bound(sortx.begin(), sortx.end(), Range{x2, x2})
            - sortx.begin();
        int w1 = lower_bound(sorty.begin(), sorty.end(), Range{y1, y1})
            - sorty.begin();
        int w2 = lower_bound(sorty.begin(), sorty.end(), Range{y2, y2})
            - sorty.begin();
        for (int h = h1; h <= h2; h++) {
            for (int w = w1; w <= w2; w++) {
                matrix[h][w] = min(matrix[h][w], v-((mask>>i)&1));
            }
        }
    }
    int ans = 1;
    for (int i = 0; i < nh; i++) {
        for (int j = 0; j < nw; j++) {
            int sz = (sortx[i].hi-sortx[i].lo+1)
                * (sorty[j].hi-sorty[j].lo+1);
            ans = mul(ans, qpow(matrix[i][j], sz));
        }
    }
    if (__builtin_popcount(mask) & 1) ans = MOD - ans;
    return ans;
}

void solve() {
    scanf("%d%d%d%d", &H, &W, &M, &N);
    vector<Range> sortx = {{0, 0}, {H-1, H-1}};
    vector<Range> sorty = {{0, 0}, {W-1, W-1}};
    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2, v;
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &v);
        x1--; y1--; x2--; y2--;
        submatrix[i] = {x1, y1, x2, y2, v};
        sortx.push_back({x1, x1});
        sortx.push_back({x2, x2});
        sorty.push_back({y1, y1});
        sorty.push_back({y2, y2});
    }
    sortuniq(sortx);
    sortuniq(sorty);
    fillspace(sortx);
    fillspace(sorty);

    int ans = 0;
    for (int mask = 0; mask < (1<<N); mask++) {
        ans = add(ans, solve(mask, sortx, sorty));
    }
    printf("%d\n", ans);
}


int main() {
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
