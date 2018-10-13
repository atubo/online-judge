// https://www.luogu.org/problemnew/show/P2564
// [SCOI2009]生日礼物

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;
int N, K;
int M;
int cnt[60];
int missing;
int **P;
int pos[MAXN];

int id(int x) {
    return lower_bound(pos, pos+M, x) - pos;
}

bool push(int q) {
    for (int i = 1; i <= P[q][0]; i++) {
        int c = P[q][i];
        if (cnt[c]++ == 0) missing--;
    }
    return missing == 0;
}

bool pop(int q) {
    for (int i = 1; i <= P[q][0]; i++) {
        int c = P[q][i];
        if (--cnt[c] == 0) missing++;
    }
    return missing == 0;
}

int solve() {
    missing = K;
    int p = 0, q = -1;
    int ans = INT_MAX;
    while (true) {
        while (++q < M && !push(q));
        if (q == M) break;
        ans = min(ans, pos[q]-pos[p]);
        while (p < q && pop(p++)) {
            ans = min(ans, pos[q]-pos[p]);
        }
    }
    return ans;
}

int main() {
    scanf("%d%d", &N, &K);
    vector<vector<int>> pearls(K);
    for (int i = 0; i < K; i++) {
        int t;
        scanf("%d", &t);
        pearls[i].resize(t);
        for (int j = 0; j < t; j++) {
            scanf("%d", &pearls[i][j]);
            pos[M++] = pearls[i][j];
        }
    }
    sort(pos, pos+M);
    M = unique(pos, pos+M) - pos;

    vector<int> cnt_by_pos(M);
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < (int)pearls[i].size(); j++) {
            pearls[i][j] = id(pearls[i][j]);
            cnt_by_pos[pearls[i][j]]++;
        }
    }
    P = new int*[M]{};
    for (int i = 0; i < M; i++) {
        P[i] = new int[cnt_by_pos[i]+1]{};
    }

    for (int i = 0; i < K; i++) {
        for (int x: pearls[i]) {
            P[x][++P[x][0]] = i;
        }
    }

    int ans = solve();
    printf("%d\n", ans);

    return 0;
}
