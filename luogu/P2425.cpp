// https://www.luogu.org/problemnew/show/P2425
// 小红帽的回文数

#include <bits/stdc++.h>
using namespace std;

int T;
int64_t A;
int64_t B[36];

bool isPalindrome(int64_t a, int x) {
    int p = 0;
    while (a) {
        B[p++] = a % x;
        a /= x;
    }
    for (int i = 0; 2*i <= p-1; i++) {
        if (B[i] != B[p-1-i]) return false;
    }
    return true;
}

void solve() {
    scanf("%ld", &A);
    if (A <= 3) {
        printf("2\n");
        return;
    }
    int s = sqrt(A) + 0.01;
    int64_t t = A - 1;
    for (int i = s-1; i > 1; i--) {
        if (A % i == 0) {
            t = A / i - 1;
            break;
        }
    }

    for (int i = 2; i <= s; i++) {
        if (isPalindrome(A, i)) {
            t = i;
            break;
        }
    }
    printf("%ld\n", t);
}

int main() {
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
