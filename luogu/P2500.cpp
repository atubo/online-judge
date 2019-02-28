// https://www.luogu.org/problemnew/show/P2500
// [SDOI2012]集合

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
const int MAXM = 500010;

int N, M, Q;

struct Edge {
    int u, v, w;
    bool operator < (const Edge &other) const {
        if (w != other.w) return w < other.w;
        if (u != other.u) return u < other.u;
        return v < other.v;
    }
} E[MAXM];

int S[MAXN];

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        E[i] = {u, v, w};
    }
    sort(E, E+M);
    scanf("%d", &Q);
    char query[10];
    for (int i = 0; i < Q; i++) {
        scanf("%s", query);
        if (query[0] == 'M') {
            int x;
            scanf("%d", &x);
            x--;
            int to = query[4] - 'A';
            S[x] = to;
        } else {
            int a = query[3] - 'A';
            int b = query[4] - 'A';
            int ans = -1;
            for (int j = 0; j < M; j++) {
                if ((S[E[j].u] == a && S[E[j].v] == b) ||
                    (S[E[j].u] == b && S[E[j].v] == a)) {
                    ans = E[j].w;
                    break;
                }
            }
            if (ans >= 0) {
                printf("%d\n", ans);
            } else {
                printf("No Found!\n");
            }
        }
    }
    return 0;
}
