// https://www.luogu.org/problem/show?pid=1333
// 瑞瑞的木棍

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int64_t, int64_t>;

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

bool solve(const vector<PII>& edges, const vector<int64_t>& colors) {
    UnionFind uf(N);
    int ncomp = N;
    for (const auto& e: edges) {
        int u = lower_bound(colors.begin(), colors.end(), e.first) - colors.begin();
        int v = lower_bound(colors.begin(), colors.end(), e.second) - colors.begin();
        deg[u]++;
        deg[v]++;
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
    vector<int64_t> colors;
    SZ = fread(buf, 1, BUFSIZE, stdin);

    while (true) {
        int64_t a = read();
        int64_t b = read();
        edges.push_back(make_pair(a, b));
        colors.push_back(a);
        colors.push_back(b);
        if (ptr - buf == SZ) break;
    }
    sort(colors.begin(), colors.end());
    colors.erase(unique(colors.begin(), colors.end()), colors.end());
    N = colors.size();

    bool possible = solve(edges, colors);
    printf("%s\n", possible ? "Possible" : "Impossible");

    return 0;
}
