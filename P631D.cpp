// http://codeforces.com/problemset/problem/631/D

#include <bits/stdc++.h>

using namespace std;

class Solution {
    using PII = pair<int64_t, int>;
private:
    vector<int> f;
    vector<PII> T;
    vector<PII> S;
public:
    Solution() {
        int n, m;
        cin >> n >> m;
        T.resize(n);
        S.resize(m);
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            T[i] = buildPair(s);
        }

        for (int i = 0; i < m; i++) {
            string s;
            cin >> s;
            S[i] = buildPair(s);
        }

        normalize(T);
        normalize(S);
    }

    void normalize(vector<PII>& v) {
        vector<PII> ret;
        for (const PII& p: v) {
            if (ret.empty() || ret.back().second != p.second) {
                ret.push_back(p);
            } else {
                ret.back().first += p.first;
            }
        }
        swap(v, ret);
    }

    PII buildPair(const string& s) {
        int sz = s.length();
        int x = stoi(s.substr(0, sz - 2));
        int y = s.back() - 'a';
        return make_pair(x, y);
    }

    void buildKMP() {
        f.resize(S.size());
        int t = 0;
        f[0] = 0;

        // prefix function
        for (int s = 1; s < (int)S.size(); s++) {
            while (t > 0 && S[s] != S[t]) {
                t = f[t-1];
            }
            if (match1(s, t)) {
                t++;
            }
            f[s] = t;
        }
    }

    bool match1(int s, int t) {
        assert(s > 0);
        if (t > 0) return S[s] == S[t];
        else return contains(S[s], S[t]);
    }

    bool match2(int s, int t) {
        const int M = S.size();
        if (s == 0 || s == M -1) {
            return contains(T[t], S[s]);
        } else {
            return T[t] == S[s];
        }
    }

    bool contains(const PII& p, const PII& q) {
        return p.second == q.second &&
               p.first >= q.first;
    }

    void solve() {
        if (S.size() == 1) {
            solve1();
        } else {
            solve2();
        }
    }

    void solve1() {
        int64_t ret = 0;
        for (const auto& p: T) {
            if (contains(p, S[0])) {
                ret += p.first - S[0].first + 1;
            }
        }
        cout << ret << endl;
    }

    void solve2() {
        buildKMP();
#if 1
        for (int x: f) {
            cout << x << " ";
        }
        cout << endl;
#endif

        int s = 0;
        int ret = 0;
        for (int i = 0; i < (int)T.size(); i++) {
            while (s > 0 && !match2(s, i)) {
                s = f[s-1];
            }
            if (match2(s, i)) s++;
            if (s == (int)S.size()) {
                ret++;
                s = f[s-1];
            }
        }
        cout << ret << endl;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
