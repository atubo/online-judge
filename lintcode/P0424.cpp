// https://www.lintcode.com/problem/evaluate-reverse-polish-notation/description?_from=ladder&&fromId=23
// 424. Evaluate Reverse Polish Notation

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int evalRPN(vector<string> &tokens) {
        stack<int> st;
        int x, y;
        for (const auto &t: tokens) {
            if (t.length() == 1) {
                switch (t[0]) {
                    case '+':
                        tie(x, y) = pop2(st);
                        st.push(x+y);
                        break;
                    case '-':
                        tie(x, y) = pop2(st);
                        st.push(x-y);
                        break;
                    case '*':
                        tie(x, y) = pop2(st);
                        st.push(x*y);
                        break;
                    case '/':
                        tie(x, y) = pop2(st);
                        st.push(x/y);
                        break;
                    default:
                        st.push(stoi(t));
                        break;
                }
            } else {
                st.push(stoi(t));
            }
        }
        return st.top();
    }

    pair<int, int> pop2(stack<int> &st) {
        int y = st.top();
        st.pop();
        int x = st.top();
        st.pop();
        return make_pair(x, y);
    }
};

int main() {
    Solution solution;
    return 0;
}
