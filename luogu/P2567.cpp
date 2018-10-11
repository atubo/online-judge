// https://www.luogu.org/problemnew/show/P2567
// [SCOI2010]幸运数字

#include <bits/stdc++.h>
using namespace std;

int64_t A, B;

vector<int64_t> pure_lucky;
int64_t cnt[1000];

void init() {
    vector<vector<int64_t>> lucky(11);
    lucky[0].push_back(0);
    for (int d = 1; d <= 10; d++) {
        for (int64_t x: lucky[d-1]) {
            lucky[d].push_back(x*10+6);
            lucky[d].push_back(x*10+8);
            pure_lucky.push_back(x*10+6);
            pure_lucky.push_back(x*10+8);
        }
    }
    for (int i = 0; i < (int)pure_lucky.size(); i++) {
        if (pure_lucky[i] < 0) continue;
        for (int j = i+1; j < (int)pure_lucky.size(); j++) {
            if (pure_lucky[j] % pure_lucky[i] == 0) {
                pure_lucky[j] = -1;
            }
        }
    }
    auto it = partition(pure_lucky.begin(), pure_lucky.end(),
                        [](int64_t em) {return em > 0;});
    pure_lucky.erase(it, pure_lucky.end());
    sort(pure_lucky.begin(), pure_lucky.end());
}

int64_t gcd(int64_t x, int64_t y) {
    if (y == 0) return x;
    return gcd(y, x%y);
}

int64_t lcm(int64_t x, int64_t y) {
    int64_t g = gcd(x, y);
    return x/g * y;
}

int64_t rangeCount(int64_t l, int64_t r, int64_t x) {
    l = l/x + (l%x != 0);
    r /= x;
    return r - l + 1;
}

void search(int p, int m, int64_t curr) {
    if (p < 0) return;
    int64_t x = pure_lucky[p];
    if (1.0 * x /gcd(x, curr) * curr <= B) {
        int64_t next = lcm(x, curr);
        if (next <= B) {
            cnt[m+1] += rangeCount(A, B, next);
            search(p-1, m+1, next);
        }
    }
    search(p-1, m, curr);
}

int main() {
    scanf("%ld%ld", &A, &B);
    init();
    search(pure_lucky.size()-1, 0, 1);
    int64_t ans = 0;
    for (int64_t x: pure_lucky) {
        if (x <= B) ans += rangeCount(A, B, x);
    }
    for (int i = 2; i < 1000; i++) {
        if (i&1) ans += cnt[i];
        else ans -= cnt[i];
    }
    printf("%ld\n", ans);
    return 0;
}
