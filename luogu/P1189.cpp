// https://www.luogu.org/problem/show?pid=1189
// SEARCH

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;

int R, C;
int N;
bool town[50][50];
bool pre[50][50], curr[50][50];

const int DX[4] = {0, -1, 0, 1};
const int DY[4] = {1, 0, -1, 0};

bool inRange(int r, int c) {
    return 0 <= r && r < R && 0 <= c && c < C;
}

void bfs(int d) {
    memset(curr, 0, sizeof(curr));
    queue<PII> q;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (pre[i][j]) q.push(make_pair(i, j));
        }
    }

    while (!q.empty()) {
        int u = q.front().first;
        int v = q.front().second;
        q.pop();
        int s = u + DX[d];
        int t = v + DY[d];
        if (inRange(s, t) && !curr[s][t] && town[s][t]) {
            q.push(make_pair(s, t));
            curr[s][t] = true;
        }
    }

    memcpy(pre, curr, sizeof(curr));
}

int main() {
    cin >> R >> C;
    for (int i = 0; i < R; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < C; j++) {
            switch (s[j]) {
                case '.':
                    town[i][j] = true;
                    break;
                case 'X':
                    town[i][j] = false;
                    break;
                case '*':
                    town[i][j] = true;
                    pre[i][j] = true;
                    break;
                default:
                    assert(0);
                    break;
            }
        }
    }

    cin >> N;
    while (N--) {
        string s;
        cin >> s;
        int d = 0;
        if (s[0] == 'N') d = 1;
        else if (s[0] == 'W') d = 2;
        else if (s[0] == 'S') d = 3;

        bfs(d);
    }

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (!town[i][j]) cout << 'X';
            else if (!pre[i][j]) cout << '.';
            else cout << '*';
        }
        cout << endl;
    }
    return 0;
}
