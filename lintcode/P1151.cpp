// https://www.lintcode.com/problem/tag-validator/description
// 1151. Tag Validator

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
    const static char LB = '<';
    const static char RB = '>';
    const static char SL = '/';
    const static char EC = '!';

    class ParseError:public exception {};

    void error() {
        throw ParseError();
    }

    stack<string> tagname;
public:
    bool isValid(string &code) {
        while (!tagname.empty()) tagname.pop();

        int pos;
        try {
            parseCode(code, pos);
        } catch (const ParseError &e) {
            return false;
        }
        return pos == (int)code.length();
    }

    void parseCode(const string &code, int &pos) {
        parseOpenTag(code, pos);
        parseTagContent(code, pos);
        parseCloseTag(code, pos);
    }

    void parseOpenTag(const string &code, int &pos) {
        accept(code, pos, LB);
        parseTagName(code, pos, true);
        accept(code, pos, RB);
    }

    void parseCloseTag(const string &code, int &pos) {
        accept(code, pos, LB);
        accept(code, pos, SL);
        parseTagName(code, pos, false);
        accept(code, pos, RB);
    }

    void accept(const string &code, int &pos, char c) {
        if (pos >= (int)code.length() || code[pos++] != c) {
            error();
        }
    }

    void parseTagName(const string &code, int &pos, bool push) {
        int p = pos;
        while(p < (int)code.length() &&
              'A' <= code[p] && code[p] <= 'Z') p++;
        if (p - pos == 0 || p - pos > 9) error();
        if (push) {
            tagname.push(code.substr(pos, p-pos));
        } else {
            string top = tagname.top();
            if (top != code.substr(pos, p-pos)) error();
            tagname.pop();
        }

        pos = p;
    }

    char peek(const string &code, int pos) {
        return (pos < (int)code.length() ? code[pos] : '\0');
    }

    void parseTagContent(const string &code, int &pos) {
        while (pos < (int)code.length()) {
            if (peek(code, pos) == LB && peek(code, pos+1) == SL) {
                return;
            }
            if (peek(code, pos) == LB && peek(code, pos+1) == EC) {
                parseCdata(code, pos);
            } else if (peek(code, pos) == LB) parseCode(code, pos);
            else pos++;
        }
        error();
    }

    void parseCdata(const string &code, int &pos) {
        const int n = code.length();
        if (n < pos + 9 || code.substr(pos, 9) != "<![CDATA[") {
            error();
        }
        pos += 9;
        while (pos <= n-3 &&
               !(peek(code, pos) == ']' && peek(code, pos+1) == ']' &&
                 peek(code, pos+2) == RB)) {
            pos++;
        }
        if (pos > n-3) error();
        pos += 3;
    }
};

int main() {
    Solution solution;
    string s;
    while (true) {
        getline(cin, s);
        if (s.empty()) break;
        cout << solution.isValid(s) << endl;
    }
    return 0;
}
