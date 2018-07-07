// https://www.luogu.org/problemnew/show/P3940
// 分组

#include <bits/stdc++.h>
using namespace std;

class UnionFind {
private:
    const int N;
    vector<int> rank;
    vector<int> parent;
    vector<int> size;

    int link(int u, int v) {
        if (u == v) return u;
        if (rank[u] > rank[v]) {
            parent[v] = u;
            size[u] += size[v];
            return u;
        } else {
            parent[u] = v;
            size[v] += size[u];
            if (rank[u] == rank[v]) {
                rank[v]++;
            }
            return v;
        }
    }

public:
    UnionFind(int n): N(n) {
        rank.resize(N);
        parent.resize(N);
        size.resize(N);

        reset();
    }

    void reset() {
        for (int i = 0; i < N; i++) {
            makeSet(i);
        }
    }

    void makeSet(int k) {
        assert(0 <= k && k < N);

        parent[k] = k;
        rank[k] = 0;
        size[k] = 1;
    }

    int find(int k) {
        if (parent[k] == k) return k;
        int root = find(parent[k]);
        return parent[k] = root;
    }

    int join(int u, int v) {
        return link(find(u), find(v));
    }

    int count(int u) {
        return size[find(u)];
    }
};

const int MAXN = 131100;
int N, K;
int A[MAXN], cnt[MAXN];
int deg[MAXN];
int num_seen, seen[MAXN];

bool feasible1(int i) {
    int a = A[i];
    for (int k = 1; k <= 512; k++) {
        int64_t b = k*k - a;
        if (b > 0 &&  b < MAXN && cnt[b] > 0) return false;
    }
    cnt[a]++;
    seen[num_seen++] = a;
    return true;
}

void reset1(int k) {
    for (int i = num_seen-1; i >= 0;  i--) {
        cnt[seen[i]] = 0;
    }
    cnt[A[k]] = 1;
    seen[0] = A[k];
    num_seen = 1;
}

bool isHalfSquare(int x) {
    int y = sqrt(2*x) + 0.1;
    return 2 * x == y * y;
}

bool feasible2(int i, UnionFind &uf) {
    int a = A[i];
    bool a_is_half_square = isHalfSquare(a);
    if (a_is_half_square) {
        if (deg[a] > 0 || cnt[a] > 1) return false;
    }
    cnt[a]++;
    seen[num_seen++] = a;
    for (int k = 1; k <= 512; k++) {
        int64_t b = k*k - a;
        if (b == a) continue;
        if (b > 0 && b < MAXN && cnt[b] > 0) {
            if (uf.find(a) == uf.find(b) ||
                uf.find(a+MAXN) == uf.find(b+MAXN)) return false;
            if (isHalfSquare(b)) {
                if (cnt[b] > 1) return false;
                deg[b]++;
            }
            if (a_is_half_square) deg[a]++;
            uf.join(a, b+MAXN);
            uf.join(a+MAXN, b);
        }
    }
    return true;
}

void reset2(int k, UnionFind &uf) {
    for (int i = num_seen-1; i >= 0; i--) {
        int a = seen[i];
        cnt[a] = 0;
        deg[a] = 0;
        uf.makeSet(a);
        uf.makeSet(a+MAXN);
    }
    cnt[A[k]] = 1;
    seen[0] = A[k];
    num_seen = 1;
}

void solve1() {
    vector<int> ans;
    for (int i = N-1; i >= 0; i--) {
        if (!feasible1(i)) {
            ans.push_back(i+1);
            reset1(i);
        }
    }
    printf("%d\n", ans.size()+1);
    reverse(ans.begin(), ans.end());
    for (int x: ans) {
        printf("%d ", x);
    }
    printf("\n");
}

void solve2() {
    vector<int> ans;
    UnionFind uf(2*MAXN);
    for (int i = N-1; i >= 0; i--) {
        if (!feasible2(i, uf)) {
            ans.push_back(i+1);
            reset2(i, uf);
        }
    }
    printf("%d\n", ans.size()+1);
    reverse(ans.begin(), ans.end());
    for (int x: ans) {
        printf("%d ", x);
    }
    printf("\n");
}

int main() {
    scanf("%d%d", &N, &K);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    if (K == 1) solve1();
    else solve2();

    return 0;
}
