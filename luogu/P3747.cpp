// https://www.luogu.org/problemnew/show/P3747
// [六省联考2017]相逢是问候

#include <bits/stdc++.h>
using namespace std;

int calcPhi(int p) {
    int64_t ret = p;
    for (int i = 2; 1LL*i*i <= p; i++) {
        if (p % i == 0) ret = (ret*(i-1))/i;
        while (p % i == 0) {
            p /= i;
        }
    }
    if (p > 1) ret = (ret*(p-1))/p;
    return ret;
}

int N, M, P, C;
int K;
int phi[55];
int64_t pow1[10005][55], pow2[10005][55];

void build() {
    for (int i = 0; i < K; i++) {
        pow1[0][i] = 1;
        for (int j = 1; j <= 10000; j++) {
            pow1[j][i] = (pow1[j-1][i]*C) % phi[i];
        }
    }

    for (int i = 0; i < K; i++) {
        pow2[0][i] = 1;
        for (int j = 1; j <= 10000; j++) {
            pow2[j][i] = (pow2[j-1][i]*pow1[10000][i]) % phi[i];
        }
    }
}

int qpow(int n, int i) {
    return (pow2[n/10000][i] * pow1[n%10000][i]) % phi[i];
}

int64_t qpow2(int64_t n) {
    if (n == -1) return -1;
    int64_t x = C;
    int64_t ret = 1;
    while (n) {
        if (n & 1) {
            ret *= x;
            if (ret >= P) return -1;
        }
        x *= x;
        if (x >= P) return -1;
        n >>= 1;
    }
    if (ret >= P) ret = -1;
    return ret;
}


// note it's 1-indexed
class SegmentTree {
    int N;
    int64_t *t_;
    int64_t *a_;
    int *c_;
    bool *seal_;

public:
    SegmentTree(int N_): N(N_) {
        t_ = new int64_t[4*N]{};
        a_ = new int64_t[4*N]{};
        c_ = new int[4*N]{};
        seal_ = new bool[4*N]{};
    }

    ~SegmentTree() {
        delete[] t_;
        delete[] a_;
        delete[] c_;
        delete[] seal_;
    }

    void update(int a, int b) {
        update(1, 1, N, a, b);
    }

    // query range sum in [a, b]
    int64_t query(int a, int b) {
        return query(1, a, b, 1, N);
    }

    void build(int *arr) {
        build(1, 1, N, arr);
    }

private:
    void build(int k, int l, int r, int *arr) {
        if (l == r) {
            t_[k] = arr[l] % phi[0];
            a_[k] = arr[l];
            return;
        }

        int mid = (l + r) / 2;
        build(2*k, l, mid, arr);
        build(2*k+1, mid+1, r, arr);
        combine(k);
    }

    void combine(int k) {
        t_[k] = (t_[2*k] + t_[2*k+1]) % P;
        seal_[k] = seal_[2*k] && seal_[2*k+1];
    }

    void update(int k, int l, int r, int a, int b) {
        if (a > b) return;
        if (seal_[k]) return;
        if (l == r) {
            if (a_[k] == 0) {
                a_[k] = 1;
                t_[k] = 1;
                return;
            }
            if (++c_[k] == K-1) seal_[k] = true;
            int64_t x = a_[k];
            int64_t rx = x;
            for (int i = c_[k]; i >= 1; i--) {
                if (rx == -1 || rx >= phi[i]) {
                    x = qpow(x%phi[i]+phi[i], i-1);
                } else {
                    x = qpow(rx, i-1);
                }
                rx = qpow2(rx);
            }
            t_[k] = x;
            return;
        }

        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   l, mid, a, b);
        if (mid < b)  update(2*k+1, mid+1, r, a, b);
        combine(k);
    }

    // query range sum in [a, b], current node is [L, R]
    int64_t query(int k, int a, int b, int L, int R) {
        if (!k) return 0;
        if (b < L || a > R) return 0;
        if (a <= L && R <= b) return t_[k];
        int64_t sum = 0;
        int mid = (L + R) / 2;
        if (a <= mid) sum += query(2*k, a, b, L, mid);
        if (mid < b)  sum += query(2*k+1, a, b, mid+1, R);
        return sum;
    }
};

const int MAXN = 5e4+10;
int A[MAXN];

int main() {
    scanf("%d%d%d%d", &N, &M, &P, &C);
    int p = P;
    while (p > 1) {
        phi[K++] = p;
        p = calcPhi(p);
    }
    phi[K++] = 1;
    build();

    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
    SegmentTree st(N);
    st.build(A);

    for (int i = 0; i < M; i++) {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 0) {
            st.update(l, r);
        } else {
            printf("%ld\n", st.query(l, r) % P);
        }
    }
    return 0;
}
