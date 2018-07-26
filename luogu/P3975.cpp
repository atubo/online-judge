// https://www.luogu.org/problemnew/show/P3975
// [TJOI2015]弦论

#include <bits/stdc++.h>
using namespace std;

// Suffix array using radix sort
// which means the alphabet of the input string should be small
// END character must be the smallest
// See: 罗穗骞 后缀数组 - 处理字符串的有力工具
class SuffixArrayRadix {
public:
    SuffixArrayRadix(const string &s_):s(s_), N(s.length()) {
        char cmin = 0x7F, cmax = 0;
        for (char c: s) {
            cmin = min(cmin, c);
            cmax = max(cmax, c);
        }
        M = cmax - cmin + 1;
        MAXN = max(M, N);

        wa = new int[MAXN]{};
        wb = new int[MAXN]{};
        wv = new int[MAXN]{};
        ws = new int[MAXN]{};
        sa = new int[MAXN]{};
        r  = new int[MAXN]{};
        lcp = new int[MAXN]{};

        for (int i = 0; i < N; i++) {
            r[i] = s[i] - cmin;
        }
    }

    ~SuffixArrayRadix() {
        delete[] wa;
        delete[] wb;
        delete[] wv;
        delete[] ws;
        delete[] sa;
        delete[] r;
        delete[] lcp;
    }
    int *wa, *wb, *wv, *ws;
    int *sa, *r, *rank;
    int *lcp;

    void buildSA() {
        buildSA(N, M);
    }

    void buildLCP() {
        for (int i = 0, k = 0; i < N; ++i) if (rank[i] != N - 1)
        {
            for (int j = sa[rank[i] + 1]; s[i + k] == s[j + k];)
                ++k;
            lcp[rank[i]] = k;
            if (k)--k;
        }
    }

private:
    int cmp(int *arr, int a, int b, int l) {
        return arr[a] == arr[b] && arr[a+l] == arr[b+l];
    }

    void buildSA(int n, int m) {
        int i, j, p, *x = wa, *y = wb, *t;
        // first round of radix sort
        for (i = 0; i < m; i++) ws[i] = 0;
        for (i = 0; i < n; i++) ws[x[i]=r[i]]++;
        for (i = 1; i < m; i++) ws[i] += ws[i-1];
        for (i = n-1; i >= 0; i--) sa[--ws[x[i]]] = i;
        for (j=1, p=1; p < n; j*=2,m=p) {
            // sort by the second key
            for (p=0, i=n-j; i<n; i++) y[p++] = i;
            for (i=0; i<n; i++) if (sa[i]>=j) y[p++] = sa[i]-j;
            // sort by the first key
            for (i=0; i<n; i++) wv[i] = x[y[i]];
            for (i=0; i<m; i++) ws[i] = 0;
            for (i=0; i<n; i++) ws[wv[i]]++;
            for (i=1; i<m; i++) ws[i] += ws[i-1];
            for (i=n-1; i>=0; i--) sa[--ws[wv[i]]] = y[i];
            for (t=x, x=y, y=t, p=1, x[sa[0]]=0, i=1; i<n; i++) {
                x[sa[i]]=cmp(y, sa[i-1], sa[i], j)?p-1:p++;
            }
        }
        rank = x;
    }

public:
    const string &s;
    const int N;
private:
    int M;
    int MAXN;
};

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
    int64_t cnt;
    /*
     * Constructor
     */
    SuffixNode(int begin_, int end_, int depth_, SuffixNode *parent_) {
        children = new SuffixNode* [ALPHASIZE];
        for (int i = 0; i < ALPHASIZE; i++) children[i] = NULL;
        this->begin = begin_;
        this->end = end_;
        this->parent = parent_;
        this->depth = depth_;
        this->suffixLink = NULL;
        this->cnt = 0;
    }

    ~SuffixNode() {
        for (int i = 0; i < ALPHASIZE; i++) {
            delete children[i];
        }
        delete[] children;
    }

    bool contains(int d) {
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
        delete root;
    }
    /*
     * Funtion to build suffix tree for given text
     */
    void build(string s) {
        int n = s.length();
        vector<int> a(n);
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

const int MAXN = 500010;
int64_t ps[MAXN];

void dfs1(SuffixNode *node, int n) {
    node->cnt = node->end - node->begin;
    if (node->end == n) node->cnt--;
    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            dfs1(node->children[i], n);
            node->cnt += node->children[i]->cnt;
        }
    }
}

void dfs2(const SuffixNode *node, int k, const string &s, string &res) {
    if (node->end - node->begin >= k) {
        res += s.substr(node->begin, k);
        return;
    }
    k -= node->end - node->begin;
    res += s.substr(node->begin, node->end-node->begin);
    for (int i = 0; i < 26; i++) {
        SuffixNode *ch = node->children[i];
        if (!ch) continue;
        if (ch->cnt >= k) {
            dfs2(ch, k, s, res);
            return;
        }
        else k -= ch->cnt;
    }
}

void solve0(string &s, int k) {
    s.push_back('$');
    SuffixTree st;
    st.build(s);
    const int n = s.length();
    dfs1(st.root, n);
    if (k > st.root->cnt) {
        printf("-1\n");
        return;
    }
    string res;
    dfs2(st.root, k, s, res);
    cout << res << endl;
}


int lowerbound(const SuffixArrayRadix &sa, int top, int bot, int pos, char c) {
    int lo = top, hi = bot;
    if (sa.N - sa.sa[lo] > pos && sa.s[sa.sa[lo]+pos] >= c) return lo;
    while (lo < hi-1) {
        int mid = (lo + hi) / 2;
        if (sa.N - sa.sa[mid] <= pos || sa.s[sa.sa[mid]+pos] < c) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    return hi;
}

int upperbound(const SuffixArrayRadix &sa, int top, int bot, int pos, char c) {
    int lo = top, hi = bot;
    if (sa.N - sa.sa[lo] > pos && sa.s[sa.sa[lo]+pos] > c) return lo;
    while (lo < hi-1) {
        int mid = (lo + hi) / 2;
        if (sa.N - sa.sa[mid] <= pos || sa.s[sa.sa[mid]+pos] <= c) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    return hi;
}

void solve1(string &s, int k) {
    const int N = s.length();
    s.push_back('`');
    SuffixArrayRadix sa(s);
    sa.buildSA();
    s.pop_back();
    for (int i = 0; i < N; i++) {
        sa.sa[i] = sa.sa[i+1];
    }

    for (int i = 0; i < N; i++) {
        ps[i+1] = ps[i] + (N - sa.sa[i]);
    }
    if (k > ps[N]) {
        printf("-1\n");
        return;
    }
    string res;
    int top = 0, bot = N;
    bool found = false;
    for (int pos = 0; pos < N; pos++) {
        for (char c = 'a'; c <= 'z'; c++) {
            int p = lowerbound(sa, top, bot, pos, c);
            int q = upperbound(sa, top, bot, pos, c);
            int tot = ps[q] - ps[p] - (q - p) * pos;
            if (tot < k) {
                k -= tot;
                top = q;
                continue;
            }
            res.push_back(c);
            top = p;
            bot = q;
            if (k <= bot - top) found = true;
            k -= (bot - top);
            break;
        }
        if (found) break;
    }
    cout << res << endl;
}

int main() {
    string s;
    cin >> s;
    int t, k;
    scanf("%d%d", &t, &k);
    if (t == 0) {
        solve0(s, k);
    } else {
        solve1(s, k);
    }
    return 0;
}
