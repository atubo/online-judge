// https://www.luogu.org/problemnew/show/P4093
// [HEOI2016/TJOI2016]序列

#include <bits/stdc++.h>
using namespace std;

class BIT {
public:
    // 1-indexed
    BIT(int size): N(size) {
        tree = (int*)malloc((size+1) * sizeof(int));
        clear();
    }

    ~BIT() {
        free(tree);
        tree = NULL;
    }

    void clear() {
        memset(tree, 0, (N+1) * sizeof(int));
    }

    void set(int x, int v) {
        while(x <= N) {
            tree[x] = max(tree[x], v);
            x += (x & -x);
        }
    }

    void reset(int x) {
        while (x <= N) {
            tree[x] = 0;
            x += (x & -x);
        }
    }

    int get(int x) const {
        int res = 0;
        while(x) {
            res = max(res, tree[x]);
            x -= (x & -x);
        }
        return res;
    }

private:
    int* tree;
    const int N;
};

const int MAXN = 100010;
int N, M;

int dp[MAXN];

struct Item {
    int l, r, v, id;
} a[MAXN];

bool cmpid(const Item &x, const Item &y) {return x.id < y.id;}
bool cmpv(const Item &x, const Item &y) {return x.v < y.v;}
bool cmpl(const Item &x, const Item &y) {return x.l < y.l;}

void cdq(int l, int r, BIT &ft) {
    if (l == r) return;
    int mid = (l + r) / 2;
    cdq(l, mid, ft);
    sort(a + l, a + mid + 1, cmpv);
    sort(a + mid + 1, a + r + 1, cmpl);
    int j = l;
    for (int i = mid+1; i <= r; i++) {
        while (j <= mid && a[j].v <= a[i].l) {
            ft.set(a[j].r, dp[a[j].id]);
            j++;
        }
        dp[a[i].id] = max(dp[a[i].id], ft.get(a[i].v)+1);
    }

    for (int i = l; i < j; i++) {
        ft.reset(a[i].r);
    }
    sort(a + l, a + r + 1, cmpid);
    cdq(mid + 1, r, ft);
}

int main() {
    scanf("%d%d", &N, &M);
    fill(dp, dp+N, 1);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i].v);
        a[i].id = i;
        a[i].l = a[i].r = a[i].v;
    }
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--;
        a[x].l = min(a[x].l, y);
        a[x].r = max(a[x].r, y);
    }
    BIT ft(MAXN);
    cdq(0, N-1, ft);
    int ans = *max_element(dp, dp+N);
    printf("%d\n", ans);
    return 0;
}
