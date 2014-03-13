#include <iostream>
using namespace std;

struct Point
{
    Point(): x(0), y(0) {}
    Point(int x_, int y_): x(x_), y(y_) {}
    double x;
    double y;
};

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(Point p, Point q, Point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
       return true;

    return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    // See 10th slides from following link for derivation of the formula
    // http://www.dcs.gla.ac.uk/~pat/52233/slides/Geometry1x1.pdf
    double val = (q.y - p.y) * (r.x - q.x) -
        (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; // Doesn't fall in any of the above cases
}

Point mirror(Point p, int x0, int y0, int x1, int y1)
{

    double dx,dy,a,b;
    double x2,y2;
    Point p1; //reflected point to be returned 

    dx  = (double) (x1 - x0);
    dy  = (double) (y1 - y0);

    a   = (dx * dx - dy * dy) / (dx * dx + dy*dy);
    b   = 2 * dx * dy / (dx*dx + dy*dy);

    x2  = (a * (p.x - x0) + b*(p.y - y0) + x0);
    y2  = (b * (p.x - x0) - a*(p.y - y0) + y0);

    p1 = Point(x2,y2);

    return p1;
}

int main()
{
    int x, y;
    cin >> x >> y;
    Point victor(x, y);
    
    cin >> x >> y;
    Point peter(x, y);

    int x2, y2;
    cin >> x >> y >> x2 >> y2;
    Point pw1(x, y);
    Point pw2(x2, y2);

    cin >> x >> y >> x2 >> y2;
    Point pm1(x, y);
    Point pm2(x2, y2);

    bool canSee = false;

    if (!doIntersect(pm1, pm2, victor, peter)) {
        if (!doIntersect(pw1, pw2, victor, peter)) {
            canSee = true;
        } else {
            Point pv_m = mirror(victor, pm1.x, pm1.y, pm2.x, pm2.y);
            if (doIntersect(pm1, pm2, pv_m, peter)) {
                canSee = true;
            }
        }
    } else if (orientation(pm1, pm2, victor) == 0 &&
               orientation(pm1, pm2, peter) == 0) {
        canSee = true;
    }

    cout << (canSee ? "YES" : "NO") << endl;

    return 0;
}
