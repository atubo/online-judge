// https://www.luogu.org/problemnew/show/P2397
// yyy loves Maths VI (mode)

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;

int main() {
    PII stat = make_pair(0, 0);
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
        if (stat.second == 0) {
            stat = make_pair(x, 1);
        } else {
            if (stat.first == x) stat.second++;
            else stat.second--;
        }
    }
    printf("%d\n", stat.first);
    return 0;
}
