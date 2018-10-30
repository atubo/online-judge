// https://www.luogu.org/problemnew/show/P1120
// 小木棍 ［数据加强版］

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 66;
int N;
bool vis[MAXN];
int nxt[MAXN];

bool dfs(const vector<int> &A, int x0, int last, int x, int t) {
    //printf("x0=%d x=%d t=%d\n", x0, x, t);
    if (x == 0 && t == 1) return true;
    if (x == 0) {
        t--;
        x = x0;
        last = 0;
    }
    if (A[N-1] > x) return false;
    int p = last+1;
    while (p < N && vis[p]) p++;
    if (p == N) return false;

    while (p < N && A[p] > x) p = nxt[p];
    while (p < N && vis[p]) p++;
    while (p < N) {
        vis[p] = true;
        if (dfs(A, x0, p, x-A[p], t)) return true;
        vis[p] = false;
        if (x == A[p] || x == x0) break;
        p = nxt[p];
        while (p < N && vis[p]) p++;
    }
    return false;
}


bool check(const vector<int> &A, int x, int t) {
    memset(vis, 0, N*sizeof(bool));
    vis[0] = true;
    return dfs(A, x, 0, x-A[0], t);
}

int main() {
    scanf("%d", &N);
    vector<int> A;
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
        if (x <= 50) A.push_back(x);
    }
    N = A.size();
    int tot = 0;
    for (int x: A) tot += x;
    sort(A.begin(), A.end(), greater<int>());
    nxt[N-1] = N;
    for (int i = N-2; i >= 0; i--) {
        nxt[i] = (A[i] == A[i+1] ? nxt[i+1]: i+1);
    }
    int ans = 0;
    for (int x = A[0]; x <= tot; x++) {
        if (tot % x != 0) continue;
        if (check(A, x, tot/x)) {
            ans = x;
            break;
        }
    }
    printf("%d", ans);
    return 0;
}
