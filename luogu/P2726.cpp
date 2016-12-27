// https://www.luogu.org/problem/show?pid=2726
// P2726 阶乘 Factorials
// see http://blog.sina.com.cn/s/blog_a661ecd50101499c.html
#include <iostream>
using namespace std;

int powerOf2[5] = {1, 2, 4, 8, 6};

int solve(int n) {
    int t = n % 5;
    int k = n / 5;
    int f = 1;
    for (int i = 1; i <= t; i++) {
        f = (f * i) % 10;
    }
    if (k > 0) {
        f = (f * powerOf2[(k-1)%4 + 1] * solve(k)) % 10;
    }
    return f;
}

int main() {
    int n;
    cin >> n;
    cout << solve(n) << endl;
    return 0;
}
