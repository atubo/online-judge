// https://www.luogu.org/problemnew/show/P3527
// [POI2011]MET-Meteors

#include <bits/stdc++.h>
using namespace std;

class BIT {
public:
    // 1-indexed
    BIT(int size): N(size) {
        tree = (int64_t*)malloc((size+1) * sizeof(int64_t));
        clear();
    }

    ~BIT() {
        free(tree);
        tree = NULL;
    }

    void clear() {
        memset(tree, 0, (N+1) * sizeof(int64_t));
    }

    // add v to value at x
    void set(int x, int v) {
        while(x <= N) {
            tree[x] += v;
            x += (x & -x);
        }
    }

    // get cumulative sum up to and including x
    int64_t get(int x) const {
        int64_t res = 0;
        while(x) {
            res += tree[x];
            x -= (x & -x);
        }
        return res;
    }

private:
    int64_t* tree;
    const int N;
};

const int MAXN = 300010;
int N, M, K;
int C[MAXN], P[MAXN];
int countries[MAXN], tmp_countries[MAXN];
int64_t tot[MAXN];
int ans[MAXN];
vector<int> stations[MAXN];

struct Shower {
    int l, r, a;
} S[MAXN];

void shower(BIT &ft, int left, int right) {
    for (int i = left; i <= right; i++) {
        int l = S[i].l;
        int r = S[i].r;
        int a = S[i].a;
        if (l <= r) {
            ft.set(l, a);
            ft.set(r+1, -a);
        } else {
            ft.set(1, a);
            ft.set(r+1, -a);
            ft.set(l, a);
        }
    }
}

void unshower(BIT &ft, int left, int right) {
    for (int i = left; i <= right; i++) {
        int l = S[i].l;
        int r = S[i].r;
        int a = S[i].a;
        if (l <= r) {
            ft.set(l, -a);
            ft.set(r+1, a);
        } else {
            ft.set(1, -a);
            ft.set(r+1, a);
            ft.set(l, -a);
        }
    }
}

void search(BIT &ft, int left, int right, int p, int q) {
    if (left == right) {
        for (int i = p; i <= q; i++) {
            int c = countries[i];
            ans[c] = left;
        }
        return;
    }

    int mid = (left + right) / 2;

    shower(ft, left, mid);

    for (int i = p; i <= q; i++) {
        int c = countries[i];
        tot[c] = 0;
        for (int s: stations[c]) {
            tot[c] += ft.get(s);
            if (tot[c] > P[c]) break;
        }
    }

    int a = p, b = q;
    for (int i = p; i <= q; i++) {
        int c = countries[i];
        if (tot[c] < P[c]) {
            P[c] -= tot[c];
            tmp_countries[b--] = c;
        } else {
            tmp_countries[a++] = c;
        }
    }
    assert(a == b+1);

    for (int i = p; i <= q; i++) {
        countries[i] = tmp_countries[i];
    }

    unshower(ft, left, mid);

    search(ft, left, mid, p, b);
    search(ft, mid+1, right, a, q);
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; i++) {
        scanf("%d", &C[i]);
        stations[C[i]].push_back(i);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &P[i]);
    }
    scanf("%d", &K);
    for (int i = 1; i <= K; i++) {
        int l, r, a;
        scanf("%d%d%d", &l, &r, &a);
        S[i] = {l, r, a};
    }

    for (int i = 1; i <= N; i++) {
        countries[i] = i;
    }

    BIT ft(M);
    search(ft, 1, K+1, 1, N);

    for (int i = 1; i <= N; i++) {
        if (ans[i] == K+1) printf("NIE\n");
        else printf("%d\n", ans[i]);
    }

    return 0;
}
