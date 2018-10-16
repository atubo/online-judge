// https://www.luogu.org/problemnew/show/P1315
// 观光公交

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
int N, M, K;
int D[MAXN];
struct Tourist {
    int t, a, b;
} tourists[10010];
int cutoff[MAXN], off[MAXN];
int arrival[MAXN], departure[MAXN];
int64_t ans;

void travel() {
    arrival[1] = 0;
    departure[1] = cutoff[1];
    for (int i = 2; i <= N; i++) {
        arrival[i] = departure[i-1] + D[i-1];
        ans += 1LL * off[i] * arrival[i];
        departure[i] = max(cutoff[i], arrival[i]);
    }
}

int eval(int p, int q) {
    int ret = 0;
    for (int i = p+1; i <= q+1; i++) {
        ret += off[i];
    }
    return ret;
}

bool speedup() {
    int p = 1;
    int mx = -1;
    pair<int, int> pr;
    while (p < N) {
        if (D[p] == 0) {
            p++;
            continue;
        }
        int offset = 0;
        int q = p;
        while (q < N && departure[q+1] > cutoff[q+1]) {
            q++;
        }
        if (q >= N) {
            q--;
            offset = 1;
        }
        int rd = eval(p, q);
        if (rd > mx) {
            mx = rd;
            pr = make_pair(p, q);
        }
        p = q + 1 + offset;
    }
    if (mx == -1) return false;

    ans -= mx;

    D[pr.first]--;
    for (int i = pr.first; i <= pr.second; i++) {
        arrival[i+1]--;
        departure[i+1] = max(departure[i+1]-1, cutoff[i+1]);
    }
    return true;
}

int main() {
    scanf("%d%d%d", &N, &M, &K);
    for (int i = 1; i <= N-1; i++) {
        scanf("%d", &D[i]);
    }
    for (int i = 0; i < M; i++) {
        int t, a, b;
        scanf("%d%d%d", &t, &a, &b);
        tourists[i] = {t, a, b};
        cutoff[a] = max(cutoff[a], t);
        off[b]++;
        ans -= t;
    }

    travel();
    for (int k = 1; k <= K; k++) {
        if (!speedup()) break;
    }
    printf("%ld\n", ans);
    return 0;
}
