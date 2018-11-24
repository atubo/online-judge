// https://www.luogu.org/problemnew/show/P2741
// [USACO4.4]重叠的图像Frame Up

#include <bits/stdc++.h>
using namespace std;

const int SZ = 26;
int H, W;
int toId[SZ];
char toChar[SZ];
int A[32][32];
int L[SZ], R[SZ], T[SZ], B[SZ];
bool adj[SZ][SZ];
int deg[SZ];
vector<vector<int>> ans;
bool in[SZ];

void dfs(int u, int d, vector<int> &path, int sz) {
    in[u] = true;
    path.push_back(u);
    if (d == 0) {
        ans.push_back(path);
        path.pop_back();
        in[u] = false;
        return;
    }

    for (int v = 0; v < sz; v++) {
        if (adj[u][v]) {
            deg[v]--;
        }
    }

    for (int v = 0; v < sz; v++) {
        if (!in[v] && !deg[v]) {
            dfs(v, d-1, path, sz);
        }
    }

    for (int v = 0; v < sz; v++) {
        if (adj[u][v]) {
            deg[v]++;
        }
    }
    path.pop_back();
    in[u] = false;
}

void processH(int u, int x1, int x2, int y) {
    for (int x = x1; x <= x2; x++) {
        int v = A[y][x];
        if (u != v) {
            if (!adj[v][u]) deg[u]++;
            adj[v][u] = true;
        }
    }
}

void processV(int u, int y1, int y2, int x) {
    for (int y = y1; y <= y2; y++) {
        int v = A[y][x];
        if (u != v) {
            if (!adj[v][u]) deg[u]++;
            adj[v][u] = true;
        }
    }
}

int main() {
    memset(toId, -1, sizeof(toId));
    memset(A, -1, sizeof(A));
    scanf("%d%d", &H, &W);
    int curr = 0;
    char line[32];
    for (int i = 0; i < H; i++) {
        scanf("%s", line);
        for (int j = 0; j < W; j++) {
            char c = line[j];
            if (c == '.') continue;
            if (toId[c-'A'] == -1) {
                toId[c-'A'] = curr;
                toChar[curr] = c;
                curr++;
            }
            A[i][j] = toId[c-'A'];
        }
    }

    for (int i = 0; i < SZ; i++) {
        L[i] = T[i] = INT_MAX;
        R[i] = B[i] = INT_MIN;
    }

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            int x = A[i][j];
            if (x == -1) continue;
            L[x] = min(L[x], j);
            R[x] = max(R[x], j);
            T[x] = min(T[x], i);
            B[x] = max(B[x], i);
        }
    }

    for (int i = 0; i < curr; i++) {
        processH(i, L[i], R[i], T[i]);
        processH(i, L[i], R[i], B[i]);
        processV(i, T[i], B[i], L[i]);
        processV(i, T[i], B[i], R[i]);
    }

    for (int i = 0; i < curr; i++) {
        if (deg[i] == 0) {
            vector<int> path;
            dfs(i, curr-1, path, curr);
        }
    }

    vector<string> ans2;
    for (auto &v: ans) {
        string s(curr, '\0');
        for (int i = curr-1; i >= 0; i--) {
            s[curr-1-i] = toChar[v[i]];
        }
        ans2.push_back(s);
    }

    sort(ans2.begin(), ans2.end());
    for (auto &s: ans2) {
        printf("%s\n", s.c_str());
    }
    return 0;
}
