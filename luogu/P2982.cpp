// https://www.luogu.org/problem/show?pid=2982
// [USACO10FEB]慢下来Slowing down

#include <bits/stdc++.h>
using namespace std;

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

int order = 1;
const int MAXN = 100010;
vector<int> A;
int first[MAXN], last[MAXN];
vector<vector<int>> adj;

void dfs(int u, int f) {
    first[u] = order++;
    A.push_back(u);
    for (int v: adj[u]) {
        if (v != f) dfs(v, u);
    }
    last[u] = order++;
    A.push_back(u);
}

int main() {
    int N;
    scanf("%d", &N);
    adj.resize(N+1);
    for (int i = 0; i < N-1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> pastures(N+1);
    vector<int> cows(N+1);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &pastures[i]);
        cows[pastures[i]] = i;
    }

    dfs(1, 0);

    BIT ft(262144);
    vector<int> ret(N+1);
    for (int i = 1; i <= N; i++) {
        int p = pastures[i];
        int x = first[p], y = last[p];
        ret[i] = ft.get(x);
        ft.set(x, 1);
        ft.set(y+1, -1);
    }
    for (int i = 1; i <= N; i++) {
        printf("%d\n", ret[i]);
    }
    return 0;
}
