// https://www.lintcode.com/problem/remove-comments/description
// 1069. Remove Comments

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
    bool blockStarts(const string &whole, int pos) {
        const int n = whole.length();
        return pos < n-1 && whole[pos] == '/' && whole[pos+1] == '*';
    }

    bool blockEnds(const string &whole, int pos) {
        const int n = whole.length();
        return pos < n-1 && whole[pos] == '*' && whole[pos+1] == '/';
    }

    bool lineStarts(const string &whole, int pos) {
        const int n = whole.length();
        return pos < n-1 && whole[pos] == '/' && whole[pos+1] == '/';
    }


public:
    vector<string> removeComments(vector<string> &source) {
        string whole;
        for (const auto &line: source) {
            whole += line + '\n';
        }
        whole.pop_back();
        int pos = 0, state = 0;
        const int n = whole.length();
        string out;
        while (pos < n) {
            switch (state) {
                case 0:
                    if (blockStarts(whole, pos)) {
                        state = 1;
                        pos += 2;
                    } else if (lineStarts(whole, pos)) {
                        state = 2;
                        pos += 2;
                    } else {
                        out.push_back(whole[pos++]);
                    }
                    break;
                case 1:
                    if (blockEnds(whole, pos)) {
                        state = 0;
                        pos += 2;
                    } else pos++;
                    break;
                case 2:
                    if (whole[pos] == '\n') {
                        state = 0;
                        out.push_back('\n');
                    }
                    pos++;
                    break;
                default:
                    break;
            }
        }
        cout << out << endl;
        vector<string> ret;
        int curr = 0;
        while (curr < n && out[curr] == '\n') curr++;
        while (curr < n) {
            auto p = out.find('\n', curr);
            if (p == string::npos) {
                ret.push_back(out.substr(curr));
                break;
            }
            ret.push_back(out.substr(curr, p-curr));
            while ((int)p < n && out[p] == '\n') p++;
            curr = p;
        }
        return ret;
    }
};

int main() {
    Solution solution;
    int n;
    cin >> n;
    string tmp;
    getline(cin, tmp);
    vector<string> lines(n);
    for (int i = 0; i < n; i++) {
        getline(cin, lines[i]);
    }
    auto ret = solution.removeComments(lines);
    for (auto l: ret) {
        cout << l << endl;
    }

    return 0;
}
