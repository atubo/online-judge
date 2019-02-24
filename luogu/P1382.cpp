// https://www.luogu.org/problemnew/show/P1382
// 楼房

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int N;

int xord[2*MAXN], yord[MAXN];
int cnt[MAXN];
int prof[2*MAXN];

struct Edge {
    int x, y, t;
    bool operator < (const Edge &other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return t < other.t;
    }
} E[2*MAXN];

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int h, l, r;
        scanf("%d%d%d", &h, &l, &r);
        E[2*i] = {l, h, 0};
        E[2*i+1] = {r, h, 1};
        xord[2*i] = l;
        xord[2*i+1] = r;
        yord[i] = h;
    }
    yord[N] = 0;
    sort(xord, xord+2*N);
    sort(yord, yord+N+1);
    auto endx = unique(xord, xord+2*N);
    auto endy = unique(yord, yord+N+1);

    for (int i = 0; i < 2*N; i++) {
        int x = lower_bound(xord, endx, E[i].x) - xord;
        int y = lower_bound(yord, endy, E[i].y) - yord;
        E[i] = {x, y, E[i].t};
    }

    sort(E, E+2*N);

    priority_queue<int> pq;
    pq.push(0);
    cnt[0] = 1;
    int p = 0;
    while (true) {
        int q = p;
        while (q < 2*N && E[q].x == E[p].x) {
            int y = E[q].y;
            int t = E[q].t;
            if (t == 0) {
                cnt[y]++;
                pq.push(y);
            } else {
                cnt[y]--;
            }
            q++;
        }
        while (cnt[pq.top()] == 0) pq.pop();
        prof[E[p].x] = pq.top();
        p = q;
        if (p >= 2*N) break;
    }

    vector<pair<int, int>> ret;
    int lasty = 0;
    for (int i = 0; i < 2*N; i++) {
        int x = xord[i];
        int y = yord[prof[i]];
        if (y == lasty) continue;
        ret.push_back(make_pair(x, lasty));
        ret.push_back(make_pair(x, y));
        lasty = y;
    }

    printf("%d\n", (int)ret.size());
    for (const auto &pr: ret) {
        printf("%d %d\n", pr.first, pr.second);
    }

    return 0;
}
