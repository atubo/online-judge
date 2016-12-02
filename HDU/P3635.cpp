// http://acm.hdu.edu.cn/showproblem.php?pid=3635
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
int rnk[MAXN];
int parent[MAXN];
int size[MAXN];

void init(int N) {
    for (int i = 0; i < N; i++) {
        parent[i] = i;
        rnk[i] = 0;
        size[i] = 1;
    }
}

int find(int k) {
    if (parent[k] == k) return k;
    int root = find(parent[k]);
    rnk[k] += rnk[parent[k]];
    return parent[k] = root;
}

void join(int u, int v) {
    int fu = find(u);
    int fv = find(v);
    parent[fu] = fv;
    size[fv] += size[fu];
    rnk[fu] = 1;
}

void solve() {
    int N, q;
    scanf("%d %d", &N, &q);
    init(N);
    char t;
    int a, b;
    while (q--) {
        cin >> t;
        if (t == 'T') {
            scanf("%d %d", &a, &b);
            a--; b--;
            if (find(a) != find(b)) join(a, b);
        } else {
            scanf("%d", &a);
            a--;
            int x = find(a);
            int y = size[x];
            int z = rnk[a];
            printf("%d %d %d\n", x+1, y, z);
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        printf("Case %d:\n", i);
        solve();
    }
    return 0;
}
