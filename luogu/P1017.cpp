// https://www.luogu.org/problem/show?pid=1017
// P1017 进制转换

#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

int main() {
    int N, R;
    scanf("%d %d", &N, &R);
    R = -R;

    if (N == 0) {
        printf("0=0(base%d)\n", -R);
        return 0;
    }

    int N0 = N;

    vector<int> ans;
    int d = 1;
    while (N != 0) {
        int x = abs(N) % R;
        if (d * N > 0) {
            ans.push_back(x);
            N = (N - x * d) / R;
        } else {
            if (x > 0) {
                ans.push_back(R - x);
                N = (N - (R-x) * d) / R;
            } else {
                ans.push_back(0);
                N = N / R;
            }
        }
        d = -d;
    }

    string ALPHA = "0123456789ABCDEFGHIJ";

    printf("%d=", N0);
    for (int i = (int)ans.size()-1; i >= 0; i--) {
        printf("%c", ALPHA[ans[i]]);
    }
    printf("(base%d)\n", -R);

    return 0;
}
