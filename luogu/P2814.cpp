// https://www.luogu.org/problem/show?pid=2814
// 家谱（gen）

#include <bits/stdc++.h>
using namespace std;

class UnionFind {
private:
    const int N;
    vector<int> parent;

    void makeSet(int k) {
        assert(0 <= k && k < N);

        parent[k] = k;
    }

    void link(int u, int v) {
        parent[u] = v;
    }

public:
    UnionFind(int n): N(n) {
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

struct Query {
    int type;
    int id;
    vector<int> children;

    Query(int type_, int id_): type(type_), id(id_) {}
};

class Solution {
private:
    map<string, int> nameToId;
    vector<string> names;
    vector<Query> queries;
public:
    Solution() {
        string s;
        cin >> s;
        while (s != "$") {
            string name = s.substr(1);
            if (nameToId.count(name) == 0) {
                nameToId.insert(make_pair(name, nameToId.size()));
                names.push_back(name);
            }
            int id = nameToId.at(name);
            char c = s[0];
            if (c == '#') {
                queries.push_back(Query(0, id));
            } else if (c == '+') {
                queries.back().children.push_back(id);
            } else {
                queries.push_back(Query(1, id));
            }
            cin >> s;
        }
    }

    void solve() {
        int n = nameToId.size();
        UnionFind uf(n);
        for (const Query& q: queries) {
            if (q.type == 0) {
                int father = q.id;
                for (int child: q.children) {
                    uf.join(child, father);
                }
            } else {
                cout << names[q.id] << " " << names[uf.find(q.id)] << endl;
            }
        }
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
