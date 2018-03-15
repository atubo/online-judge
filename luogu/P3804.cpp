// https://www.luogu.org/problemnew/show/P3804
// 【模板】后缀自动机

#include <bits/stdc++.h>
using namespace std;

/* 
 * SuffixNode Declaration
 */
class SuffixNode 
{
public:
    static constexpr const char* ALPHABET = "abcdefghijklmnopqrstuvwxyz$";
    const static int ALPHASIZE = strlen(ALPHABET);

    int depth, begin, end;
    SuffixNode **children;
    SuffixNode *parent, *suffixLink;
    /*
     * Constructor
     */
    SuffixNode(int begin_, int end_, int depth_, SuffixNode *parent_):
        depth(depth_), begin(begin_), end(end_), parent(parent_),
        suffixLink(NULL) {
        children = new SuffixNode* [ALPHASIZE]{};
        //for (int i = 0; i < ALPHASIZE; i++) children[i] = NULL;
        //this->begin = begin_;
        //this->end = end_;
        //this->parent = parent_;
        //this->depth = depth_;
        //this->suffixLink = NULL;
    }

    ~SuffixNode() {
        for (int i = 0; i < ALPHASIZE; i++) {
            delete children[i];
        }
        delete[] children;
    }

    inline bool contains(int d) const {
        return depth <= d && d < depth + (end - begin);
    }
};
 
/* 
 * Class SuffixTree Declaration
 */
class SuffixTree 
{
public:
    SuffixTree() {
        root = NULL;
    }

    ~SuffixTree() {
        //delete root;
    }
    /*
     * Funtion to build suffix tree for given text
     */
    void build(string s) {
        int n = s.length();
        int *a = new int[n]{};
        for (int i = 0; i < n; i++) 
        {
            bool found = false;
            for (int j = 0; j < SuffixNode::ALPHASIZE; j++) {
                if (SuffixNode::ALPHABET[j] == s.at(i)) {
                    a[i] = j;
                    found = true;
                    break;
                }
            }
            assert(found);
        }
        root = new SuffixNode(0, 0, 0, NULL);
        SuffixNode *cn = root;
        root->suffixLink = root;
        SuffixNode *needsSuffixLink = NULL;
        int lastRule = 0;
        int j = 0;
        for (int i = -1; i < n - 1; i++) 
        {
            int cur = a[i + 1]; 
            for (; j <= i + 1; j++) 
            {
                int curDepth = i + 1 - j;
                if (lastRule != 3) 
                {
                    if (cn->suffixLink != NULL) 
                        cn = cn->suffixLink;
                    else
                        cn = cn->parent->suffixLink;
                    int k = j + cn->depth;
                    while (curDepth > 0 && !cn->contains(curDepth - 1)) 
                    {
                        k += cn->end - cn->begin;
                        cn = cn->children[a[k]];
                    }
                }
                if (!cn->contains(curDepth)) 
                { 
                    if (needsSuffixLink != NULL) 
                    {
                        needsSuffixLink->suffixLink = cn;
                        needsSuffixLink = NULL;
                    }
                    if (cn->children[cur] == NULL) 
                    {
                        cn->children[cur] = new SuffixNode(i + 1, n, curDepth, cn);
                        lastRule = 2;
                    }
                    else 
                    {    
                        cn = cn->children[cur];
                        lastRule = 3;
                        break;
                    }
                }
                else 
                { 
                    int end = cn->begin + curDepth - cn->depth;
                    if (a[end] != cur) 
                    { 
                        SuffixNode *newn = new SuffixNode(cn->begin, end, cn->depth, cn->parent);
                        newn->children[cur] = new SuffixNode(i + 1, n, curDepth, newn);
                        newn->children[a[end]] = cn;
                        cn->parent->children[a[cn->begin]] = newn;
                        if (needsSuffixLink != NULL) 
                            needsSuffixLink->suffixLink = newn;
                        cn->begin = end;
                        cn->depth = curDepth;
                        cn->parent = newn;
                        cn = needsSuffixLink = newn;
                        lastRule = 2;
                    } 
                    else if (cn->end != n || (cn->begin - cn->depth) < j) 
                    {
                        lastRule = 3;
                        break;
                    }
                    else
                        lastRule = 1;                      
                }
            }
        }
        root->suffixLink = NULL;
    }

public:
    SuffixNode *root;
};

int dfs(SuffixNode* node, int64_t &ans) {
    int nc = 0;
    for (int i = 0; i < SuffixNode::ALPHASIZE; i++) {
        if (node->children[i]) {
            nc += dfs(node->children[i], ans);
        }
    }

    int length = node->end - node->begin;
    if (nc == 0) return 1;
    ans = max(ans, ((int64_t)node->depth + length) * nc);
    return nc;
}


int main() {
    string s;
    cin >> s;
    s.push_back('$');
    SuffixTree st;
    st.build(s);

    int64_t ans = 0;
    dfs(st.root, ans);
    cout << ans << endl;
    return 0;
}
