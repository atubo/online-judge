// https://www.luogu.org/problemnew/show/P2264
// 情书

#include <bits/stdc++.h>
using namespace std;

int N;

int solve(const string &s, const set<string> &dict) {
    //cout << s << endl;
    int ans = 0;
    size_t p = 0;
    set<string> seen;
    while (p < s.length()) {
        size_t q = p;
        p = s.find_first_of("., ", q);
        if (p == string::npos) break;
        auto w = s.substr(q, p-q);
        if (seen.find(w) == seen.end() && dict.find(w) != dict.end()) {
            ans++;
            seen.insert(w);
        }
        //printf("w=%s ans=%d\n", w.c_str(), ans);
        p++;
    }
    return ans;
}

int main() {
    scanf("%d", &N);
    set<string> dict;
    for (int i = 0; i < N; i++) {
        string w;
        cin >> w;
        transform(w.begin(), w.end(), w.begin(), ::tolower);
        dict.insert(w);
    }
    string s;
    getline(cin, s);
    getline(cin, s);
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    size_t p = 0;
    int ans = 0;
    while (p < s.length()) {
        size_t q = p;
        p = s.find_first_of('.', q);
        if (p == string::npos) {
            ans += solve(s.substr(q), dict);
            break;
        } else {
            ans += solve(s.substr(q, p-q+1), dict);
            p++;
        }
    }
    printf("%d", ans);
    return 0;
}
