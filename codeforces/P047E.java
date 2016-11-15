import java.util.*;

public class P047E {
    private static final double g = 9.8;
    private final int N;
    private final int M;
    private final double V;
    private final double[] shots;
    private final Wall[] walls;
    private ArrayList<Threshold> alpha_th;
    
    private static class Wall implements Comparable<Wall> {
        private final double x;
        private final double y;
        
        public Wall(double x, double y) {
            this.x = x;
            this.y = y;
        }
        
        public int compareTo(Wall other) {
            int cmpx = Double.compare(x, other.x);
            return (cmpx != 0 ? cmpx : Double.compare(y, other.y));
        }
    }
    
    private static class Threshold {
        private final double x;
        private final double alpha;
        
        public Threshold(double x, double alpha) {
            this.x     = x;
            this.alpha = alpha;
        }
    }
    
    private double getAlpha(double x, double y) {
        double a = 0.5 * g * x * x / (V * V);
        double b = -x;
        double c = y + a;
        double delta = b*b - 4*a*c;
        if (delta < 0) {
            return Math.PI/4;
        }
        double talpha = (-b - Math.sqrt(delta)) / (2*a);
        return Math.atan(talpha);
    }
    
    private static double range(double v, double alpha) {
        return v * v * Math.sin(2*alpha) / g;
    }
    
    private static double height(double v, double x, double alpha) {
        double t = x / (v * Math.cos(alpha));
        double h = v * Math.sin(alpha) * t - 0.5 * g * t * t;
        assert h >= 0;
        return h;
    }
    
    private static void print(double x, double  y) {
        System.out.printf("%.10f %.10f\n", x, y);
    }
    
    private void shotGround(double alpha) {
        double x = range(V, alpha);
        print(x, 0);
    }
    
    private void shotWall(Threshold th, double alpha) {
        double xrange = range(V, alpha);
        if (xrange < th.x) {
            print(xrange, 0);
        } else {
            double h = height(V, th.x, alpha);
            print(th.x, h);
        }
    }
    
    private void solveOneShot(double alpha) {
        int i = 0;
        int j = alpha_th.size() - 1;
        if (alpha > alpha_th.get(j).alpha) {
            shotGround(alpha);
            return;
        }
        if (alpha <= alpha_th.get(i).alpha) {
            shotWall(alpha_th.get(i), alpha);
            return;
        }
        while (j > i+1) {
            int mid = (j + i) / 2;
            if (alpha <= alpha_th.get(mid).alpha) {
                j = mid;
            } else {
                i = mid;
            }
        }
        shotWall(alpha_th.get(j), alpha);
    }
        
    
    private void solve() {
        double[] alpha_th0 = new double[M];
        for (int i = 0; i < M; i++) {
            alpha_th0[i] = getAlpha(walls[i].x, walls[i].y);
        }
        
        alpha_th = new ArrayList<Threshold>();
        double currAlpha = -1;
        for (int i = 0; i < M; i++) {
            double alpha = alpha_th0[i];
            if (alpha > currAlpha) {
                alpha_th.add(new Threshold(walls[i].x, alpha));
                currAlpha = alpha;
            }
        }
        
        for (double shot: shots) {
            solveOneShot(shot);
        }
    }
    
    public P047E() {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        V = sc.nextInt();
        shots = new double[N];
        for (int i = 0; i < N; i++) {
            shots[i] = sc.nextDouble();
        }
        M = sc.nextInt();
        walls = new Wall[M];
        for (int i = 0; i < M; i++) {
            double x = sc.nextDouble();
            double y = sc.nextDouble();
            walls[i] = new Wall(x, y);
        }
        Arrays.sort(walls);
    }
    
    public static void main(String[] args) {
        P047E solution = new P047E();
        solution.solve();
    }
}
        