// https://www.luogu.org/problemnew/show/P3217
// [HNOI2011]数矩形

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1510;
int N;
int X[MAXN], Y[MAXN];

struct Link {
    int64_t length;
    int cx, cy;
    int p, q;
    bool operator < (const Link &other) {
        if (length < other.length) return true;
        if (length > other.length) return false;
        if (cx < other.cx) return true;
        if (cx > other.cx) return false;
        if (cy < other.cy) return true;
        if (cy > other.cy) return false;
        if (p < other.p) return true;
        if (p > other.p) return false;
        return q < other.q;
    }
};

int64_t calcArea(int p, int q, int r) {
    int64_t dx1 = X[r] - X[p];
    int64_t dy1 = Y[r] - Y[p];
    int64_t dx2 = X[r] - X[q];
    int64_t dy2 = Y[r] - Y[q];
    int64_t ret = abs(dx1*dy2) + abs(dx2*dy1);
    return ret;
}


int64_t calc(const vector<Link> &links, int l, int r) {
    int64_t ans = 0;
    for (int i = l; i < r; i++) {
        for (int j = i+1; j < r; j++) {
            ans = max(ans, calcArea(links[i].p, links[i].q,
                                    links[j].p));
        }
    }
    return ans;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &X[i], &Y[i]);
    }

    vector<Link> links;
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
            int64_t dx = X[i] - X[j];
            int64_t dy = Y[i] - Y[j];
            int64_t length = dx * dx + dy * dy;
            int cx = X[i] + X[j];
            int cy = Y[i] + Y[j];
            links.push_back({length, cx, cy, i, j});
        }
    }

    sort(links.begin(), links.end());

    const int nl = links.size();
    int l = 0, r = 0;
    int64_t ans = 0;
    while (l < nl) {
        while (r < nl && links[r].length == links[l].length &&
               links[r].cx == links[l].cx &&
               links[r].cy == links[l].cy) r++;
        ans = max(ans, calc(links, l, r));
        l = r;
    }
    printf("%ld\n", ans);

    return 0;
}
