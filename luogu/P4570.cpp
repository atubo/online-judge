// https://www.luogu.org/problemnew/show/P4570
// [BJWC2011]元素

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
const int MAXN = 1010;
int N;
struct Ore {
    int64_t num;
    int mag;
    bool operator > (const Ore &other) const {
        if (mag > other.mag) return true;
        if (mag < other.mag) return false;
        return num > other.num;
    }
} ore[MAXN];

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%ld%d", &ore[i].num, &ore[i].mag);
    }
    sort(ore, ore+N, greater<Ore>());

    XorLinearBasis xlb(63);
    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (xlb.insert(ore[i].num)) {
            ans += ore[i].mag;
        }
    }
    printf("%d\n", ans);
    return 0;
}
