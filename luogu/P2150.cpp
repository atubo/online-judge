// https://www.luogu.org/problemnew/show/P2150
// [NOI2015]寿司晚宴

#include <bits/stdc++.h>
using namespace std;

const int MAXMASK = 255;
const int PRIMES[8] = {2, 3, 5, 7, 11, 13, 17, 19};
const int MAXN = 501;
int N;
int64_t P;
int64_t f[MAXMASK+1][MAXMASK+1];
int64_t g[2][MAXMASK+1][MAXMASK+1];

struct Number {
    int z, mask;
    bool operator < (const Number &other) const {
        return z < other.z;
    }
} numbers[MAXN];

Number normalize(int x) {
    int mask = 0, z = 1;
    for (int i = 0; i < 8; i++) {
        while (x % PRIMES[i] == 0) {
            mask |= (1 << i);
            x = x / PRIMES[i];
        }
    }
    for (int p = 23; p <= x; p += 2) {
        if (x % p == 0) {
            z = p;
            break;
        }
    }
    return {z, mask};
}

int main() {
    scanf("%d%lld", &N, &P);
    for (int i = 0; i < N-1; i++) {
        numbers[i] = normalize(i+2);
    }

    sort(numbers, numbers+N-1);

    f[0][0] = 1;
    int p = 0;
    while (p < N-1) {
        int q = p + 1;
        if (numbers[p].z > 1) {
            while (q < N-1 && numbers[q].z == numbers[p].z) q++;
        }
        for (int a = 0; a <= MAXMASK; a++) {
            for (int b = 0; b <= MAXMASK; b++) {
                g[0][a][b] = f[a][b];
                g[1][a][b] = f[a][b];
            }
        }
        for (int i = 1; i < q-p+1; i++) {
            int s = numbers[i-1+p].mask;
            for (int a = MAXMASK; a >= 0; a--) {
                for (int b = MAXMASK; b >= 0; b--) {
                    if ((s & b) == 0) {
                        (g[0][a|s][b] += g[0][a][b]) %= P;
                    }
                    if ((s & a) == 0) {
                        (g[1][a][b|s] += g[1][a][b]) %= P;
                    }
                }
            }
        }
        for (int a = 0; a <= MAXMASK; a++) {
            for (int b = 0; b <= MAXMASK; b++) {
                f[a][b] = (g[0][a][b] + g[1][a][b] - f[a][b] + P) % P;
            }
        }
        p = q;
    }

    int64_t ans = 0;
    for (int a = 0; a <= MAXMASK; a++) {
        for (int b = 0; b <= MAXMASK; b++) {
            (ans += f[a][b]) %= P;
        }
    }
    printf("%lld\n",ans);

    return 0;
}
