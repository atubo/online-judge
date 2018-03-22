// https://www.luogu.org/problemnew/show/P2444
// [POI2000]病毒

#include <bits/stdc++.h>
using namespace std;

class AhoCorasick {
public:
    const static int MAXN = 40000;

    vector<array<int, 2>> to;
    vector<array<int, 2>> to2;
    int sz = 1;
    int *link;  // blue link in the wiki
    int *que;
    bool *mark, *instack, *vis;
    int keywordIndex;
    stack<int> stk;

    AhoCorasick(): to(MAXN), to2(MAXN), keywordIndex(0) {
        link = new int[MAXN]{};
        que  = new int[MAXN]{};
        mark = new bool[MAXN]{};
        instack = new bool[MAXN]{};
        vis = new bool[MAXN]{};
    }

    ~AhoCorasick() {
        delete[] link;
        delete[] que;
        delete[] mark;
        delete[] instack;
        delete[] vis;
    }

    void add_str(const string &s) {
        int v = 0;
        for(auto c: s) {
            int i = c - '0';
            if(!to[v][i]) to[v][i] = sz++;
            v = to[v][i];
        }
        mark[v] = true;
    }

    void push_links() {
        link[0] = -1;
        int st = 0, fi = 1;
        que[0] = 0;
        while (st < fi) {
            int v = que[st++];
            for(int c = 0; c < (int)to[v].size(); c++) {
                int u = to[v][c];
                if (u > 0) {
                    int j = link[v];
                    while(j != -1 && !to[j][c]) j = link[j];
                    if(j != -1) link[u] = to[j][c];
                    if (mark[link[u]]) mark[u] = true;
                    que[fi++] = u;
                }
            }
        }
    }

    void connect() {
        int st = 0, fi = 1;
        que[0] = 0;
        while (st < fi) {
            int v = que[st++];
            for (int c = 0; c < (int)to[v].size(); c++) {
                int u = to[v][c];
                if (u == 0 && link[v] >= 0) {
                    to2[v][c] = to2[link[v]][c];
                } else {
                    to2[v][c] = to[v][c];
                    if (u > 0) que[fi++] = u;
                }
            }
        }
    }

    bool dfs(int u) {
        stk.push(u);
        instack[u] = true;
        vis[u] = true;
        for (int i = 0; i < 2; i++) {
            int v = to2[u][i];
            if (mark[v]) continue;
            if (!vis[v]) {
                bool ok = dfs(v);
                if (ok) return true;
            } else if (instack[v]) {
                while (!stk.empty()) {
                    //printf("%d ", stk.top());
                    stk.pop();
                }
                return true;
            }
        }
        instack[u] = false;
        stk.pop();
        return false;
    }
};

int N;

int main() {
    scanf("%d", &N);
    AhoCorasick ac;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        ac.add_str(s);
    }
    ac.push_links();
    ac.connect();
    bool ok = ac.dfs(0);
    if (ok) printf("TAK");
    else printf("NIE");

    return 0;
}
