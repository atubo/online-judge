// http://poj.org/problem?id=2104
// K-th Number

#include <cstdio>
#include <climits>
#include <algorithm>
#include <new>
using namespace std;

const int MAXN = 100000;

template <size_t SIZE>
struct MemoryPool {
    char buf[SIZE], *cur;

    MemoryPool(): cur(buf) {}

    void *alloc(const int size) {
        if (cur == buf + SIZE) return malloc(size);
        else {
            char *p = cur;
            cur += size;
            return p;
        }
    }
};

MemoryPool<(4 + 4 + 8 + 8 + 4) * MAXN * 10> pool;

struct ChairmanTree {
    struct Node {
        int l, r;
        Node *lc, *rc;
        int cnt;

        Node(int l, int r, Node *lc = NULL, Node *rc = NULL):
            l(l), r(r), lc(lc), rc(rc),
            cnt((lc ? lc->cnt : 0) + (rc ? rc->cnt : 0)) {}
        Node(int l, int r, int cnt):
            l(l), r(r), lc(NULL), rc(NULL), cnt(cnt) {}

        void pushDown() {
            if (lc && rc) return;
            int mid = l + ((r -l) >> 1);
            if (!lc) lc = new (pool.alloc(sizeof(Node))) Node(l, mid);
            if (!rc) rc = new (pool.alloc(sizeof(Node))) Node(mid+1, r);
        }

        Node *insert(int num) {
            if (num < l || num > r) return this;
            else if (num == l && num == r) {
                return new (pool.alloc(sizeof(Node))) Node(l, r, this->cnt + 1);
            } else {
                int mid = l + ((r -l) >> 1);
                pushDown();
                if (num <= mid) {
                    return new (pool.alloc(sizeof(Node))) Node(l, r, lc->insert(num), rc);
                } else {
                    return new (pool.alloc(sizeof(Node))) Node(l, r, lc, rc->insert(num));
                }
            }
        }

        int rank() const {
            return lc ? lc->cnt : 0;
        }
    } *root[MAXN + 1];

    int n;

    void build(const int a[], const int n) {
        this->n = n;
        root[0] = new (pool.alloc(sizeof(Node))) Node(0, n-1);
        for (int i = 1; i <= n; i++) {
            root[i] = root[i-1]->insert(a[i-1]);
        }
    }

    int query(int l, int r, int k) {
        Node *L = root[l-1], *R = root[r];
        int min = 0, max = n-1;
        while (min != max) {
            L->pushDown(); R->pushDown();
            int mid = min + ((max-min) >> 1), t = R->rank() - L->rank();
            if (k <= t) {
                L = L->lc;
                R = R->lc;
                max = mid;
            } else {
                k -= t;
                L = L->rc;
                R = R->rc;
                min = mid + 1;
            }
        }
        return min;
    }
} t;

int main() {
    int n, m, a[MAXN];
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int set[MAXN];
    std::copy(a, a+n, set);
    std::sort(set, set+n);
    int *end = std::unique(set, set+n);
    for (int i = 0; i < n; i++) {
        a[i] = std::lower_bound(set, end, a[i]) - set;
    }

    t.build(a, n);

    for (int i = 0; i < m; i++) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        int ans = t.query(l, r, k);
        printf("%d\n", set[ans]);
    }

    return 0;
}
