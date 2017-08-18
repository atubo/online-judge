// https://www.luogu.org/problem/show?pid=1032
// 字串变换

#include <bits/stdc++.h>
using namespace std;

using Rule = pair<string, string>;
string A, B;
vector<Rule> rules;

int bfs() {
    using Node = pair<string, int>;
    queue<Node> q;
    set<string> visited;
    q.push(make_pair(A, 0));
    visited.insert(A);
    while (!q.empty()) {
        string u = q.front().first;
        int d = q.front().second;
        q.pop();
        if (u == B) return d;
        if (d == 10) continue;
        for (const auto& rule: rules) {
            size_t pos = 0;
            const string& from = rule.first;
            const string& to   = rule.second;
            while ((pos = u.find(from, pos)) != string::npos) {
                string v = u.substr(0, pos) + to + u.substr(pos + from.length());
                if (visited.count(v) == 0) {
                    q.push(make_pair(v, d+1));
                    visited.insert(v);
                }
                pos++;
            }
        }
    }
    return -1;
}


int main() {
    cin >> A >> B;
    char from[22], to[22];
    while (scanf("%s%s", from, to) == 2) {
        rules.push_back(make_pair(string(from), string(to)));
    }
    int ans = bfs();
    if (ans == -1) cout << "NO ANSWER!" << endl;
    else cout << ans << endl;
    return 0;
}
