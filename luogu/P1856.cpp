// https://www.luogu.org/problemnew/show/P1856
// [USACO5.5]矩形周长Picture

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5010;
const int MAXP = 20010;
const int SHIFT = 10000;

struct Segment {
    int start, end, pos, type;
    bool operator < (const Segment &other) const {
        if (pos < other.pos) return true;
        if (pos > other.pos) return false;
        if (type < other.type) return true;
        if (type > other.type) return false;
        if (start < other.start) return true;
        if (start > other.start) return false;
        return end < other.end;
    }
};

Segment X[2*MAXN], Y[2*MAXN];
int cnt[MAXP];
int N;

int solve(Segment *s) {
    memset(cnt, 0, sizeof(cnt));
    sort(s, s+2*N);
    int ret = 0;
    for (int i = 0; i < 2*N; i++) {
        if (s[i].type == 0) {
            for (int j = s[i].start; j < s[i].end; j++) {
                if (cnt[j]++ == 0) ret++;
            }
        } else {
            for (int j = s[i].start; j < s[i].end; j++) {
                if (--cnt[j] == 0) ret++;
            }
        }
    }
    return ret;
}


int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int xmin, ymin, xmax, ymax;
        scanf("%d%d%d%d", &xmin, &ymin, &xmax, &ymax);
        xmin += SHIFT; ymin += SHIFT; xmax += SHIFT; ymax += SHIFT;
        X[2*i] = {xmin, xmax, ymin, 0};
        X[2*i+1] = {xmin, xmax, ymax, 1};
        Y[2*i] = {ymin, ymax, xmin, 0};
        Y[2*i+1] = {ymin, ymax, xmax, 1};
    }
    int ret = solve(X);
    ret += solve(Y);
    printf("%d\n", ret);
    return 0;
}
