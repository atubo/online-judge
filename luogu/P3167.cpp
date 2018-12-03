// https://www.luogu.org/problemnew/show/P3167
// [CQOI2014]通配符匹配

#include <bits/stdc++.h>
using namespace std;

const uint64_t KEY = 19260817;
const int MAXN = 100010;
int N;
uint64_t pre[MAXN], fac[MAXN], H[20];
bool dp[15][MAXN];
int pos[15];
char name[MAXN], pattern[MAXN];
int nwild, patlen, namelen;

void hashit() {
    uint64_t ret = 0;
    for (int i = 1; i <= namelen; i++) {
        ret = ret * KEY + name[i];
        pre[i] = ret;
    }
}

void init() {
    fac[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fac[i] = KEY * fac[i-1];
    }
    uint64_t h = 0;
    for (int i = 1; i <= patlen; i++) {
        if (pattern[i] == '*' || pattern[i] == '?') {
            nwild++;
            pos[nwild] = i;
            H[nwild] = h;
            h = 0;
        } else {
            h = h * KEY + pattern[i];
        }
    }
}

int main() {
    scanf("%s", pattern+1);
    strcat(pattern+1, "?");
    patlen = strlen(pattern+1);
    scanf("%d", &N);
    init();

    for (int ns = 0; ns < N; ns++) {
        scanf("%s", name+1);
        strcat(name+1, "{");
        namelen = strlen(name+1);
        hashit();
        memset(dp, 0, sizeof(dp));
        dp[0][0] = true;
        for (int i = 0; i < nwild; i++) {
            for (int j = 0; j < namelen; j++) {
                if (!dp[i][j]) continue;
                if (pattern[pos[i]] == '*') dp[i][j+1] = true;
                int w = pos[i+1] - pos[i] - 1;
                if (j + w > namelen) continue;
                uint64_t hs = pre[j+w] - pre[j] * fac[w];
                uint64_t hp = H[i+1];
                if (hs == hp) {
                    if (pattern[pos[i+1]] == '?') {
                        if (j+w+1 <= namelen) dp[i+1][j+w+1] = true;
                    } else {
                        dp[i+1][j+w] = true;
                    }
                }
            }
        }
        if (dp[nwild][namelen]) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}
