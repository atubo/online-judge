// https://www.luogu.org/problemnew/show/P2447
// [SDOI2010]外星千足虫

#include <bits/stdc++.h>
using namespace std;

class Mask {
    // 1000-bit
    static const int SZ = 32;
private:
    unsigned int bits[SZ];
public:
    Mask() {
        memset(bits, 0, sizeof(bits));
    }

    void set(int i) {
        bits[i/32] |= (1 << (i%32));
    }

    void unset(int i) {
        bits[i/32] &= ~(1 << (i%32));
    }

    int get(int i) const {
        // return 0 or 1
        return (bits[i/32] >> (i%32)) & 1;
    }

    Mask& operator |= (const Mask &other) {
        for (int i = 0; i < SZ; i++) {
            bits[i] |= other.bits[i];
        }
        return *this;
    }

    Mask& operator ^= (const Mask &other) {
        for (int i = 0; i < SZ; i++) {
            bits[i] ^= other.bits[i];
        }
        return *this;
    }

    int popcount() {
        int ret = 0;
        for (int i = 0; i < SZ; i++) {
            ret += __builtin_popcount(bits[i]);
        }
        return ret;
    }

    string toString(int n) {
        string ret(n, '0');
        for (int i = 0; i < n; i++) {
            ret[n-1-i] = get(i) + '0';
        }
        return ret;
    }
};

const int MAXM = 2010, MAXN = 1010;

struct Ifc {
    Mask mask;
    int result;
} ifc[MAXM];

int N, M;
int pos[MAXN];
int remain;

void solve() {
    int result[N] = {0};
    for (int p = 0; p < N; p++) {
        int k = pos[p];
        int rhs = ifc[k].result;
        for (int i = 0; i < p; i++) {
            if (ifc[k].mask.get(i)) rhs ^= result[i];
        }
        result[p] = rhs;
    }
    for (int i = N-1; i >= 0; i--) {
        if (result[i]) printf("?y7M#\n");
        else printf("Earth\n");
    }
}


int main() {
    memset(pos, -1, sizeof(pos));
    scanf("%d%d", &N, &M);
    remain = N;
    char line[MAXN];
    int rhs;
    for (int i = 0; i < M; i++) {
        scanf("%s%d", line, &rhs);
        for (int j = N-1; j >= 0; j--) {
            if (line[N-1-j] == '1') {
                ifc[i].mask.set(j);
            }
        }
        ifc[i].result = rhs;
        for (int j = N-1; j >= 0; j--) {
            if (ifc[i].mask.get(j)) {
                int k = pos[j];
                if (k != -1) {
                    ifc[i].mask ^= ifc[k].mask;
                    ifc[i].result ^= ifc[k].result;
                } else {
                    pos[j] = i;
                    remain--;
                    break;
                }
            }
        }
        if (remain == 0) {
            printf("%d\n", i+1);
            solve();
            return 0;
        }
    }
    printf("Cannot Determine\n");

    return 0;
}
