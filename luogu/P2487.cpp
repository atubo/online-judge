// https://www.luogu.org/problemnew/show/P2487
// [SDOI2011]拦截导弹

#include <bits/stdc++.h>
using namespace std;

struct SegmentInFenwick {
    struct Data {
        int val;
        double cnt;
        void merge(const Data &other) {
            if (val > other.val) return;
            if (val == other.val) cnt += other.cnt;
            else *this = other;
        }
    };
    int N;  // number of positions, index is 1-based
    int M;  // number of weights, index is 0-based
    int numOfNodes;
    int T_cnt;
    int *root;
    int *lc, *rc;
    Data *data;

    // cap is the number of elements to be added
    SegmentInFenwick(int N_, int M_, int cap): N(N_), M(M_), T_cnt(1) {
        root = new int[N+1]{};
        numOfNodes = cap * int(log2(N)+2) * int(log2(M)+2);
        lc = new int[numOfNodes]{};
        rc = new int[numOfNodes]{};
        data = new Data[numOfNodes]{};
    }

    ~SegmentInFenwick() {
        delete[] root;
        delete[] lc;
        delete[] rc;
        delete[] data;
    }

    void clear() {
        T_cnt = 1;
        memset(root, 0, (N+1)*sizeof(int));
        memset(lc, 0, numOfNodes*sizeof(int));
        memset(rc, 0, numOfNodes*sizeof(int));
        memset(data, 0, numOfNodes*sizeof(Data));
    }

    void add(int x, int w, const Data &t) {
        for (int i = x; i <= N; i += lowbit(i)) {
            update(root[i], w, t, 0, M-1);
        }
    }

    Data query(int k, int r) const {
        Data ret = {0, 1};
        if (r < 0) return ret;
        for (int j = k; j; j -= lowbit(j)) {
            ret.merge(querySingleTree(root[j], 0, M-1, 0, r));
        }
        return ret;
    }

private:
    int lowbit(int x) const {return x & -x;}

    void update(int &now, int w, const Data &t, int l, int r) {
        if (!now) now = T_cnt++;
        data[now].merge(t);
        if (l == r) return;
        int mid = (l + r) / 2;
        if (w <= mid) update(lc[now], w, t, l, mid);
        else          update(rc[now], w, t, mid+1, r);
    }

    Data querySingleTree(int node, int L, int R, int l, int r) const {
        if (L >= l && R <= r) return data[node];
        if (L > r || R < l) return {-1, 0};
        Data ret = {-1, 0};
        int mid = (L + R) / 2;
        if (l <= mid) ret.merge(querySingleTree(lc[node], L, mid, l, r));
        if (mid < r)  ret.merge(querySingleTree(rc[node], mid+1, R, l, r));
        return ret;
    }
};

const int MAXN = 5e4+10;
int N;
int H[MAXN], V[MAXN];
int H2[MAXN], V2[MAXN];
double ans[MAXN];
SegmentInFenwick::Data pcnt[MAXN], pcnt2[MAXN];

void discretize(int *a, int *a2) {
    vector<int> ordered(N);
    copy(a, a+N, ordered.begin());
    sort(ordered.begin(), ordered.end());
    ordered.erase(unique(ordered.begin(), ordered.end()), ordered.end());
    for (int i = 0; i < N; i++) {
        a[i] = lower_bound(ordered.begin(), ordered.end(), a[i]) -
            ordered.begin();
        a2[i] = ordered.size() - a[i] - 1;
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &H[i], &V[i]);
    }
    discretize(H, H2);
    discretize(V, V2);
    SegmentInFenwick sif(N, N, N);
    for (int i = 0; i < N; i++) {
        auto data = sif.query(H2[i]+1, V2[i]);
        pcnt[i] = {data.val+1, data.cnt};
        sif.add(H2[i]+1, V2[i], pcnt[i]);
    }

    int maxlen = 0;

    for (int i = 0; i < N; i++) {
        maxlen = max(maxlen, pcnt[i].val);
    }

    double totcnt = 0;
    for (int i = 0; i < N; i++) {
        if (pcnt[i].val == maxlen) totcnt += pcnt[i].cnt;
    }

    sif.clear();
    for (int i = N-1; i >= 0; i--) {
        auto data = sif.query(H[i]+1, V[i]);
        pcnt2[i] = {data.val+1, data.cnt};
        sif.add(H[i]+1, V[i], pcnt2[i]);
    }

    for (int i = 0; i < N; i++) {
        if (pcnt[i].val + pcnt2[i].val == maxlen + 1) {
            ans[i] = 1.0 * pcnt[i].cnt * pcnt2[i].cnt / totcnt;
        }
    }

    printf("%d\n", maxlen);
    for (int i = 0; i < N; i++) {
        printf("%.5f ", ans[i]);
    }

    return 0;
}
