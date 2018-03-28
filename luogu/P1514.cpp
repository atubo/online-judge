// https://www.luogu.org/problemnew/show/P1514
// 引水入城

#include <bits/stdc++.h>
using namespace std;

class Mask {
    // 500-bit
    static const int SZ = 16;
private:
    unsigned int bits[SZ];
public:
    Mask() {
        memset(bits, 0, sizeof(bits));
    }

    void set(int i) {
        bits[i/32] |= (1 << (i%32));
    }

    void unset(int i) {
        bits[i/32] &= ~(1 << (i%32));
    }

    int get(int i) const {
        // return 0 or 1
        return (bits[i/32] >> (i%32)) & 1;
    }

    Mask& operator |= (const Mask &other) {
        for (int i = 0; i < SZ; i++) {
            bits[i] |= other.bits[i];
        }
        return *this;
    }

    Mask& operator ^= (const Mask &other) {
        for (int i = 0; i < SZ; i++) {
            bits[i] ^= other.bits[i];
        }
        return *this;
    }

    int popcount() {
        int ret = 0;
        for (int i = 0; i < SZ; i++) {
            ret += __builtin_popcount(bits[i]);
        }
        return ret;
    }

    string toString(int n) {
        string ret(n, '0');
        for (int i = 0; i < n; i++) {
            ret[n-1-i] = get(i) + '0';
        }
        return ret;
    }
};

struct City {
    int h;
    int row, col;
    bool operator < (const City &other) const {
        if (h < other.h) return true;
        if (h > other.h) return false;
        if (row > other.row) return true;
        if (row < other.row) return false;
        return col > other.col;
    }
};

const int MAXN = 510;
int N, M;
Mask masks[MAXN][MAXN];

int H[MAXN][MAXN];
bool vis[MAXN][MAXN];

const int DX[4] = {0, -1, 0, 1};
const int DY[4] = {1, 0, -1, 0};

bool inRange(int row, int col) {
    return 0 <= row && row < N && 0 <= col && col < M;
}


void flow() {
    priority_queue<City> pq;
    for (int i = 0; i < M; i++) {
        pq.push({H[0][i], 0, i});
        masks[0][i].set(i);
    }
    while (!pq.empty()) {
        City c = pq.top();
        pq.pop();
        int row0 = c.row, col0 = c.col, h0 = c.h;
        for (int d = 0; d < 4; d++) {
            int row1 = row0 + DX[d];
            int col1 = col0 + DY[d];
            if (inRange(row1, col1) && H[row1][col1] < h0) {
                masks[row1][col1] |= masks[row0][col0];
                if (!vis[row1][col1]) {
                    pq.push({H[row1][col1], row1, col1});
                    vis[row1][col1] = true;
                }
            }
        }
    }
}

struct Range {
    int x = MAXN;
    int y = -1;
    bool operator < (const Range &other) const {
        if (y < other.y) return true;
        if (y > other.y) return false;
        return x < other.x;
    }
};

void solve() {
    int ans = 0;
    for (int j = 0; j < M; j++) {
        if (masks[N-1][j].popcount() == 0) {
            ans++;
        }
    }
    if (ans > 0) {
        printf("0\n%d", ans);
        return;
    }

    vector<Range> ranges(M);
    for (int j = 0; j < M; j++) {
        for (int i = 0; i < M; i++) {
            if (masks[N-1][j].get(i) == 1) {
                ranges[i].x = min(j, ranges[i].x);
                ranges[i].y = max(j, ranges[i].y);
            }
        }
    }
    sort(ranges.begin(), ranges.end());
    vector<int> dp(M+1, 1e5);
    dp[0] = 0;
    for (const auto &r: ranges) {
        int x = r.x+1, y = r.y+1;
        int ret = 1e5;
        for (int j = x-1; j <= y; j++) {
            ret = min(ret, dp[j]);
        }
        dp[y] = min(dp[y], ret+1);
    }
    printf("1\n%d", dp[M]);
}


int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &H[i][j]);
        }
    }
    flow();
    solve();
    return 0;
}
