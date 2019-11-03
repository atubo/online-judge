// https://www.luogu.org/problem/P4205
// [NOI2005]智慧珠游戏

#include <bits/stdc++.h>
using namespace std;

struct Point {
  Point(int xx, int yy): x(xx), y(yy) {}
  bool operator == (const Point& other) const {
    return x == other.x && y == other.y;
  }
  bool operator != (const Point& other) const {
    return !(*this == other);
  }
  bool operator < (const Point& other) const {
    if (y != other.y) return y < other.y;
    return x < other.x;
  }
  int x, y;
};

struct Rep {
  Rep(const vector<Point>& points): pts(points) {
    xmin = ymin = INT_MAX;
    xmax = ymax = INT_MIN;
    for (const Point& p: pts) {
      xmin = min(xmin, p.x);
      xmax = max(xmax, p.x);
      ymin = min(ymin, p.y);
      ymax = max(ymax, p.y);
    }
  }
  vector<Point> pts;
  int xmin, xmax, ymin, ymax;
};

class Part {
 public:
  Part(const vector<string>& raw): n_(0) {
    vector<Point> r0;
    for (int i = 0; i < (int)raw.size(); i++) {
      for (int j = 0; j < (int)raw[i].length(); j++) {
        if (raw[i][j] == '1') {
          n_++;
          r0.emplace_back(j, i);
        }
      }
    }
    build(normalize(std::move(r0)));
  }

  int n_;
  vector<Rep> rep_;

 private:
  void check(const vector<Point>& r, queue<vector<Point>>& q) {
    if (!contains(r)) {
      rep_.emplace_back(r);
      q.push(r);
    }
  }

  void build(const vector<Point>& r0) {
    queue<vector<Point>> q;
    q.push(r0);
    rep_.emplace_back(r0);
    while (!q.empty()) {
      auto r = q.front();
      q.pop();
      check(rotate(r), q);
      check(xmirror(r), q);
      check(ymirror(r), q);
    }
  }

  static vector<Point> normalize(vector<Point>&& r) {
    vector<Point> ret = r;
    int ymin = INT_MAX, xmin = INT_MAX;
    for (const Point& p: ret) {
      if (p.y < ymin || (p.y == ymin && p.x < xmin)) {
        ymin = p.y;
        xmin = p.x;
      }
    }

    for (Point& p: ret) {
      p.x -= xmin;
      p.y -= ymin;
    }
    sort(ret.begin(), ret.end());
    return ret;
  }

  static vector<Point> rotate(const vector<Point>& r) {
    vector<Point> ret;
    for (const Point& p: r) {
      ret.emplace_back(-p.y, p.x);
    }
    return normalize(std::move(ret));
  }

  static vector<Point> xmirror(const vector<Point>& r) {
    vector<Point> ret;
    for (const Point& p: r) {
      ret.emplace_back(p.x, -p.y);
    }
    return normalize(std::move(ret));
  }

  static vector<Point> ymirror(const vector<Point>& r) {
    vector<Point> ret;
    for (const Point& p: r) {
      ret.emplace_back(-p.x, p.y);
    }
    return normalize(std::move(ret));
  }

  static bool isSame(const vector<Point>& r1, const vector<Point>& r2) {
    assert(r1.size() == r2.size());
    for (int i = 0; i < (int)r1.size(); i++) {
      if (r1[i] != r2[i]) return false;
    }
    return true;
  }

  bool contains(const vector<Point>& r) const {
    for (const auto& t: rep_) {
      if (isSame(t.pts, r)) return true;
    }
    return false;
  }
};

int DX[4] = {1, 0, -1, 0};
int DY[4] = {0, 1, 0, -1};
bool vis[10][10];

class Board {
 public:
  static const int n = 10;
  int** board_;
  Board() {
    alloc();
  }

  ~Board() {
    dealloc();
  }

  bool apply(int x, int y, const Rep& rep, int k) {
    if (x + rep.xmin < 0 || x + rep.xmax >= n) return false;
    if (y + rep.ymin < 0 || y + rep.ymax >= n) return false;
    if (x + rep.xmax > y + rep.ymax) return false;
    for (const Point& p: rep.pts) {
      int x2 = x + p.x;
      int y2 = y + p.y;
      if (!check(x2, y2)) return false;
    }
    for (const Point& p: rep.pts) {
      int x2 = x + p.x;
      int y2 = y + p.y;
      board_[x2][y2] = k;
    }
    return true;
  }

  void unapply(int x, int y, const vector<Point>& part) {
    for (const Point& p: part) {
      int x2 = x + p.x;
      int y2 = y + p.y;
      board_[x2][y2] = -1;
    }
  }

  void print() const {
    for (int y = 0; y < n; y++) {
      for (int x = 0; x <= y; x++) {
        printf("%c", board_[x][y] + 'A');
      }
      printf("\n");
    }
  }

  int bfs(int x0, int y0) const {
    queue<Point> q;
    q.push(Point(x0, y0));
    vis[x0][y0] = true;
    int sz = 1;
    while (!q.empty()) {
      Point p = q.front();
      q.pop();
      for (int d = 0; d < 4; d++) {
        int x = p.x + DX[d];
        int y = p.y + DY[d];
        if (check(x, y) && !vis[x][y]) {
          q.push(Point(x, y));
          vis[x][y] = true;
          sz++;
        }
      }
    }
    return sz;
  }

  Point findStart2(int& ret) const {
    memset(vis, 0, sizeof(vis));
    int minsz = INT_MAX, x0 = -1, y0 = -1;
    for (int y = 0; y < n; y++) {
      for (int x = 0; x <= y; x++) {
        if (!vis[x][y] && board_[x][y] == -1) {
          int sz = bfs(x, y);
          if (sz < minsz) {
            minsz = sz;
            x0 = x;
            y0 = y;
          }
        }
      }
    }
    ret = minsz;
    return Point{x0, y0};
  }

  Point findStart() const {
    Point ret{-1, -1};
    bool found = false;
    for (int y  = 0; y < n; y++) {
      for (int x = 0; x <= y; x++) {
        if (board_[x][y] == -1) {
          ret.x = x;
          ret.y = y;
          found = true;
          break;
        }
      }
      if (found) break;
    }
    return ret;
  }

 private:
  void alloc() {
    board_ = new int*[n]{};
    for (int i = 0; i < n; i++) {
      board_[i] = new int[n]{};
      memset(board_[i], -1, n*sizeof(int));
    }
  }

  void dealloc() {
    for (int i = 0; i < n; i++) {
      delete[] board_[i];
    }
    delete[] board_;
  }

  bool check(int x, int y) const {
    if (x < 0 || y < 0) return false;
    if (x >= n || y >= n) return false;
    return (x <= y && board_[x][y] == -1);
  }
};

bool used[12];

bool dfs(Board& board, int n, const vector<Part>& parts) {
  if (n == 0) return true;
  int sz;
  Point p = board.findStart2(sz);
  for (int k = 0; k < 12; k++) {
    if (parts[k].n_ > sz) break;
    if (!used[k]) {
      for (const Rep& r: parts[k].rep_) {
        if (board.apply(p.x, p.y, r, k)) {
          used[k] = true;
          bool ok = dfs(board, n-1, parts);
          if (ok) return true;
          board.unapply(p.x, p.y, r.pts);
          used[k] = false;
        }
      }
    }
  }
  return false;
}

int main() {
  vector<Part> parts;
  parts.emplace_back(vector<string>{"11", "10"});     // A
  parts.emplace_back(vector<string>{"1111"});         // B
  parts.emplace_back(vector<string>{"111", "100"});   // C
  parts.emplace_back(vector<string>{"11", "11"});     // D
  parts.emplace_back(vector<string>{"1", "1", "111"});// E
  parts.emplace_back(vector<string>{"1111", "01"});   // F
  parts.emplace_back(vector<string>{"111", "101"});   // G
  parts.emplace_back(vector<string>{"111", "110"});   // H
  parts.emplace_back(vector<string>{"111", "0011"});  // I
  parts.emplace_back(vector<string>{"010", "111", "010"});  // J
  parts.emplace_back(vector<string>{"1", "11", "011"});  // K
  parts.emplace_back(vector<string>{"1111", "1"});       // L

  char line[20];
  Board board;
  for (int y = 0; y < 10; y++) {
    scanf("%s", line);
    for (int x = 0; x <= y; x++) {
      if (line[x] == '.') continue;
      int k = line[x] - 'A';
      used[k] = true;
      board.board_[x][y] = k;
    }
  }

  int n = 12;
  for (int k = 0; k < 12; k++) n -= used[k];

  bool ok = dfs(board, n, parts);
  if (ok) {
    board.print();
  } else {
    printf("No solution\n");
  }
  return 0;
}
