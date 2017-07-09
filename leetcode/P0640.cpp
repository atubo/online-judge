// https://leetcode.com/problems/solve-the-equation/#/description
// 640. Solve the Equation

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    struct CanonForm {
        CanonForm(): coeff(0), con(0) {}
        int coeff;
        int con;
    };
public:
    string solveEquation(string equation) {
        int pos = equation.find('=');
        string left = equation.substr(0, pos);
        string right = equation.substr(pos+1);
        CanonForm lhs = parse(left);
        CanonForm rhs = parse(right);
        if (lhs.coeff == rhs.coeff) {
            return lhs.con == rhs.con ? "Infinite solutions" : "No solution";
        } else {
            int x = (rhs.con - lhs.con) / (lhs.coeff - rhs.coeff);
            return "x=" + to_string(x);
        }
    }

    void parseTerm(const string& term, CanonForm& cf) {
        if (term.back() == 'x') {
            string co = term.substr(0, term.length()-1);
            if (co.empty() || co == "+") {
                cf.coeff++;
            } else if (co == "-") {
                cf.coeff--;
            } else {
                cf.coeff += stoi(co);
            }
        } else {
            cf.con += stoi(term);
        }
    }

    CanonForm parse(const string& s) {
        CanonForm ret;
        int p = 0, q = s.find_first_of("+-", 1);
        while (q != (int)string::npos) {
            string term = s.substr(p, q-p);
            parseTerm(term, ret);
            p = q;
            q = s.find_first_of("+-", p+1);
        }
        parseTerm(s.substr(p), ret);
        return ret;
    }
};

int main() {
    string s;
    cin >> s;
    Solution solution;
    cout << solution.solveEquation(s) << endl;
    return 0;
}
