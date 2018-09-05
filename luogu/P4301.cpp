// https://www.luogu.org/problemnew/show/P4301
// [CQOI2013]新Nim游戏

#include <bits/stdc++.h>
using namespace std;

class XorLinearBasis {
public:
    int64_t *a;

    XorLinearBasis(int maxl): maxl_(maxl) {
        alloc();
    }

    XorLinearBasis(const XorLinearBasis &b) {
        maxl_ = b.maxl_;
        alloc();
        memcpy(a, b.a, maxl_*sizeof(int64_t));
    }

    XorLinearBasis& operator = (const XorLinearBasis &b) {
        dealloc();
        maxl_ = b.maxl_;
        alloc();
        memcpy(a, b.a, maxl_*sizeof(int64_t));
        return *this;
    }

    ~XorLinearBasis() {
        dealloc();
    }

    bool insert(int64_t t) {
        for (int j = maxl_; j >= 0; j--) {
            if (!(t & (1ll << j))) continue;

            if (a[j]) t ^= a[j];
            else {
                for (int k = 0; k < j; k++) {
                    if (t & (1ll << k)) t ^= a[k];
                }

                for (int k = j+1; k <= maxl_; k++) {
                    if (a[k] & (1ll << j)) a[k] ^= t;
                }
                a[j] = t;
                return true;
            }
        }
        return false;
    }

    void mergeFrom(const XorLinearBasis &other) {
        for (int i = 0; i <= maxl_; i++) {
            insert(other.a[i]);
        }
    }

    static XorLinearBasis merge(const XorLinearBasis &a,
                                const XorLinearBasis &b) {
        XorLinearBasis res = a;
        for (int i = 0; i <= res.maxl_; i++) {
            res.insert(b.a[i]);
        }
        return res;
    }

private:
    int maxl_;

    void alloc() {
        a = new int64_t[maxl_+1]{};
    }

    void dealloc() {
        delete[] a;
    }
};
int main() {
    int N;
    scanf("%d", &N);
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    sort(A.begin(), A.end(), greater<int>());
    XorLinearBasis xlb(31);
    int64_t ans = 0;
    for (int x: A) {
        if (!xlb.insert(x)) {
            ans += x;
        }
    }
    printf("%ld\n", ans);

    return 0;
}
