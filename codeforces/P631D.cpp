// http://codeforces.com/problemset/problem/631/D

#include <bits/stdc++.h>

using namespace std;

class Solution {
    using PII = pair<int64_t, int>;
private:
    vector<int> f;
    vector<PII> T;
    vector<PII> S;
    vector<PII> PAT;
    PII head, tail;
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

        head = *S.begin();
        tail = *S.rbegin();
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
        assert(S.size() > 2);
        PAT.resize(S.size()-2);
        copy_n(S.begin() + 1, PAT.size(), PAT.begin());
        f.resize(PAT.size());
        int t = 0;
        f[0] = 0;

        // prefix function
        for (int s = 1; s < (int)PAT.size(); s++) {
            while (t > 0 && PAT[s] != PAT[t]) {
                t = f[t-1];
            }
            if (PAT[s] == PAT[t]) {
                t++;
            }
            f[s] = t;
        }
    }

    bool contains(const PII& p, const PII& q) {
        return p.second == q.second &&
               p.first >= q.first;
    }

    void solve() {
        if (S.size() == 1) {
            solve1();
        } else if (S.size() == 2) {
            solve2();
        } else {
            solve3();
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
        int ret = 0;
        for (int i = 0; i < (int)T.size()-1; i++) {
            if (contains(T[i], head) && contains(T[i+1], tail)) ret++;
        }
        cout << ret << endl;
    }


    void solve3() {
        buildKMP();

        int s = 0;
        int ret = 0;
        for (int i = 0; i < (int)T.size(); i++) {
            while (s > 0 && T[i] != PAT[s]) {
                s = f[s-1];
            }
            if (T[i] == PAT[s]) s++;
            if (s == (int)PAT.size()) {
                if (checkBoundary(i)) ret++;
                s = f[s-1];
            }
        }
        cout << ret << endl;
    }

    bool checkBoundary(int p) {
        int i = p - PAT.size();
        int j = p + 1;
        if (i < 0 || !contains(T[i], head)) return false;
        if (j >= (int)T.size() || !contains(T[j], tail)) return false;
        return true;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
