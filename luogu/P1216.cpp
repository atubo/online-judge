// https://www.luogu.org/problem/show?pid=1216
// [USACO1.5]数字金字塔 Number Triangles

#include <bits/stdc++.h>
using namespace std;

int main() {
    int R;
    scanf("%d", &R);
    vector<int> dpPrev(R), dpCurr(R);
    scanf("%d", &dpPrev[0]);
    for (int r = 2; r <= R; r++) {
        for (int i = 0; i < r; i++) {
            scanf("%d", &dpCurr[i]);
        }
        dpCurr[0] += dpPrev[0];
        dpCurr[r-1] += dpPrev[r-2];
        for (int i = 1; i < r-1; i++) {
            dpCurr[i] += max(dpPrev[i], dpPrev[i-1]);
        }
        swap(dpPrev, dpCurr);
    }
    printf("%d\n", *max_element(dpPrev.begin(), dpPrev.end()));
    return 0;
}
