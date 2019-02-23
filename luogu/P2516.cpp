// https://www.luogu.org/problemnew/show/P2516
// [HAOI2010]最长公共子序列

#include <bits/stdc++.h>
using namespace std;

const int MOD = 100000000;

class BIT {
public:
    // 1-indexed
    BIT(int size): N(size) {
        tree = (int*)malloc((size+1) * sizeof(int));
        clear();
    }

    ~BIT() {
        free(tree);
        tree = NULL;
    }

    void clear() {
        memset(tree, 0, (N+1) * sizeof(int));
    }

    // add v to value at x
    void set(int x, int v) {
        while(x <= N) {
            (tree[x] += v) %= MOD;
            x += (x & -x);
        }
    }

    // get cumulative sum up to and including x
    int get(int x) const {
        int64_t res = 0;
        while(x) {
            (res += tree[x]) %= MOD;
            x -= (x & -x);
        }
        return res;
    }

private:
    int* tree;
    const int N;
};

const int MAXN = 5010;
string S, T;
int N, M;
int dp[2][MAXN];

struct Data {
    int l, p, c;
};

void solve_lcs() {
    N = S.length() - 1;
    M = T.length() - 1;
    int maxl = min(N, M);
    vector<BIT*> bits(maxl+1);
    for (int i = 1; i <= maxl; i++) {
        bits[i] = new BIT(N);
    }
    vector<Data> update;
    for (int i = 1; i <= M; i++) {
        update.clear();
        int curr = i & 1;
        int prev = curr ^ 1;
        for (int j = 1; j <= N; j++) {
            if (S[j-1] == T[i-1]) {
                int len = 1 + dp[prev][j-1];
                dp[curr][j] = len;
                int cnt = (len == 1 ? 1 : bits[len-1]->get(j-1));
                update.push_back({len, j, cnt});
            } else {
                dp[curr][j] = max(dp[curr][j-1], dp[prev][j]);
            }
        }
        for (const auto &d: update) {
            bits[d.l]->set(d.p, d.c);
        }
    }
    int ans = dp[M&1][N];
    printf("%d\n", ans);
    printf("%d", bits[ans]->get(N));
}

int main() {
    cin >> S >> T;
    solve_lcs();

    return 0;
}
