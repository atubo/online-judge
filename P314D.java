import java.util.*;
import java.io.*;

public class P314D {
    public static class Point {
        private int x;
        private int y;
        
        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
    
    public static Comparator<Point> PointCompX = new Comparator<Point>() {
        public int compare(Point p1, Point p2) {
            if (p1.x < p2.x) return -1;
            if (p1.x > p2.x) return 1;
            return Integer.compare(p1.y, p2.y);
        }
    };
    
    public static Comparator<Point> PointCompY =new Comparator<Point>() {
        public int compare(Point p1, Point p2) {
            if (p1.y < p2.y) return -1;
            if (p1.y > p2.y) return 1;
            return Integer.compare(p1.x, p2.x);
        }
    };
    
    private static class Reader {
        static BufferedReader reader;
        static StringTokenizer tokenizer;
        
        /** call this method to initialize reader for InputStream */
        static void init(InputStream input) {
            reader = new BufferedReader(
                                        new InputStreamReader(input) );
            tokenizer = new StringTokenizer("");
        }
        
        /** get next word */
        static String next() throws IOException {
            while ( ! tokenizer.hasMoreTokens() ) {
                //TODO add check for eof if necessary
                tokenizer = new StringTokenizer(
                                                reader.readLine() );
            }
            return tokenizer.nextToken();
        }
        
        static int nextInt() throws IOException {
            return Integer.parseInt( next() );
        }
        
        static double nextDouble() throws IOException {
            return Double.parseDouble( next() );
        }
    }
    
    private ArrayList<Point> points = new ArrayList<>();
    private final int N;
    private double result = Double.MAX_VALUE;
    
    public P314D() throws IOException {
        Reader.init(System.in);
        N = Reader.nextInt();
        for (int i = 0; i < N; i++) {
            int x = Reader.nextInt();
            int y = Reader.nextInt();
            points.add(new Point(x+y, x-y));
        }
        Collections.sort(points, PointCompX);
    }
    
    public double solve() {
        int left = 0;
        int right = 0;
        TreeSet<Point> xSet = new TreeSet<>(PointCompX);  // points with close x positions
        TreeSet<Point> ySet = new TreeSet<>(PointCompY);
        
        // initialize
        xSet.add(points.get(0));
        for (int i = 1; i < N; i++) {
            ySet.add(points.get(i));
        }
        
        double wx = getWidthX(xSet);
        double wy = getWidthY(ySet);
        updateResult(wx, wy);
        
        mainLoop:
        while (true) {

            while (wx <= wy) {
                // move right end
                right++;
                if (right == N) {
                    break mainLoop;
                }
                xSet.add(points.get(right));
                ySet.remove(points.get(right));
                wx = getWidthX(xSet);
                wy = getWidthY(ySet);
                updateResult(wx, wy);
            }
            
            while (wx > wy) {
                // move left end to right
                xSet.remove(points.get(left));
                ySet.add(points.get(left));
                left++;
                wx = getWidthX(xSet);
                wy = getWidthY(ySet);
                updateResult(wx, wy);
            }
        }
        
        return result/2;
    }
    
    private double getWidthX(TreeSet<Point> pSet) {
        if (pSet.size() == 0) return 0;
        return pSet.last().x - pSet.first().x;
    }
    
    private double getWidthY(TreeSet<Point> pSet) {
        if (pSet.size() == 0) return 0;
        return pSet.last().y - pSet.first().y;
    }  
    
    private void updateResult(double wx, double wy) {
        result = Math.min(result, Math.max(wx, wy));
    }
    
    public static void main(String[] args) throws IOException {
        P314D solution = new P314D();
        double result = solution.solve();
        System.out.printf("%.7f\n", result);
    }
                
        
        
}
        
