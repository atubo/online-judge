// https://www.luogu.org/problemnew/show/1056
// 排座椅

#include <bits/stdc++.h>
using namespace std;

int M, N, K, L, D;

using PII = pair<int, int>;

void solve(vector<PII>& a, int k) {
    sort(a.begin(), a.end(), greater<PII>());
    vector<int> result;
    for (int i = 0; i < k; i++) {
        result.push_back(a[i].second+1);
    }
    sort(result.begin(), result.end());
    for (int i = 0; i < (int)result.size(); i++) {
        printf("%d", result[i]);
        if (i < (int)result.size()-1) printf(" ");
    }
    printf("\n");
}

int main() {
    scanf("%d%d%d%d%d", &M, &N, &K, &L, &D);
    vector<PII> hori(M), vert(N);
    for (int i = 0; i < M; i++) hori[i] = make_pair(0, i);
    for (int i = 0; i < N; i++) vert[i] = make_pair(0, i);
    for (int i = 0; i < D; i++) {
        int x, y, p, q;
        scanf("%d%d%d%d", &x, &y, &p, &q);
        x--; y--; p--; q--;
        if (x == p) {
            if (y > q) swap(y, q);
            vert[y].first++;
        } else {
            if (x > p) swap(x, p);
            hori[x].first++;
        }
    }
    solve(hori, K);
    solve(vert, L);
    return 0;
}
