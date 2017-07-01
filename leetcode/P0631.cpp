// https://leetcode.com/problems/design-excel-sum-formula/#/description
// 631. Design Excel Sum Formula

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;

struct Range {
    int r1, c1, r2, c2;
    Range(int r1_, int c1_, int r2_, int c2_):
        r1(r1_), c1(c1_), r2(r2_), c2(c2_) {}
};

class Excel {
public:
    Excel(int H_, char Wc) {
        H = H_;
        W = Wc - 'A' + 1;
        N = H * W;
        cells.resize(N);
        adj.resize(N);
        for (int i = 0; i < N; i++) adj[i].resize(N, 0);
    }

    int idx(int r, char c) {
        return r * W + (c - 'A');
    }

    void propagate(int i, int d) {
        for (int j = 0; j < N; j++) {
            if (adj[i][j] != 0) {
                cells[j] += adj[i][j] * d;
                propagate(j, adj[i][j] * d);
            }
        }
    }

    void set(int r, char c, int v) {
        r--;
        int i = idx(r, c);
        clearIncident(i);
        int d = v - cells[i];
        cells[i] = v;
        propagate(i, d);
    }

    int get(int r, char c) {
        r--;
        return cells[idx(r, c)];
    }

    void clearIncident(int j) {
        for (int i = 0; i < N; i++) adj[i][j] = 0;
    }

    void setIncident(int i, int j, int x) {
        adj[i][j] += x;
    }

    pair<int, int> parseOneEntry(const string& s) {
        assert(s.length() == 2 || s.length() == 3);
        int c = s[0] - 'A';
        int r = stoi(s.substr(1)) - 1;
        return make_pair(r, c);
    }

    Range parseToRange(const string& s) {
        int p = s.find(':');
        int x1, y1, x2, y2;
        if (p == (int)string::npos) {
            tie(x1, y1) = parseOneEntry(s);
            x2 = x1;
            y2 = y1;
        } else {
            tie(x1, y1) = parseOneEntry(s.substr(0, p));
            tie(x2, y2) = parseOneEntry(s.substr(p+1));
        }
        return Range(x1, y1, x2, y2);
    }

    vector<int> markRanges(const vector<Range>& ranges) {
        vector<vector<PII>> ins(H), del(H);
        for (const Range& range: ranges) {
            ins[range.r1].push_back(make_pair(range.c1, range.c2));;
            if (range.r2 < H-1) {
                del[range.r2+1].push_back(make_pair(range.c1, range.c2));
            }
        }

        vector<vector<int>> matrix(H, vector<int>(W, 0));
        for (int r = 0; r < H; r++) {
            for (const auto& pr: ins[r]) {
                for (int c = pr.first; c <= pr.second; c++) {
                    matrix[r][c]++;
                }
            }
            for (const auto& pr: del[r]) {
                for (int c = pr.first; c <= pr.second; c++) {
                    matrix[r][c]--;
                }
            }
            for (int c = 0; c < W; c++) {
                matrix[r][c] += (r == 0 ? 0 : matrix[r-1][c]);
            }
        }

        vector<int> ret(H*W);
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                ret[r*W + c] = matrix[r][c];
            }
        }
        return ret;
    }

    int sum(int r, char c, vector<string> strs) {
        r--;
        int j = idx(r, c);
        int old = cells[j];
        cells[j] = 0;
        clearIncident(j);

        vector<Range> ranges;
        for (const auto& s: strs) {
            ranges.push_back(parseToRange(s));
        }
        vector<int> in = markRanges(ranges);
        for (int i = 0; i < N; i++) {
            setIncident(i, j, in[i]);
        }

        for (int i = 0; i < N; i++) {
            cells[j] += adj[i][j] * cells[i];
        }
        propagate(j, cells[j] - old);

        return cells[j];
    }

private:
    int H, W, N;
    vector<int> cells;
    vector<vector<int>> adj;
};

int main() {
    Excel e(5, 'E');
    e.set(1, 'A', 5);
    e.set(1, 'B', 3);
    e.set(1, 'C', 2);
    cout << e.sum(1, 'C', {"A1", "A1:B1"}) << endl;
    cout << e.get(1, 'C') << endl;
    e.set(1, 'B', 5);
    cout << e.get(1, 'C') << endl;
    cout << e.sum(1, 'B', {"A1:A5"}) << endl;
    e.set(5, 'A', 10);
    cout << e.get(1, 'B') << endl;
    cout << e.get(1, 'C') << endl;
    cout << e.sum(3, 'C', {"A1:C1", "A1:A5"}) << endl;
    e.set(3, 'A', 3);
    cout << e.get(1, 'B') << endl;
    cout << e.get(1, 'C') << endl;
    cout << e.get(3, 'C') << endl;
    cout << e.get(5, 'A') << endl;
    return 0;
}
