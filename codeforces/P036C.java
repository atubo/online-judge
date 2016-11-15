import java.util.*;
import java.io.*;

public class P036C {
    private static class Point implements Comparable<Point> {
        private final double x;
        private final double y;
        
        public Point(double x, double y) {
            this.x = x;
            this.y = y;
        }
        
        public int compareTo(Point other) {
            if      (x < other.x) return -1;
            else if (x > other.x) return 1;
            else if (y < other.y) return -1;
            else if (y > other.y) return 1;
            else                  return 0;
        }
        
        public boolean equals(Object o) {
            if (this == o) return true;
            
            if (!(o instanceof Point)) return false;
            
            Point other = (Point)o;
            return x == other.x && y == other.y;
        }
        
        public String toString() {
            return String.format("Point: %.3f %.3f\n", x, y);
        }
            
    }
    
    private static final double XMAX = 100000;
    private static final double YMAX = 100000;
    
    private TreeSet<Point> contour = new TreeSet<Point>();
    
    private Point interpolate(Point p1, Point p2, double x) {
        assert p1.x <= x && x <= p2.x;
        assert p1.x < p2.x;
        
        double y = p1.y + (p2.y - p1.y) / (p2.x - p1.x) * (x - p1.x);
        return new Point(x, y);
    }
    
    private double calcIntercept(Point p, double k) {
        return p.y - k * p.x;
    }
    
    private Point calcSupportPoint(ArrayList<Point> polyline, double k) {
        assert polyline.size() >= 2;
        Point result = null;
        double bMax = -Double.MAX_VALUE;
        for (Point p: polyline) {
            double b = calcIntercept(p, k);
            if (b > bMax) {
                bMax   = b;
                result = p;
            }
        }
        return result;
    }
    
    private void printContour() {
        System.out.println("contour:");
        for (Point p: contour) {
            System.out.print(p);
        }
    }
    
    private void updateContour(Point p, double x1, double x2, double k) {
        double y1 = p.y + k * (x1 - p.x);
        double y2 = p.y + k * (x2 - p.x);
        Point pLast = contour.last();
        if (pLast.y <= y2) {
            contour.clear();
            contour.add(new Point(0, y1));
            contour.add(new Point(x1, y1));
            contour.add(new Point(x2, y2));
            contour.add(new Point(XMAX, y2));
            return;
        }
        Point pPrev = contour.lower(new Point(x2, -YMAX));
        Point pCurr = contour.higher(pPrev);
        while (pCurr.y <= y2) {
            pPrev = pCurr;
            pCurr = contour.higher(pCurr);
        }
        double x3 = pPrev.x + (y2 - pPrev.y) / (pCurr.y - pPrev.y) * (pCurr.x - pPrev.x);
        
        while (contour.first() != pCurr) {
            contour.remove(contour.first());
        }
        
        contour.add(new Point(0, y1));
        contour.add(new Point(x1, y1));
        contour.add(new Point(x2, y2));
        contour.add(new Point(x3, y2));
    }
    
    private ArrayList<Point> getPolyline(double x1, double x2) {
        ArrayList<Point> result = new ArrayList<Point>();
        
        Point p1 = contour.lower(new Point(x1, -YMAX));
        Point p2 = contour.higher(p1);
        assert p1.x < x1 && x1 <= p2.x;
        if (x1 < p2.x) {
            result.add(interpolate(p1, p2, x1));
        }

        Point p4 = contour.higher(new Point(x2, YMAX));
        Point p3 = contour.lower(p4);        
        assert p3.x <= x2 && x2 < p4.x;
        
        Point p = p2;
        while (p != p4) {
            result.add(p);
            p = contour.higher(p);
        }
        
        if (x2 > p3.x) {
            result.add(interpolate(p3, p4, x2));
        }
        
        return result;
    }
    
    private void processOneBowl(double x1, double x2, double h) {
        assert x2 > x1;
        
        ArrayList<Point> polyline = getPolyline(x1, x2);
        
        double k = h / (x2 - x1);
        Point p = calcSupportPoint(polyline, k);
        
        updateContour(p, x1, x2, k);
    }
    
    private void solve() throws FileNotFoundException, UnsupportedEncodingException {
        Scanner sc = new Scanner(new File("input.txt"));
        int n = sc.nextInt();
        
        // "table surface"
        contour.add(new Point(0, 0));
        contour.add(new Point(1, 0));
        contour.add(new Point(XMAX, 0));
        
        for (int i = 0; i < n; i++) {
            int h = sc.nextInt();
            int r = sc.nextInt();
            int R = sc.nextInt();
            processOneBowl(r/2.0, R/2.0, h);
        }
        
        PrintWriter writer = new PrintWriter("output.txt", "UTF-8");
        writer.printf("%.8f\n", contour.last().y);
        writer.close();
    }
    
    public P036C() {
        try {
            solve();
        }
        catch(FileNotFoundException e) {
            System.out.println("File not found.");
        }
        catch(UnsupportedEncodingException e) {
            e.printStackTrace();
        }
    }
    
    public static void main(String[] args) {
        P036C solution = new P036C();
    }
}
            
        

        
        