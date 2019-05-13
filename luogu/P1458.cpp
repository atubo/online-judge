// https://www.luogu.org/problemnew/show/P1458
// 顺序的分数 Ordered Fractions

#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

int N;
struct Fraction {
    int p, q;
    bool operator > (const Fraction& other) const {
        return p * other.q > q * other.p;
    }
};

int main() {
    scanf("%d", &N);
    priority_queue<Fraction, vector<Fraction>, greater<Fraction>> pq;
    printf("0/1\n");
    for (int i = 1; i <= N; i++) {
        pq.push({1, i});
    }
    while (!pq.empty()) {
        auto f = pq.top();
        pq.pop();
        printf("%d/%d\n", f.p, f.q);
        int p = f.p + 1;
        while (p < f.q && gcd(p, f.q) > 1) p++;
        if (p < f.q) pq.push({p, f.q});
    }

    return 0;
}
