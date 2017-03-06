// https://www.luogu.org/problem/show?pid=1333
// 瑞瑞的木棍

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;

map<int64_t, int> toId;
int N;
int SZ;
int deg[250010];

const int BUFSIZE = 24*250000;
char buf[BUFSIZE];
char *ptr = buf;

int64_t read() {
    int64_t ret = 0;
    while ('a' <= *ptr && *ptr <= 'z') {
        ret = ret * 26 + *(ptr++) - 'a';
    }
    while (ptr-buf < SZ && (*ptr < 'a' || *ptr > 'z')) ptr++;
    return ret;
}


class UnionFind {
private:
    const int N;
    vector<int> rank;
    vector<int> parent;

    void makeSet(int k) {
        assert(0 <= k && k < N);

        parent[k] = k;
        rank[k] = 0;
    }

    void link(int u, int v) {
        if (rank[u] > rank[v]) {
            parent[v] = u;
        } else {
            parent[u] = v;
            if (rank[u] == rank[v]) {
                rank[v]++;
            }
        }
    }

public:
    UnionFind(int n): N(n) {
        rank.resize(N);
        parent.resize(N);

        for (int i = 0; i < N; i++) {
            makeSet(i);
        }
    }

    int find(int k) {
        if (parent[k] == k) return k;
        int root = find(parent[k]);
        return parent[k] = root;
    }

    void join(int u, int v) {
        link(find(u), find(v));
    }
};

bool solve(const vector<PII>& edges) {
    UnionFind uf(N);
    int ncomp = N;
    for (const auto& e: edges) {
        int u = e.first, v = e.second;
        if (uf.find(u) != uf.find(v)) {
            uf.join(u, v);
            ncomp--;
        }
    }
    if (ncomp > 1) return false;
    int oddCount = 0;
    for (int i = 0; i < N; i++) {
        oddCount += (deg[i] & 1);
    }
    return oddCount == 0 || oddCount == 2;

}

int main() {
    vector<PII> edges;
    SZ = fread(buf, 1, BUFSIZE, stdin);

    while (true) {
        int64_t a = read();
        int64_t b = read();
        if (toId.count(a) == 0) {
            toId.insert(make_pair(a, toId.size()));
        }
        if (toId.count(b) == 0) {
            toId.insert(make_pair(b, toId.size()));
        }
        int u = toId[a];
        int v = toId[b];
        edges.push_back(make_pair(u, v));
        deg[u]++;
        deg[v]++;
        if (ptr - buf == SZ) break;
    }
    N = toId.size();

    bool possible = solve(edges);
    printf("%s\n", possible ? "Possible" : "Impossible");

    return 0;
}
