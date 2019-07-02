// https://www.luogu.org/problemnew/show/P4885
// 灭顶之灾

#include <bits/stdc++.h>
using namespace std;

struct Range {
    int64_t l, r;
    bool operator < (const Range& other) const {
        if (l != other.l) return l < other.l;
        return r < other.r;
    }
} R[1000010];
int64_t N, M, S, Q;
int rcnt;
vector<Range> cand;

int build() {
    for (int i = 0; i < S; i++) {
        int64_t a, b;
        scanf("%ld%ld", &a, &b);
        a--; b--;
        if (b / M >= N) return 1;
        if (a == b) continue;
        int64_t p = a % M, q = b % M;
        if (p < q) {
            if (a / M == N-1) R[rcnt++] = {M-q, M-1};
            else R[rcnt++] = {M-q, M-p-1};
        } else {
            R[rcnt++] = {0, M-p-1};
            if (q > 0) R[rcnt++] = {M-q, M-1};
        }
    }
    sort(R, R+rcnt);
    int64_t last = -1;
    for (int i = 0; i < rcnt; i++) {
        if (R[i].l > last+1) cand.push_back({last+1, R[i].l-1});
        last = max(last, R[i].r);
    }
    if (last < M-1) cand.push_back({last+1, M-1});
    if (cand.empty()) return 1;
    if (!(cand.size() == 1 && cand[0].r == cand[0].l)) return 2;
    return 0;
}

int64_t eval() {
    int64_t s = cand[0].l;

    int64_t ret = 0;
    for (int i = 0; i < Q; i++) {
        int64_t a;
        scanf("%ld", &a);
        a += s - 1;
        if (a/M >= N) continue;
        int64_t x = a/M + 1;
        int64_t y = a%M + 1;
        ret ^= x;
        ret ^= y;
    }
    return ret;
}

int main() {
    scanf("%ld%ld%ld%ld", &N, &M, &S, &Q);
    int ret = build();

    if (ret == 1) printf("Impossible!\n");
    else if (ret == 2) printf("Uncertain!\n");
    else printf("%ld\n", eval());
    return 0;
}
