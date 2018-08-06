// https://www.luogu.org/problemnew/show/P3295
// [SCOI2016]萌萌哒

#include <bits/stdc++.h>
using namespace std;

class UnionFind {
private:
    const int N;
    vector<int> parent;

    void makeSet(int k) {
        assert(0 <= k && k < N);

        parent[k] = k;
    }

    int link(int u, int v) {
        if (u == v) return u;
        if (u < v) {
            parent[v] = u;
            return u;
        } else {
            parent[u] = v;
            return v;
        }
    }

public:
    UnionFind(int n): N(n) {
        parent.resize(N);

        reset();
    }

    void reset() {
        for (int i = 0; i < N; i++) {
            makeSet(i);
        }
    }

    int find(int k) {
        if (parent[k] == k) return k;
        int root = find(parent[k]);
        return parent[k] = root;
    }

    int join(int u, int v) {
        return link(find(u), find(v));
    }

};

const int MOD = 1e9 + 7;
int N, M;

int main() {
    scanf("%d%d", &N, &M);
    if (N == 1) {
        printf("10\n");
        return 0;
    }
    vector<UnionFind*> ufs(17);
    for (int i = 0; i < 17; i++) {
        ufs[i] = new UnionFind(N);
    }
    for (int i = 0; i < M; i++) {
        int l1, r1, l2, r2;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        l1--; r1--; l2--; r2--;
        if (l1 > l2) {
            swap(l1, l2);
            swap(r1, r2);
        }
        for (int k = 16; k >= 0; k--) {
            if (r1-l1+1 >= (1<<k)) {
                ufs[k]->join(l1, l2);
                l1 += (1<<k);
                l2 += (1<<k);
            }
        }
    }
    for (int k = 16; k >= 1; k--) {
        for (int i = 0; i + (1<<k) <= N; i++) {
            int fa = ufs[k]->find(i);
            if (fa != i) {
                ufs[k-1]->join(i, fa);
                ufs[k-1]->join(i+(1<<(k-1)), fa+(1<<(k-1)));
            }
        }
    }

    int64_t ans = 9;
    for (int i = 1; i < N; i++) {
        if (ufs[0]->find(i) == i) {
            ans = (ans * 10) % MOD;
        }
    }
    printf("%ld\n", ans);
    return 0;
}
