// https://www.luogu.org/problem/show?pid=1972
// [SDOI2009]HH的项链
#include <inttypes.h>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

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

typedef pair<int, int> PII;
typedef pair<pair<int, int>, int> TIII;

vector<int> normalize(vector<PII>& A) {
    const int N = A.size();
    sort(A.begin(), A.end());
    vector<int> ret(N);
    int curr = -1;
    for (int i = 0; i < N; i++) {
        if (i == 0 || A[i].first != A[i-1].first) {
            curr++;
        }
        ret[A[i].second] = curr;
    }
    return ret;
}

int main() {
    int N;
    scanf("%d", &N);
    int a, b;
    vector<PII> A(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a);
        A[i] = make_pair(a, i);
    }
    vector<int> B = normalize(A);

    int maxelem = *max_element(B.begin(), B.end());
    vector<int> last(maxelem+1, N);
    vector<int> next(N);
    for (int i = N-1; i >= 0; i--) {
        next[i] = last[B[i]];
        last[B[i]] = i;
    }

    int M;
    scanf("%d", &M);
    vector<TIII> queries(M);
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        queries[i] = make_pair(make_pair(a, b), i);
    }
    sort(queries.begin(), queries.end());

    BIT ft(65536);
    vector<bool> seen(maxelem+1, false);
    for (int i = 0; i < N; i++) {
        if (!seen[B[i]]) {
            ft.set(i+1, 1);
            seen[B[i]] = true;
        }
    }

    vector<int> ans(M);
    int p = 0;
    for (int i = 0; i < M; i++) {
        int q = queries[i].first.first;
        for (int j = p; j < q; j++) {
            ft.set(next[j]+1, 1);
        }
        p = q;
        a = queries[i].first.first;
        b = queries[i].first.second;

        ans[queries[i].second] = (ft.get(b+1) - (a == 0 ? 0 : ft.get(a)));
    }

    for (int i = 0; i < M; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}
