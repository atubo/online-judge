// https://www.luogu.org/problemnew/show/P3224
// [HNOI2012]永无乡

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag,
        tree_order_statistics_node_update> ordered_set;

const int MAXN = 100010;
int N, M;
int id_prio[MAXN], prio_id[MAXN];
vector<vector<int>> followers;
vector<ordered_set*> trees;
int leader[MAXN];

void merge(int a, int b) {
    int u = leader[id_prio[a]], v = leader[id_prio[b]];
    if (u == v) return;
    if (trees[u]->size() > trees[v]->size()) swap(u, v);
    for (int x: followers[u]) {
        followers[v].push_back(x);
        trees[v]->insert(x);
        leader[x] = v;
    }
}

int query(int x, int k) {
    int u = leader[id_prio[x]];
    if ((int)trees[u]->size() < k) return -1;
    int p = *trees[u]->find_by_order(k-1);
    return prio_id[p];
}

int main() {
    scanf("%d%d", &N, &M);
    trees.resize(N+1);
    followers.resize(N+1);
    for (int i = 1; i <= N; i++) {
        int x;
        scanf("%d", &x);
        id_prio[i] = x;
        prio_id[x] = i;
        trees[i] = new ordered_set();
        trees[i]->insert(i);
        leader[i] = i;
        followers[i].push_back(i);
    }
    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        merge(a, b);
    }
    int q;
    scanf("%d", &q);
    char cmd[10];
    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%s %d %d", cmd, &x, &y);
        if (cmd[0] == 'B') merge(x, y);
        else printf("%d\n", query(x, y));
    }

    return 0;
}
