// https://www.luogu.org/problem/show?pid=2375
// P2375 动物园

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int64_t MOD = 1000000007L;
const int MAXN = 10000010;
int z[MAXN];

void z_function(const string& s) {
    int n = (int) s.length();
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
}

int64_t mul(int64_t a, int64_t b) {
    return (a * b) % MOD;
}

class BIT {
public:
    // Note size needs to be power of 2
    BIT(int size): N(size) {
        tree = (int64_t*)malloc((size+1) * sizeof(int64_t));
        memset(tree, 0, (size+1) * sizeof(int64_t));
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

BIT fenwick(1048576);

class Solution {
private:
    string S;
public:
    Solution() {
        cin >> S;
    }

    void solve() {
        int N = S.length();
        memset(z, 0, sizeof(z));
        z_function(S);

        fenwick.clear();

        for (int p = 0; p < N; p++) {
            int L = z[p];
            if (L > 0) {
                int q = min(N-1, p + min(p, L) - 1);
                fenwick.set(p+1, 1);
                fenwick.set(q+2, -1);
            }
        }

        int64_t ans = 1;
        for (int i = 0; i < N; i++) {
            ans = mul(ans, fenwick.get(i+1) + 1);
        }
        cout << ans << endl;
    }

};

int main() {
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        Solution solution;
        solution.solve();
    }
    return 0;
}
