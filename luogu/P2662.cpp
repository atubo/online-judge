// https://www.luogu.org/problemnew/show/P2662
// 牛场围栏

#include <bits/stdc++.h>
using namespace std;

class FenwickTree {
public:
    // 1-indexed
    FenwickTree(int size): n_(size) {
        tree_ = new int64_t[n_+1]{};
    }

    ~FenwickTree() {
        delete[] tree_;
    }

    void clear() {
        memset(tree_, 0, (n_+1) * sizeof(int64_t));
    }

    // add v to value at x
    void set(int x, int v) {
        while(x <= n_) {
            tree_[x] += v;
            x += (x & -x);
        }
    }

    // get cumulative sum up to and including x
    int64_t get(int x) const {
        int64_t res = 0;
        while(x) {
            res += tree_[x];
            x -= (x & -x);
        }
        return res;
    }

private:
    int64_t* tree_;
    const int n_;
};

void spfa(const vector<int> &B, int n) {
    vector<int> d(n);
    for (int i = 1; i < n; i++) d[i] = INT_MAX;
    vector<bool> inq(n);
    queue<int> q;
    q.push(0);
    inq[0] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;

        for (int x: B) {
            int v = (u + x) % n;
            if (d[v] > d[u] + x) {
                d[v] = d[u] + x;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) ans = max(ans, d[i]);
    if (ans == INT_MAX || ans < n) printf("-1\n");
    else printf("%d\n", ans-n);
}

const int MAXN = 110;
int N, M;
int L[MAXN];

int main() {
    scanf("%d%d", &N, &M);
    int maxl = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &L[i]);
        maxl = max(maxl, L[i]);
    }
    FenwickTree ft(maxl);
    for (int i = 0; i < N; i++) {
        int r = L[i];
        int l = max(1, r-M);
        ft.set(l, 1);
        ft.set(r+1, -1);
    }

    vector<int> B;
    for (int i = 1; i <= maxl; i++) {
        if (ft.get(i) > 0) B.push_back(i);
    }

    spfa(B, maxl);
    return 0;
}
