// https://www.luogu.org/problemnew/show/P2749
// [USACO5.1]夜空繁星Starry Night

#include <bits/stdc++.h>
using namespace std;

using PII = pair<int, int>;

int W, H;
int sky[110][110];
char mark[110][110];
bool visited[110][110];
const int DX[8] = {0, -1, -1, -1, 0, 1, 1, 1};
const int DY[8] = {1, 1, 0, -1, -1, -1, 0, 1};

bool inRange(int r, int c) {
    return 0 <= r && r < H && 0 <= c && c < W;
}

vector<PII> bfs(int r, int c) {
    vector<PII> ret;
    queue<PII> q;
    q.push(make_pair(r, c));
    visited[r][c] = true;
    while (!q.empty()) {
        tie(r, c) = q.front();
        ret.push_back(q.front());
        q.pop();
        for (int d = 0; d < 8; d++) {
            int r2 = r + DX[d];
            int c2 = c + DY[d];
            if (inRange(r2, c2) && !visited[r2][c2] && sky[r2][c2]) {
                q.push(make_pair(r2, c2));
                visited[r2][c2] = true;
            }
        }
    }
    return ret;
}

double dist(const PII &p, const PII &q) {
    double sq = (p.first - q.first) * (p.first - q.first) +
        (p.second - q.second) * (p.second - q.second);
    return sqrt(sq);
}

int64_t discretize(double x) {
    return int64_t(x * 100000 + 0.5);
}

int64_t calcSignature(const vector<PII>& constellation) {
    double tot = 0.0;
    int n = constellation.size();
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            tot += dist(constellation[i], constellation[j]);
        }
    }
    return discretize(tot);
}

void markMap(const vector<PII> &constellation, char c) {
    for (auto p: constellation) {
        mark[p.first][p.second] = c;
    }
}

int main() {
    cin >> W >> H;
    for (int i = 0; i < H; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < W; j++) {
            sky[i][j] = s[j] - '0';
            mark[i][j] = '0';
        }
    }

    int cnt = 0;
    map<int64_t, char> codes;

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (!visited[i][j] && sky[i][j]) {
                vector<PII> constellation = bfs(i, j);
                int64_t signature = calcSignature(constellation);
                if (codes.find(signature) == codes.end()) {
                    codes[signature] = 'a' + cnt;
                    cnt++;
                }
                char c = codes[signature];
                markMap(constellation, c);
            }
        }
    }

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cout << mark[i][j];
        }
        cout << endl;
    }
    return 0;
}
