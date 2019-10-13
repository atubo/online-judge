// https://www.luogu.org/problem/P3219
// [HNOI2012]三角形覆盖问题

#include <bits/stdc++.h>
using namespace std;

const int MAXL = 2000010;
const int MAXN = 10010;
int S[MAXL];

struct Triangle {
    int x, y, d;
    int l, r;
    bool done;
    bool operator < (const Triangle& other) const {
        if (y != other.y) return y < other.y;
        if (x != other.x) return x < other.x;
        return d > other.d;
    }
} T[MAXN];

int N;

void push1(vector<int> &line, int x) {
    if (line.empty() || T[x].r > T[line.back()].r) {
        line.push_back(x);
    } else {
        for (int i = T[x].l; i < T[x].r; i++) {
            S[i]--;
            assert(S[i]);
        }
    }
}

void push2(vector<int>& line, int x, int& curr) {
    if (line.empty() || T[x].r > T[line.back()].r) {
        if (T[x].d > 0) {
            line.push_back(x);
            for (int i = T[x].l; i < T[x].r; i++) {
                if (++S[i] == 1) curr++;
            }
        }
    }
}

int main() {
    scanf("%d", &N);
    vector<vector<int>> H(MAXL);
    for (int i = 0; i < N; i++) {
        int x, y, d;
        scanf("%d%d%d", &x, &y, &d);
        T[i] = {x, y, d, x, x+d, false};
    }
    sort(T, T+N);
    int minh = INT_MAX, maxh = INT_MIN;
    for (int i = 0; i < N; i++) {
        int y = T[i].y;
        int d = T[i].d;
        H[y].push_back(i);
        minh = min(minh, y);
        maxh = max(maxh, y+d);
    }

    int64_t area = 0;
    int last = 0;

    vector<int> triangles;
    for (int h = minh; h <= maxh; h++) {
        int curr = last;
        for (int idx: triangles) {
            auto &t = T[idx];
            t.r--;
            if (--S[t.r] == 0) curr--;
            if (t.r == t.l) t.done = true;
        }
        area += (curr + last);
        vector<int> tmp;
        int idx1 = 0, idx2 = 0;
        while (idx1 < (int)triangles.size() && idx2 < (int)H[h].size()) {
            int x1 = triangles[idx1];
            int x2 = H[h][idx2];
            if (T[x1].done) {
                idx1++;
                continue;
            }
            if (T[x1].x < T[x2].x ||
                (T[x1].x == T[x2].x && T[x1].r >= T[x2].r)) {
                push1(tmp, x1);
                idx1++;
            } else {
                push2(tmp, x2, curr);
                idx2++;
            }
        }
        while (idx1 < (int)triangles.size()) {
            if (T[triangles[idx1]].done) {
                idx1++;
                continue;
            }
            push1(tmp, triangles[idx1++]);
        }
        while (idx2 < (int)H[h].size()) {
            push2(tmp, H[h][idx2++], curr);
        }
        swap(triangles, tmp);
        last = curr;
    }

    printf("%.1f\n", area/2.0);

    return 0;
}
