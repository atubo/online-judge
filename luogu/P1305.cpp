// https://www.luogu.org/problem/show?pid=1305
// 新二叉树
#include <iostream>
#include <map>
#include <utility>
#include <vector>
using namespace std;

map<char, int> mf;
map<int, char> mb;

typedef pair<char, pair<char, char> > Node;
typedef pair<int, int> PII;

void link(char c, int i) {
    mf[c] = i;
    mb[i] = c;
}

void preorder(int u, const vector<PII>& children, string& ans) {
    ans.push_back(mb.at(u));
    int v = children[u].first;
    int w = children[u].second;
    if (v >= 0) preorder(v, children, ans);
    if (w >= 0) preorder(w, children, ans);
}


int main() {
    int N;
    cin >> N;

    link('*', -1);

    vector<Node> nodes;

    char a, b, c;
    int count = 0;
    for (int i = 0; i < N; i++) {
        cin >> a >> b >> c;
        if (mf.count(a) == 0) link(a, count++);
        if (mf.count(b) == 0) link(b, count++);
        if (mf.count(c) == 0) link(c, count++);
        nodes.push_back(make_pair(a, make_pair(b, c)));
    }

    vector<bool> isRoot(count, true);
    vector<PII> children(count);
    for (int i = 0; i < N; i++) {
        int u = mf.at(nodes[i].first);
        int v = mf.at(nodes[i].second.first);
        int w = mf.at(nodes[i].second.second);
        if (v >= 0) isRoot[v] = false;
        if (w >= 0) isRoot[w] = false;
        children[u] = make_pair(v, w);
    }

    string ans;
    for (int i = 0; i < count; i++) {
        if (isRoot[i]) {
            preorder(i, children, ans);
            break;
        }
    }
    cout << ans << endl;

    return 0;
}
