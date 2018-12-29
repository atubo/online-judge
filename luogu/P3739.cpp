// https://www.luogu.org/problemnew/show/P3739
// [HAOI2014]走出金字塔

#include <bits/stdc++.h>
using namespace std;

const int MAXM = 10010;
int N, M, K, S;
int XA, YA;

int min3(int a, int b, int c) {
    return min(min(a, b), c);
}

struct Room {
    int x, y, t;
} dst[MAXM];

Room buildRoom(int x, int y) {
    int t = (abs(x-y) & 1) == (x & 1);
    return {x-t, (y-t+1)/2, t};
}

int dist(int x0, int y0, int x1, int y1) {
    int ret = abs(x0-x1) + abs(y0-y1);
    ret = min(ret, abs(x1-x0) + abs(x1-x0+y0-y1));
    ret = min(ret, abs(y1-y0) + abs(y1+x0-y0-x1));
    return ret;
}

int dist(const Room &a, const Room &b) {
    if (a.t == b.t) return 2*dist(a.x, a.y, b.x, b.y);
    if (a.t == 1) {
        return 1 + 2*min3(dist(a.x, a.y, b.x, b.y),
                          dist(a.x+1, a.y, b.x, b.y),
                          dist(a.x+1, a.y+1, b.x, b.y));
    } else {
        return 1 + 2*min3(dist(a.x, a.y, b.x, b.y),
                          dist(a.x, a.y, b.x+1, b.y),
                          dist(a.x, a.y, b.x+1, b.y+1));
    }
}

int main() {
    scanf("%d%d%d%d", &N, &M, &K, &S);
    scanf("%d%d", &XA, &YA);
    Room src = buildRoom(XA, YA);
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        dst[i] = buildRoom(x, y);
    }

    int ans = INT_MAX;
    for (int i = 0; i < M; i++) {
        ans = min(ans, dist(src, dst[i]));
    }
    if (S-K*ans > 0) {
        printf("%d", S-K*ans-1);
    } else {
        printf("-1");
    }

    return 0;
}
