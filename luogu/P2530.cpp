// https://www.luogu.org/problemnew/show/P2530
// [SHOI2001]化工厂装箱员

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;
int N;
int A[MAXN];
int ps[MAXN][3];
bool vis[MAXN*2048];

int encode(int i, int k1, int k2, int k3) {
    return (i << 11) + (k1 * 121 + k2 * 11 + k3);
}

void decode(int x, int &i, int &k1, int &k2, int &k3) {
    i = (x >> 11);
    int k = x & 0x7FF;
    k3 = k % 11;
    k = (k - k3) / 11;
    k2 = k % 11;
    k = (k - k2) / 11;
    k1 = k % 11;
}

struct Item {
    int x, d;
};

int bfs() {
    int x = encode(0, 0, 0, 0);
    deque<Item> q;
    q.push_back({x, 0});
    vis[x] = true;
    while (!q.empty()) {
        Item item = q.front();
        q.pop_front();
        x = item.x;
        int d = item.d;
        if (x == encode(N, 0, 0, 0)) {
            return d;
        }
        int p, k[3];
        decode(x, p, k[0], k[1], k[2]);

        // put all type-A
        if (k[1] + k[2] < 10) {
            int m = min(N-p, 10 - k[1] - k[2]);
            int d2 = d + (k[0] > 0);
            int kn[3] = {0, k[1], k[2]};
            int b = p, e = p+m;
            for (int i = 0; i < 3; i++) {
                kn[i] += ps[e][i] - ps[b][i];
            }
            x = encode(p+m, kn[0], kn[1], kn[2]);
            if (!vis[x]) {
                if (d2 == d) q.push_front({x, d2});
                else         q.push_back({x, d2});
                vis[x] = true;
            }
        }
        // put type-B
        if (k[0] + k[2] < 10) {
            int m = min(N-p, 10 - k[0] - k[2]);
            int d2 = d + (k[1] > 0);
            int kn[3] = {k[0], 0, k[2]};
            int b = p, e = p+m;
            for (int i = 0; i < 3; i++) {
                kn[i] += ps[e][i] - ps[b][i];
            }
            x = encode(p+m, kn[0], kn[1], kn[2]);
            if (!vis[x]) {
                if (d2 == d) q.push_front({x, d2});
                else         q.push_back({x, d2});
                vis[x] = true;
            }
        }
        // put type-C
        if (k[0] + k[1] < 10) {
            int m = min(N-p, 10 - k[0] - k[1]);
            int d2 = d + (k[2] > 0);
            int kn[3] = {k[0], k[1], 0};
            int b = p, e = p+m;
            for (int i = 0; i < 3; i++) {
                kn[i] += ps[e][i] - ps[b][i];
            }
            x = encode(p+m, kn[0], kn[1], kn[2]);
            if (!vis[x]) {
                if (d2 == d) q.push_front({x, d2});
                else         q.push_back({x, d2});
                vis[x] = true;
            }
        }
    }
    assert(0);
    return 0;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        char line[5];
        scanf("%s", line);
        A[i] = line[0] - 'A';
        for (int j = 0; j < 3; j++) {
            ps[i][j] = ps[i-1][j] + (A[i] == j);
        }
    }
    int ans = bfs();
    printf("%d\n", ans);
    return 0;
}
