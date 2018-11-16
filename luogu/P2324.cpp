// https://www.luogu.org/problemnew/show/P2324
// [SCOI2005]骑士精神

#include <bits/stdc++.h>
using namespace std;

int DX[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int DY[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int target;

int move1(int c, int x1, int y1, int x2, int y2) {
    c &= (1 << 25) - 1;
    c |= (x2*5+y2) << 25;
    if ((c>>(x2*5+y2)) & 1) {
        c |= 1 << (x1*5+y1);
        c &= ~(1<<(x2*5+y2));
    }
    return c;
}

int cost(int c1, int c2) {
    c1 &= (1 << 25) - 1;
    c2 &= (1 << 25) - 1;
    int d = c1 ^ c2;
    return max(0, __builtin_popcount(d)-1);
}

int bfs(int s) {
    queue<pair<int, int>> q;
    q.push(make_pair(s, 0));
    set<int> visited;
    while (!q.empty()) {
        int c1, d;
        tie(c1, d) = q.front();
        q.pop();
        if (c1 == target) return d;
        if (d == 15) continue;
        if (d + cost(c1, target) > 15) continue;
        int pos = c1 >> 25;
        int x = pos/5, y = pos%5;
        for (int dir = 0; dir < 8; dir++) {
            int x2 = x + DX[dir];
            int y2 = y + DY[dir];
            if (0 <= x2 && x2 < 5 && 0 <= y2 && y2 < 5) {
                int c2 = move1(c1, x, y, x2, y2);
                if (visited.count(c2) == 0) {
                    q.push(make_pair(c2, d+1));
                    visited.insert(c2);
                }
            }
        }
    }
    return -1;
}


int solve() {
    char line[10];
    int code = 0;
    for (int i = 0; i < 5; i++) {
        scanf("%s", line);
        for (int j = 0; j < 5; j++) {
            if (line[j] == '1') code |= 1 << (i*5+j);
            if (line[j] == '*') code |= (i*5+j)<<25;
        }
    }
    //printf("code=%d\n", code);
    //bitset<32> y(code);
    //cout << y << endl;
    int ans = bfs(code);
    return ans;
}

void init() {
    int s[5] = {0, 1, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        for (int j = s[i]; j < 5; j++) {
            target |= 1 << (i*5+j);
        }
    }
    target |= 12 << 25;
    //bitset<32> y(target);
    //cout << y << endl;
}

int main() {
    init();
    int t;
    scanf("%d", &t);
    while (t--) {
        printf("%d\n", solve());
    }
    return 0;
}
