// https://www.luogu.org/problemnew/show/P2285
// [HNOI2004]打鼹鼠

#include <bits/stdc++.h>
using namespace std;

const int MAXM = 10010;
int N, M;

struct Mole {
    int x, y, t, maxval;
} mole[MAXM];

bool reachable(int j, int i) {
    return mole[i].t - mole[j].t >= abs(mole[i].x - mole[j].x) +
        abs(mole[i].y - mole[j].y);
}

int main() {
    scanf("%d%d", &N, &M);
    int ret = 0;
    for (int i = 0; i < M; i++) {
        int t, x, y;
        scanf("%d%d%d", &t, &x, &y);
        mole[i] = {x, y, t, 1};
        for (int j = i-1; j >= 0; j--) {
            if (reachable(j, i)) {
                mole[i].maxval = max(mole[i].maxval, mole[j].maxval+1);
            }
        }
        ret = max(ret, mole[i].maxval);
    }
    printf("%d\n", ret);

    return 0;
}
