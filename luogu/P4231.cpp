// https://www.luogu.org/problemnew/show/P4231
// 三步必杀

#include <bits/stdc++.h>
using namespace std;

const int MAXM = 900010;
struct Event {
    int pos;
    int64_t a, d;
    bool operator < (const Event &other) const {
        if (pos < other.pos) return true;
        if (pos > other.pos) return false;
        if (a < other.a) return true;
        if (a > other.a) return false;
        return d < other.d;
    }
} events[MAXM];

int N, M;
int64_t xorv;

void process(int64_t a, int64_t d, int p, int q) {
    for (int i = p+1; i <= q; i++) {
        a += d;
        xorv ^= a;
    }
}

int main() {
    scanf("%d%d", &N, &M);
    events[0] = {0, 0, 0};
    for (int i = 1; i <= M; i++) {
        int l, r;
        int64_t s, e;
        scanf("%d%d%ld%ld", &l, &r, &s, &e);
        int64_t d = (e - s) / (r - l);
        events[3*i-2] = {l, s, d};
        events[3*i-1] = {r, 0, -d};
        events[3*i]   = {r+1, -e, 0};
    }
    sort(events+1, events+3*M+1);

    int lastidx = 0, curridx = 1;
    int64_t a = 0, d = 0;
    int64_t maxv = 0;
    while (curridx <= 3*M) {
        int p = events[lastidx].pos;
        int q = events[curridx].pos - 1;
        process(a, d, p, q);
        a += d * (q - p);
        maxv = max(maxv, a);
        a += d;
        while (curridx <= 3*M && events[curridx].pos == q+1) {
            a += events[curridx].a;
            d += events[curridx].d;
            curridx++;
        }
        maxv = max(maxv, a);
        xorv ^= a;
        lastidx = curridx-1;
    }

    xorv ^= a;
    printf("%ld %ld", xorv, maxv);

    return 0;
}
