// https://www.luogu.org/problemnew/show/P3298
// [SDOI2013]泉

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int N, K;
int W[MAXN][6];
int64_t cnt[64];


class HashSet {
    static const int MAXM = 1000003;
    static int GARBAGE;

    struct Node {
        pair<int, int> to;
        int next, cnt;
    };
public:
    HashSet(int n) {
        alloc(n);
        sz_ = 0;
    }

    ~HashSet() {
        dealloc();
    }

    bool contains(const pair<int, int> &x) {
        int y = x.first % MAXM;
        for (int i = h_[y]; i; i = e_[i].next) {
            auto to = e_[i].to;
            if (to == x) return true;
        }
        return false;
    }

    int& operator[](const pair<int, int> &x) {
        int y = x.first % MAXM;
        for (int i = h_[y]; i; i = e_[i].next) {
            auto to = e_[i].to;
            if (to == x) return e_[i].cnt;
        }
        return GARBAGE;
    }

    void insert(const pair<int, int> &x) {
        int y = x.first % MAXM;
        e_[++sz_] = Node{x, h_[y], 1};
        h_[y] = sz_;
    }

    void reset() {
        memset(h_, 0, MAXM*sizeof(int));
        sz_ = 0;
    }
private:
    Node *e_;
    int *h_;
    int sz_;

    void alloc(int n) {
        e_ = new Node[n]{};
        h_ = new int[MAXM]{};
    }

    void dealloc() {
        delete[] e_;
        delete[] h_;
    }
};

int HashSet::GARBAGE = 0;

const int P = 347;
const int Q = 997;
const int MOD1 = 1e9+7;
const int MOD2 = 1e9+9;
void hashf(pair<int, int> &p, int x) {
    p.first = (1LL*p.first * P + x) % MOD1;
    p.second = (1LL*p.second * Q + x) % MOD2;
}

int64_t countPairs(HashSet &hs, int mask) {
    hs.reset();
    int64_t ans = 0;
    for (int i = 0; i < N; i++) {
        int m = mask;
        pair<int, int> key = make_pair(0, 0);
        while (m) {
            int x = __builtin_ctz(m);
            hashf(key, W[i][x]);
            m -= (1<<x);
        }
        if (hs.contains(key)) ans += hs[key]++;
        else hs.insert(key);
    }
    return ans;
}


int findWells(const vector<int> &masks, int m) {
    int ret = 0;
    while (m) {
        int x = __builtin_ctz(m);
        ret |= masks[x];
        m -= (1<<x);
    }
    return ret;
}

int64_t solve(int k) {
    vector<int> masks;
    for (int m = 1; m < 64; m++) {
        if (__builtin_popcount(m) == k) {
            masks.push_back(m);
        }
    }
    int64_t ans = 0;
    for (int m = 1; m < (1<<masks.size()); m++) {
        int wells = findWells(masks, m);
        int pc = __builtin_popcount(m);
        if (pc & 1) ans += 1LL*pc*cnt[wells];
        else ans -= 1LL*pc*cnt[wells];
    }
    return ans;
}

int main() {
    scanf("%d%d", &N, &K);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 6; j++) {
            scanf("%d", &W[i][j]);
        }
    }

    HashSet hs(N);
    for (int mask = 1; mask < 64; mask++) {
        cnt[mask] = countPairs(hs, mask);
    }

    int64_t ans = 0;
    if (K) ans = solve(K);
    else {
        ans = 1LL * N * (N-1) / 2;
        for (int k = 1; k <= 6; k++) {
            ans -= solve(k);
        }
    }
    printf("%ld", ans);
    return 0;
}
