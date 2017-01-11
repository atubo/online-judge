// https://www.codechef.com/MARCH14/problems/GERALD07
// Chef and Graph Queries

#include <bits/stdc++.h>
using namespace std;

int nowAns;

class UnionFindRB {
private:
    const int N;
    vector<int> parentTentative;
    vector<int> parentCommitted;

    vector<bool> mark;
    vector<int> cg; // nodes to be reset

    void makeSet(int k) {
        assert(0 <= k && k < N);

        parentTentative[k] = k;
        parentCommitted[k] = k;
    }

    void linkCommitted(int u, int v) {
        parentCommitted[u] = v;
    }

    void linkTentative(int u, int v) {
        parentTentative[u] = v;
    }

public:
    UnionFindRB(int n): N(n) {
        parentTentative.resize(N);
        parentCommitted.resize(N);

        mark.resize(N);
        cg.reserve(N);

        for (int i = 0; i < N; i++) {
            makeSet(i);
        }
    }

    int findCommitted(int k) {
        if (parentCommitted[k] == k) return k;
        int root = findCommitted(parentCommitted[k]);
        return parentCommitted[k] = root;
    }

    int findTentative(int k) {
        if (parentTentative[k] == k) return k;
        int root = findTentative(parentTentative[k]);
        return parentTentative[k] = root;
    }

    int find(int k) {
        k = findCommitted(k);
        return findTentative(k);
    }

    void joinCommit(int u, int v) {
        u = findCommitted(u);
        v = findCommitted(v);
        if (u != v) {
            linkCommitted(u, v);
            nowAns--;
        }
    }

    void joinTentative(int u, int v) {
        u = findCommitted(u);
        v = findCommitted(v);
        if (!mark[u]) {
            mark[u] = true;
            cg.push_back(u);
        }
        if (!mark[v]) {
            mark[v] = true;
            cg.push_back(v);
        }

        u = findTentative(u);
        v = findTentative(v);
        if (u != v) {
            linkTentative(u, v);
            nowAns--;
        }
    }

    void rollback() {
        for (int i = (int)cg.size()-1; i >= 0; i--) {
            int u = cg[i];
            mark[u] = false;
            parentTentative[u] = u;
        }
    }

    void resetCommitted() {
        for (int i = 0; i < N; i++) {
            parentCommitted[i] = i;
        }
    }
};
class Solution {
    using PII = pair<int, int>;
    struct Query {
        int l, r, id;
        int block_id;

        bool operator < (const Query& other) const {
            return make_pair(block_id, r) < make_pair(other.block_id, other.r);
        }
    };

private:
    int N, M, Q;
    int BLOCK_SIZE;
    vector<Query> queries;
    vector<int> ans;
    vector<PII> edges;
    int lcur, rcur;
    UnionFindRB* uf;

    void add(int x, bool tp) {
        if (lcur >= rcur) return;
        int u, v;
        tie(u, v) = edges[x];
        if (tp) {
            uf->joinTentative(u, v);
        } else {
            uf->joinCommit(u, v);
        }
    }

public:
    Solution() {
        scanf("%d %d %d", &N, &M, &Q);
        queries.resize(Q);
        ans.resize(Q);

        edges.resize(M);
        for (int i = 0; i < M; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            edges[i] = make_pair(u-1, v-1);
        }

        BLOCK_SIZE = int(ceil(pow(M, 0.5)));
        for (int i = 0; i < Q; i++) {
            int l, r;
            scanf("%d %d", &l, &r);
            l--;
            queries[i].l = l;
            queries[i].r = r;
            queries[i].id = i;
            queries[i].block_id = l/BLOCK_SIZE;
        }

        ans.resize(queries.size());

        uf = new UnionFindRB(N);
        nowAns = N;
    }

    ~Solution() {
        delete uf;
        uf = NULL;
    }

    void solve() {
        sort(queries.begin(), queries.end());

        for (int i = 0, tail; i < (int)queries.size(); i++) {
            const Query& q = queries[i];
            if (i == 0 || q.block_id != queries[i-1].block_id) {
                // initialize permanent part and nowAns
                lcur = tail = min((q.block_id+1) * BLOCK_SIZE, M);
                rcur = -1;
                nowAns = N;
                uf->resetCommitted();
            }
            while (rcur < q.r) add(rcur++, 0);
            int tmp = nowAns;
            while (lcur > q.l) add(--lcur, 1);
            ans[q.id] = nowAns;
            nowAns = tmp;
            uf->rollback();
            lcur = tail;
        }

        for (int x: ans) {
            printf("%d\n", x);
        }
    }
};

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        Solution solution;
        solution.solve();
    }
    return 0;
}
