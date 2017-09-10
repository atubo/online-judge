// https://www.luogu.org/problem/show?pid=2733
// 家的范围 Home on the Range

#include <bits/stdc++.h>
using namespace std;

int N;
bool ranch[260][260];
int dp[260][260];

int min3(int a, int b, int c) {
    return min(a, min(b, c));
}

class BIT {
public:
    // Note size needs to be power of 2
    BIT(int size): N(size) {
        tree = (int64_t*)malloc((size+1) * sizeof(int64_t));
        clear();
    }
    
    ~BIT() {
        free(tree);
        tree = NULL;
    }

    void clear() {
        memset(tree, 0, (N+1) * sizeof(int64_t));
    }

    // add v to value at x
    void set(int x, int v) {
        while(x <= N) {
            tree[x] += v;
            x += (x & -x);
        }
    }

    // get cumulative sum up to and including x
    int64_t get(int x) const {
        int64_t res = 0;
        while(x) {
            res += tree[x];
            x -= (x & -x);
        }
        return res;
    }

    // get result for [x, y]
    int64_t get(int x, int y) const {
        return get(y) - (x > 1 ? get(x-1) : 0);
    }

    // get largest value with cumulative sum less than or equal to x;
    // for smallest, pass x-1 and add 1 to result
    int getind(int x) {
        int idx = 0, mask = N;
        while(mask && idx < N) {
            int t = idx + mask;
            if(x >= tree[t]) {
                idx = t;
                x -= tree[t];
            }
            mask >>= 1;
        }
        return idx;
    }

private:
    int64_t* tree;
    const int N;
};

int main() {
    BIT ft(256);

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < N; j++) {
            ranch[i][j] = s[j] - '0';
        }
    }
    for (int i = 0; i < N; i++) {
        dp[0][i] = ranch[0][i];
        dp[i][0] = ranch[i][0];
    }
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            if (ranch[i][j]) {
                dp[i][j] = 1 + min3(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]);
                ft.set(2, 1);
                ft.set(dp[i][j]+1, -1);
            }
        }
    }

    for (int i = 2; i <= N; i++) {
        int d = ft.get(i);
        if (d > 0) {
            printf("%d %d\n", i, d);
        }
    }

    return 0;
}
