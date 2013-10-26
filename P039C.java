import java.util.*;

public class P039C {
    private static class Ring implements Comparable<Ring> {
        private int type;    // left - 0, right - 1
        private int pos;
        private int id;
        private int radius;
        
        private Ring oppo; // opposite ring
        private int index;
        
        public Ring(int type, int pos, int radius, int id) {
            this.type    = type;
            this.pos     = pos;
            this.radius  = radius;
            this.id      = id;
        }
        
        public void setOppo(Ring oppo) {
            this.oppo = oppo;
        }
        
        public void setIndex(int index) {
            this.index = index;
        }
        
        public int compareTo(Ring other) {
            if      (pos < other.pos) return -1;
            else if (pos > other.pos) return 1;
            else if (type > other.type) return -1;  // right < left
            else if (type < other.type) return 1;
            else {
                if (type == 0) return other.radius - radius;
                else           return radius - other.radius;
            }
        }
        
        public String toString() {
            String result = "ring: type = " + type + " id = " + id + " index = " + index;
            return result;
        }
    };
    
    private static class Predecessor {
        private int id;
        private Predecessor p1;
        private Predecessor p2;
        
        public Predecessor(int id, Predecessor p1, Predecessor p2) {
            this.id = id;
            this.p1 = p1;
            this.p2 = p2;
        }
    };
    
    private Ring[] rings;
    private int[][] dp;
    private Predecessor[][] pred;
    private final int N;
    
    private void printdp() {
        int n = dp.length;
        System.out.println("DP table");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                System.out.printf("%d ", dp[i][j]);
            }
            System.out.printf("\n");
        }
    }
    
    private void solve() {
        for (Ring ring: rings) {
            int i = ring.oppo.index;
            int j = ring.index;
            if (ring.type == 0) {
                for (int k = j-1; k >= 0; k--) {
                    dp[j][k] = dp[j-1][k];
                    pred[j][k] = pred[j-1][k];
                }
                continue;
            }
            
            for (int k = j-1; k >= i+1; k--) {
                dp[j][k] = dp[j-1][k];
                pred[j][k] = pred[j-1][k];
            }
            if (i == j-1) {
                dp[j][i] = 1;
                pred[j][i] = new Predecessor(ring.id, null, null);
            }
            else {
                dp[j][i] = 1 + dp[j-1][i+1];
                pred[j][i] = new Predecessor(ring.id, pred[j-1][i+1], null);
            }
            for (int k = i-1; k >= 0; k--) {
                if (i == j-1) {
                    dp[j][k] = Math.max(dp[j-1][k], dp[i-1][k] + 1);
                    if (dp[j-1][k] > dp[i-1][k]+1) {
                        pred[j][k] = pred[j-1][k];
                    }
                    else {
                        pred[j][k] = new Predecessor(ring.id, pred[i-1][k], null);
                    }
                }
                else {
                    dp[j][k] = Math.max(dp[j-1][k], dp[i-1][k] + dp[j-1][i+1] + 1);
                    if (dp[j-1][k] > dp[i-1][k] + dp[j-1][i+1] + 1) {
                        pred[j][k] = pred[j-1][k];
                    }
                    else {
                        pred[j][k] = new Predecessor(ring.id, pred[i-1][k], pred[j-1][i+1]);
                    }
                }
            }
        }
    }
    
    public P039C() {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        rings = new Ring[2*N];
        dp = new int[2*N][2*N];
        pred = new Predecessor[2*N][2*N];
        for (int i = 0; i < N; i++) {
            int c = sc.nextInt();
            int r = sc.nextInt();
            rings[2*i]   = new Ring(0, c-r, r, i+1);
            rings[2*i+1] = new Ring(1, c+r, r, i+1);
            rings[2*i].setOppo(rings[2*i+1]);
            rings[2*i+1].setOppo(rings[2*i]);
        }
        
        Arrays.sort(rings);
        for (int i = 0; i < 2*N; i++) {
            rings[i].setIndex(i);
        }
        
        solve();
        
        System.out.printf("%d\n", dp[2*N-1][0]);
        
        // print crater list
        java.util.Queue<Predecessor> queue = new ArrayDeque<Predecessor>();
        queue.add(pred[2*N-1][0]);
        while (!queue.isEmpty()) {
            Predecessor p = queue.poll();
            System.out.printf("%d ", p.id);
            if (p.p1 != null) queue.add(p.p1);
            if (p.p2 != null) queue.add(p.p2);
        }
        System.out.println();
    }
    
    public static void main(String[] args) {
        P039C solution = new P039C();
    }
};
            