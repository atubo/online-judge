// http://codeforces.com/problemset/problem/253/D
#include <bits/stdc++.h>

using namespace std;

void printVector(const vector<pair<int, int>>& A) {
    for (const auto& pr: A) {
        printf("(%d %d) ", pr.first, pr.second);
    }
    cout << endl;
}

void printMatrix(const vector<vector<int>>& m) {
    for (const auto& v: m) {
        for (int x: v) {
            cout << x << " ";
        }
        cout << endl;
    }
}

class Solution {
    using Matrix = vector<vector<int>>;
    using PII = pair<int, int>;
private:
    int N, M, K;
    Matrix mat;
public:
    Solution() {
        ifstream in("input.txt");
        in >> N >> M >> K;
        mat.resize(N);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                char c;
                in >> c;
                mat[i].push_back(c-'a');
            }
        }
    }

    void solve() {
        int64_t ret = 0;
        Matrix aOccu = buildOccu();
        for (int i = 0; i < N-1; i++) {
            for (int j = i+1; j < N; j++) {
                ret += count(i, j, aOccu);
            }
        }
        ofstream out("output.txt");
        out << ret << endl;
    }

    Matrix buildOccu() const {
        Matrix ret(N, vector<int>(M));
        ret[0][0] = (mat[0][0] == 0);
        for (int i = 1; i < M; i++) {
            ret[0][i] = ret[0][i-1] + (mat[0][i] == 0);
        }
        
        for (int i = 1; i < N; i++) {
            int ps = 0;
            for (int j = 0; j < M; j++) {
                ps += (mat[i][j] == 0);
                ret[i][j] = ps + ret[i-1][j];
            }
        }
        return ret;
    }

    vector<PII> buildReprVec(int row1, int row2, const Matrix& occu) {
        vector<PII> ret;
        for (int i = 0; i < M; i++) {
            if (mat[row1][i] == mat[row2][i]) {
                ret.push_back(make_pair(mat[row1][i], i));
            }
        }
        return ret;
    }

    int countA(int row1, int row2, int col, const Matrix& occu) {
        return (row1 == 0 ?
                occu[row2][col] : occu[row2][col] - occu[row1-1][col]);
    }

    int countRange(const Matrix& occu, int r1, int r2, int c1, int c2) {
        int ret = occu[r2][c2] - (r1 == 0 ? 0 : occu[r1-1][c2]);
        if (c1 > 0) {
            ret -= occu[r2][c1-1] - (r1 == 0 ? 0 : occu[r1-1][c1-1]);
        }
        return ret;
    }

    int64_t count(int row1, int row2, const Matrix& occu) {
        //printf("row1=%d row2=%d\n", row1, row2);
        int64_t ret = 0;
        vector<PII> repr = buildReprVec(row1, row2, occu);
        const int sz = repr.size();
        if (sz == 0) return 0;
        int p = 0;
        int q = p + 1;
        vector<int> freq(26, 0);
        freq[repr[0].first] = 1;
        while (p < sz) {
            while (q < sz) {
                freq[repr[q].first]++;
                if (countRange(occu, row1, row2,
                               repr[p].second, repr[q].second) > K) break;
                q++;
            }

            if (q == sz) {
                for (int i = p; i < sz; i++) {
                    ret += calc(freq, repr[i].first, -1);
                    freq[repr[i].first]--;
                }
                break;
            }
            while (p < sz &&
                   countRange(occu, row1, row2,
                              repr[p].second, repr[q].second) > K) {
                ret += calc(freq, repr[p].first, repr[q].first);
                freq[repr[p].first]--;
                p++;
            }
            q++;
        }
        //cout << ret << endl;
        return ret;
    }

    int calc(const vector<int>& freq, int x, int y) {
        int f = freq.at(x) - (x == y);
        return max(0, f - 1);
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
