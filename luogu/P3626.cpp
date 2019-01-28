// https://www.luogu.org/problemnew/show/P3626
// [APIO2009]会议中心

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
        for (int i = 0; i <= N; i++) {
            tree[i] = 0;
        }
    }

    void set(int x, int v) {
        while(x <= N) {
            tree[x] = max(tree[x], v);
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

const int MAXN = 200010;
int N, NB;
int T[2*MAXN], mp[MAXN];
int F[MAXN][20];
const int INF = 0x3F3F3F3F;
struct Application {
    int id, l, r;
    bool operator < (const Application &other) const {
        if (l != other.l) return l < other.l;
        if (r != other.r) return r > other.r;
        return id < other.id;
    }
} A[MAXN], B[MAXN];

map<int, int> L;

void normalize() {
    memcpy(B, A, N*sizeof(Application));
    sort(B, B+N);
    stack<Application> st;
    for (int i = 0; i < N; i++) {
        auto a = B[i];
        while (!st.empty() && st.top().r >= a.r) {
            st.pop();
        }
        st.push(a);
    }
    int idx = 0;
    while (!st.empty()) {
        B[idx++] = st.top();
        st.pop();
    }
    NB = idx;
    reverse(B, B+NB);
}

void build() {
    F[NB][0] = INF;
    int p = NB;
    for (int i = NB-1; i >= 0; i--) {
        F[i][0] = F[i+1][0];
        while (p-1 >= 0 && B[p-1].l > B[i].r) p--;
        if (p < NB) F[i][0] = min(F[i][0], p);
        for (int k = 1; k < 20; k++) {
            int r = F[i][k-1];
            if (r < NB) {
                F[i][k] = F[r][k-1];
            } else {
                F[i][k] = INF;
            }
        }
    }
}

int pred(int x) {
    auto it = L.lower_bound(x);
    it--;
    return it->first;
}

int succ(int x) {
    auto it = L.lower_bound(x);
    return it->first;
}

int right(int x) {
    auto it = L.lower_bound(x);
    return it->second;
}

int count(int l, int r) {
    if (r < l) return 0;
    int idx = lower_bound(B, B+NB, Application{0, l, INT_MAX}) - B;
    if (idx == NB) return 0;
    if (B[idx].r > r) return 0;
    int ans = 1;
    for (int k = 19; k >= 0; k--) {
        if (F[idx][k] < INF && B[F[idx][k]].r <= r) {
            idx = F[idx][k];
            ans += (1<<k);
        }
    }
    return ans;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        A[i] = {i+1, x, y};
        T[2*i] = x;
        T[2*i+1] = y;
    }
    sort(T, T+2*N);
    int sz = unique(T, T+2*N) - T;
    for (int i = 0; i < N; i++) {
        A[i].l = lower_bound(T, T+sz, A[i].l) - T + 1;
        A[i].r = lower_bound(T, T+sz, A[i].r) - T + 1;
    }

    BIT bit(sz);
    sort(A, A+N);
    for (int i = 0; i < N; i++) {
        mp[A[i].id] = i;
    }

    for (int i = N-1; i >= 0; i--) {
        int d = bit.get(sz-A[i].r);
        bit.set(sz+1-A[i].l, d+1);
    }

    int ans = bit.get(sz);
    printf("%d\n", ans);

    normalize();
    build();
    L.insert(make_pair(sz+1, sz+1));
    L.insert(make_pair(0, 0));
    vector<int> res;
    for (int i = 1; i <= N; i++) {
        int l = A[mp[i]].l;
        int r = A[mp[i]].r;
        int l1 = pred(l);
        int l2 = succ(l);
        int r1 = right(l1);
        if (r1 >= l || l2 <= r) continue;
        if (count(r1+1, l-1) + count(r+1, l2-1) + 1 == count(r1+1, l2-1)) {
            res.push_back(i);
            L.insert(make_pair(l, r));
        }
    }
    sort(res.begin(), res.end());
    for (int x: res) {
        printf("%d ", x);
    }
    return 0;
}
