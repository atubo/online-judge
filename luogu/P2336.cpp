// https://www.luogu.org/problemnew/show/P2336
// [SCOI2012]喵星球上的点名

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50010, MAXM = 100010;
int roster[MAXM], student[MAXN];
bool vis[MAXM];
bool visnode[MAXM];

class AhoCorasick {
public:
    const static int MAXN = 1e5 + 42;

    vector<map<int, int> > to;
    vector<set<int> > out;
    int sz = 1;
    int *link, *que;
    int keywordIndex;

    AhoCorasick(): to(MAXN), out(MAXN), keywordIndex(0) {
        link = new int[MAXN]{};
        que  = new int[MAXN]{};
    }

    ~AhoCorasick() {
        delete[] link;
        delete[] que;
    }

    void add_str(const vector<int> &s)
    {
        int v = 0;
        for(auto c: s)
        {
            if(!to[v][c]) to[v][c] = sz++;
            v = to[v][c];
        }
        out[v].insert(keywordIndex++);
    }

    void push_links()
    {
        link[0] = -1;
        int st = 0, fi = 1;
        que[0] = 0;
        while(st < fi)
        {
            int v = que[st++];
            for(auto it: to[v])
            {
                int u = it.second;
                int c = it.first;
                int j = link[v];
                while(j != -1 && !to[j][c]) j = link[j];
                if(j != -1) link[u] = to[j][c];
                out[u].insert(out[link[u]].begin(), out[link[u]].end());
                que[fi++] = u;
            }
        }
    }

    void collect(int q, int sid, int mark) {
        if (mark == 1) {
            if (visnode[q]) return;
            for (int x: out[q]) {
                if (!vis[x]) {
                    roster[x]++;
                    student[sid]++;
                    vis[x] = true;
                }
            }
            visnode[q] = true;
        } else {
            if (!visnode[q]) return;
            for (int x: out[q]) {
                if (vis[x]) vis[x] = false;
            }
            visnode[q] = false;
        }
    }

    void traverse(const vector<int> &array, int sid, int mark) {
        int q = 0;
        for (int c: array) {
            while (q != -1 && to[q][c] == 0) {
                q = link[q];
            }
            if (q != -1) {
                q = to[q][c];
                collect(q, sid, mark);
            }
            else {
                q = 0;
            }
        }
    }

    void traverseStudent(const vector<int> &first,
                         const vector<int> &last,
                         int sid) {
        traverse(first, sid, 1);
        traverse(last, sid, 1);
        traverse(first, sid, 0);
        traverse(last, sid, 0);
    }
};

int N, M;

void read(vector<int> &s) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        s.push_back(x);
    }
}

int main() {
    scanf("%d%d", &N, &M);
    vector<vector<int>> firstNames(N), lastNames(N);
    vector<vector<int>> names(M);
    for (int i = 0; i < N; i++) {
        read(firstNames[i]);
        read(lastNames[i]);
    }

    AhoCorasick ac;
    for (int i = 0; i < M; i++) {
        read(names[i]);
        ac.add_str(names[i]);
    }

    ac.push_links();
    for (int i = 0; i < N; i++) {
        ac.traverseStudent(firstNames[i], lastNames[i], i);
    }
    
    for (int i = 0; i < M; i++) {
        printf("%d\n", roster[i]);
    }
    for (int i = 0; i < N; i++) {
        printf("%d ", student[i]);
    }
    return 0;
}
