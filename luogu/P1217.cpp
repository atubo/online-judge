// https://www.luogu.org/problem/show?pid=1217
// [USACO1.5]回文质数 Prime Palindromes

#include <bits/stdc++.h>
using namespace std;

int P10[] = {1, 10, 100, 1000, 10000, int(1e5), int(1e6), int(1e7), int(1e8)};

void palindrome(int i, int j, int x, vector<int> &res) {
    if (i < j) {
        res.push_back(x);
        return;
    }

    if (i == j) {
        for (int d = 0; d < 10; d++) {
            palindrome(i-1, j+1, x + d * P10[i], res);
        }
    } else {
        for (int d = 0; d < 10; d++) {
            palindrome(i-1, j+1, x + d * (P10[i] + P10[j]), res);
        }
    }
}

vector<int> candidates = {5, 7};

void getCandidates(int n) {
    for (int d = 1; d < 10; d += 2) {
        palindrome(n-2, 1, d * (P10[n-1] + P10[0]), candidates);
    }
}

bool isPrime(int x) {
    for (int i = 3; i * i <= x; i += 2) {
        if (x % i == 0) return false;
    }
    return true;
}

int main() {
    for (int n = 2; n < 9; n++) {
        getCandidates(n);
    }
    int a, b;
    scanf("%d%d", &a, &b);
    auto start = lower_bound(candidates.begin(), candidates.end(), a);
    auto end   = upper_bound(candidates.begin(), candidates.end(), b);
    for (auto it = start; it != end; ++it) {
        if (isPrime(*it)) {
            printf("%d\n", *it);
        }
    }
    return 0;
}
