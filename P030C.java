import java.util.*;

public class P030C {
    private static class Target {
        private int x;
        private int y;
        private int t;
        private double p;
        
        public Target(int x, int y, int t, double p) {
            this.x = x;
            this.y = y;
            this.t = t;
            this.p = p;
        }
        
        public String toString() {
            return "Target: " + x + " " + y + " " + t + " " + p;
        }
    }
    
    private Target[] targets;
    private final int N;
    
    public double solve() {
        Arrays.sort(targets, new Comparator<Target>() {
            public int compare(Target t1, Target t2) {
                return ((Integer)t1.t).compareTo((Integer)t2.t);
            }
        });
        
        double maxProb = 0;
        double[] dp = new double[N];
        for (int i = N-1; i >= 0; i--) {
            double maxExtra = 0;
            for (int j = i+1; j < N; j++) {
                if (inRange(i, j)) {
                    maxExtra = Math.max(maxExtra, dp[j]);
                }
            }
            dp[i] = targets[i].p + maxExtra;
            maxProb = Math.max(maxProb, dp[i]);
        }
        
        return maxProb;
    }
    
    private boolean inRange(int i, int j) {
        long x1 = targets[i].x;
        long y1 = targets[i].y;
        long t1 = targets[i].t;
        long x2 = targets[j].x;
        long y2 = targets[j].y;
        long t2 = targets[j].t;
        return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) <= (t1-t2)*(t1-t2);
    }
    
    public P030C() {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        targets = new Target[N];
        for (int i = 0; i < N; i++) {
            int x = sc.nextInt();
            int y = sc.nextInt();
            int t = sc.nextInt();
            double p = sc.nextDouble();
            targets[i] = new Target(x, y, t, p);
        }
        
        double p = solve();
        System.out.printf("%.10f\n", p);
    }
    
    public static void main(String[] args) {
        P030C solution = new P030C();
    }
}