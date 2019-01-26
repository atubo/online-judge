// https://www.luogu.org/problemnew/show/P4198
// 楼房重建

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int N, M;
int BN;
int H[MAXN];

struct Block {
    double b[320];
    int l, r;
    int sz;
    void build() {
        sz = 0;
        int curr = l;
        for (; curr < r; curr++) {
            if (H[curr] > 0) {
                b[sz++] = 1.0 * H[curr] / curr;
                break;
            }
        }
        for (int i = curr+1; i < r; i++) {
            double x = 1.0*H[i]/i;
            if (x > b[sz-1]) b[sz++] = x;
        }
    }
    int search(double x) {
        if (sz == 0 || b[sz-1] <= x) return 0;
        if (b[0] > x) return sz;
        int lo = 0, hi = sz-1;
        while (lo < hi-1) {
            int mid = (lo + hi) / 2;
            if (b[mid] <= x) lo = mid;
            else hi = mid;
        }
        return sz - hi;
    }
} B[320];

int solve() {
    int curr = 0;
    while (curr < BN && B[curr].sz == 0) curr++;
    if (curr == BN) return 0;
    int ans = B[curr].sz;
    double last = B[curr].b[B[curr].sz-1];
    for (int i = curr+1; i < BN; i++) {
        int len = B[i].search(last);
        ans += len;
        if (len != 0) last = B[i].b[B[i].sz-1];
    }
    return ans;
}

int main() {
    scanf("%d%d", &N, &M);
    int bsz = sqrt(N);
    BN = N/bsz;
    for (int i = 0; i < BN; i++) {
        B[i].l = i * bsz + 1;
        B[i].r = (i+1) * bsz + 1;
        B[i].build();
    }
    if (N%bsz) {
        B[BN].l = BN * bsz + 1;
        B[BN].r = N + 1;
        B[BN].build();
        BN++;
    }

    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        H[x] = y;
        int bid = (x-1) / bsz;
        B[bid].build();
        int ans = solve();
        printf("%d\n", ans);
    }

    return 0;
}
