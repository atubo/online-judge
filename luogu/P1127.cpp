// https://www.luogu.org/problemnew/show/P1127
// 词链

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int id, from, to;
    bool operator < (const Edge &other) const {
        return id < other.id;
    }
};

// For directed graph
class Hierholzer {
public:
    Hierholzer(int n): n_(n), edges_(n) {}

    void addEdge(int u, const Edge &e) {
        edges_[u].push_back(e);
    }

    vector<int> solve(int s) {
        vector<int> path;
        vector<deque<Edge>> edges = edges_;  // make a copy
        stack<Edge> st;
        st.push({-1, -1, s});
        while (!st.empty()) {
            Edge e = st.top();
            st.pop();
            if (!edges[e.to].empty()) {
                dfs(e, edges, st);
            } else {
                path.push_back(e.id);
            }
        }
        reverse(path.begin(), path.end());
        return path;
    }

    int n_;
    vector<deque<Edge>> edges_;

private:
    void dfs(const Edge &e, vector<deque<Edge>> &edges, stack<Edge> &st) {
        st.push(e);
        int u = e.to;
        if (!edges[u].empty()) {
            const auto &en = edges[u].front();
            edges[u].pop_front();
            dfs(en, edges, st);
        }
    }
};

int N;
int in[26], out[26];
bool neigh[26][26];

int findStart() {
    int p1 = -1, n1 = -1;
    for (int i = 0; i < 26; i++) {
        if (out[i] - in[i] == 0) continue;
        else if (out[i] - in[i] == 1) {
            if (p1 != -1) return -1;
            p1 = i;
        } else if (out[i] - in[i] == -1) {
            if (n1 != -1) return -1;
            n1 = i;
        } else {
            return -1;
        }
    }
    if (!((p1 >= 0 && n1 >= 0) || (p1 == -1 && n1 == -1))) return -1;
    if (p1 >= 0) return p1;

    int s = 26;
    for (int i = 25; i >= 0; i--) {
        if (out[i] > 0) s = i;
    }
    return s;
}

void floyd() {
    for (int k = 0; k < 26; k++) {
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                neigh[i][j] |= neigh[i][k] && neigh[k][j];
            }
        }
    }
}

int main() {
    scanf("%d", &N);
    vector<string> words(N);
    for (int i = 0; i < N; i++) {
        cin >> words[i];
    }
    sort(words.begin(), words.end());

    vector<vector<Edge>> adj(26);
    for (int i = 0; i < N; i++) {
        const auto &w = words[i];
        int b = w.front() - 'a';
        int e = w.back() - 'a';
        adj[b].push_back({i, b, e});
        out[b]++;
        in[e]++;
        neigh[b][e] = true;
    }
    floyd();
    bool found = false;
    for (int i = 0; i < 26; i++) {
        bool ok = true;
        for (int j = 0; j < 26; j++) {
            if (in[j] == 0) continue;
            if (!neigh[i][j]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            found = true;
            break;
        }
    }

    if (!found) {
        printf("***");
        return 0;
    }

    for (int i = 0; i < 26; i++) {
        sort(adj[i].begin(), adj[i].end());
    }

    Hierholzer hh(26);
    for (int i = 0; i < 26; i++) {
        for (const auto &e: adj[i]) {
            hh.addEdge(i, e);
        }
    }

    int s = findStart();
    if (s == -1) {
        printf("***");
        return 0;
    }

    vector<int> path = hh.solve(s);
    for (int i = 1; i < (int)path.size(); i++) {
        printf("%s", words[path[i]].c_str());
        if (i != (int)path.size()-1) printf(".");
    }

    return 0;
}
