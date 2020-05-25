// https://www.luogu.com.cn/problem/P3521
// [POI2011]ROT-Tree Rotations

#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag,
        tree_order_statistics_node_update> ordered_set;

struct Node {
  int val = 0, sz = 0;
  Node* left = nullptr;
  Node* right = nullptr;
  ordered_set* s;
  Node() {
    int x;
    scanf("%d", &x);
    if (x == 0) {
      left = new Node();
      right = new Node();
      sz = left->sz + right->sz;
    } else {
      val = x;
      sz = 1;
    }
  }
};

void dfs(Node* root, int d) {
  for (int i = 0; i < d; i++) {
    printf(" ");
  }
  printf("val=%d sz=%d\n", root->val, root->sz);
  if (root->left) {
    dfs(root->left, d+2);
  }
  if (root->right) {
    dfs(root->right, d+2);
  }
}

int64_t dfs(Node* root) {
  if (!root->left) {
    root->s = new ordered_set();
    root->s->insert(root->val);
    return 0;
  }
  assert(root->left && root->right);
  int64_t ret = dfs(root->left) + dfs(root->right);
  Node* u = root->left;
  Node* v = root->right;
  if (u->sz > v->sz) swap(u, v);
  int n1 = u->sz, n2 = v->sz;
  int64_t rev = 0;
  for (int x : *u->s) {
    rev += v->s->order_of_key(x);
  }
  ret += min(1LL*rev, 1LL*n1*n2-rev);
  for (int x : *u->s) {
    v->s->insert(x);
  }
  root->s = v->s;
  return ret;
}

int N;

int main() {
  scanf("%d", &N);
  Node* root = new Node();
  printf("%ld\n", dfs(root));
  return 0;
}
