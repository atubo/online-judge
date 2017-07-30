// https://leetcode.com/problems/number-of-islands-ii/description/
// 305. Number of Islands II

#include <bits/stdc++.h>
using namespace std;

class UnionFind {
private:
    const int N;
    vector<int> rank;
    vector<int> parent;
    vector<int> size;

    void makeSet(int k) {
        assert(0 <= k && k < N);

        parent[k] = k;
        rank[k] = 0;
        size[k] = 1;
    }

    void link(int u, int v) {
        if (rank[u] > rank[v]) {
            parent[v] = u;
            size[u] += size[v];
        } else {
            parent[u] = v;
            size[v] += size[u];
            if (rank[u] == rank[v]) {
                rank[v]++;
            }
        }
    }

public:
    UnionFind(int n): N(n) {
        rank.resize(N);
        parent.resize(N);
        size.resize(N);

        reset();
    }

    void reset() {
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

    int count(int u) {
        return size[find(u)];
    }
};

class Solution {
    using PII = pair<int, int>;
public:
    vector<int> numIslands2(int m, int n, vector<PII>& positions) {
        int DX[4] = {1, 0, -1, 0};
        int DY[4] = {0, 1, 0, -1};
        vector<int> ret;
        UnionFind uf(m*n);
        int num = 0;
        set<PII> added;
        for (const auto& pos: positions) {
            int idx = toIdx(pos.first, pos.second, n);
            num++;
            for (int d = 0; d < 4; d++) {
                int r = pos.first + DX[d];
                int c = pos.second + DY[d];
                if (inRange(r, c, m, n) && added.count(make_pair(r, c)) > 0) {
                    int nbr = toIdx(r, c, n);
                    if (uf.find(idx) != uf.find(nbr)) {
                        uf.join(idx, nbr);
                        num--;
                    }
                }
            }
            ret.push_back(num);
            added.insert(pos);
        }
        return ret;
    }

    int toIdx(int r, int c, int n) {
        return r*n + c;
    }

    bool inRange(int r, int c, int m, int n) {
        return 0 <= r && r < m && 0 <= c && c < n;
    }
};

int main() {
    return 0;
}
