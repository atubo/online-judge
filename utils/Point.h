
struct Point {
    int x, y;
    Point(): x(0), y(0) {}
    Point(int a, int b): x(a), y(b) {};
};

std::istream& operator >> (std::istream &in,
                           Point &pt) {
    char c;
    in >> c;
    assert(c == '[');
    int a, b;
    in >> a >> c >> b;
    assert(c == ',');
    pt.x = a;
    pt.y = b;
    in >> c;
    assert(c == ']');
    return in;
}

std::istream& operator >> (std::istream &in,
                           vector<Point> &pts) {
    char c;
    in >> c;
    assert(c == '[');
    Point pt;
    if (in.peek() != ']') {
        in >> pt;
        pts.push_back(pt);
    }
    while (in.peek() == ',') {
        in.get();
        in >> pt;
        pts.push_back(pt);
    }
    in >> c;
    assert(c == ']');
    return in;
}
