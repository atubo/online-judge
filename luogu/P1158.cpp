// https://www.luogu.org/problem/show?pid=1158
// 导弹拦截

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;

int cost(int x1, int y1, int x2, int y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int main() {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

    int N;
    scanf("%d", &N);

    vector<PII> A(N);
    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        A[i] = make_pair(cost(x1, y1, x, y), cost(x2, y2, x, y));
    }
    sort(A.begin(), A.end());
    int maxb = 0;
    int ret = INT_MAX;
    for (int i = N-1; i >= 0; i--) {
        ret = min(ret, A[i].first + maxb);
        maxb = max(maxb, A[i].second);
    }
    printf("%d\n", ret);
    return 0;
}
