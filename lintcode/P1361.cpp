// https://www.lintcode.com/problem/text-justification/description
// 1361. Text Justification

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string> &words, int maxWidth) {
        const int n = words.size();
        vector<string> lines;
        int p = 0;
        while (true) {
            int q = p;
            int len = 0;
            while (q < n && (len + int(words[q].length()) + (q!=p)) <= maxWidth) {
                len += words[q].length() + (q!=p);
                q++;
            }
            if (q == n) {
                lines.push_back(leftJustify(words, p, q, maxWidth));
                break;
            }
            lines.push_back(fullJustify(words, p, q, maxWidth));
            p = q;
        }
        return lines;
    }

    string leftJustify(const vector<string> &words, int p, int q,
                       int maxWidth) {
        string ret = words[p];
        int tot = words[p].length();
        for (int i = p+1; i < q; i++) {
            ret += ' ';
            ret += words[i];
            tot += words[i].length() + 1;
        }
        ret.append(maxWidth - tot, ' ');
        return ret;
    }

    string fullJustify(const vector<string> &words, int p, int q,
                       int maxWidth) {
        int ns = q - p - 1;
        string ret;
        if (ns == 0) {
            ret = words[p];
            ret.append(maxWidth - words[p].length(), ' ');
            return ret;
        }

        int tot = 0;
        for (int i = p; i < q; i++) {
            tot += words[i].length();
        }

        tot = maxWidth - tot;
        ret += words[p];
        for (int i = p+1; i < q; i++) {
            int sp = (tot + ns - 1) / ns;
            ret.append(sp, ' ');
            ret += words[i];
            tot -= sp;
            ns--;
        }
        return ret;
    }
};

int main() {
    int n;
    cin >> n;
    vector<string> words(n);
    for (int i = 0; i < n; i++) cin >> words[i];
    int maxWidth;
    cin >> maxWidth;
    Solution solution;
    auto ret = solution.fullJustify(words, maxWidth);
    for (auto s: ret) {
        cout << s << endl;
    }
    return 0;
}


