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
    
    private Ring[] rings;
    private int[][] dp;
    
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
                    dp[k][j] = dp[k][j-1];
                }
                continue;
            }
            System.out.println(ring);
            System.out.printf("%d %d\n", i, j);
            printdp();
            for (int k = j-1; k >= i+1; k--) {
                dp[k][j] = dp[k][j-1];
            }
            if (i == j-1) dp[i][j] = 1;
            else          dp[i][j] = 1 + dp[i+1][j-1];
            for (int k = i-1; k >= 0; k--) {
                dp[k][j] = Math.max(dp[k][j-1], dp[k][i-1] + dp[i+1][j-1] + 1);
            }
        }
    }
    
    public P039C() {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        rings = new Ring[2*n];
        dp = new int[2*n][2*n];
        for (int i = 0; i < n; i++) {
            int c = sc.nextInt();
            int r = sc.nextInt();
            rings[2*i]   = new Ring(0, c-r, r, i);
            rings[2*i+1] = new Ring(1, c+r, r, i);
            rings[2*i].setOppo(rings[2*i+1]);
            rings[2*i+1].setOppo(rings[2*i]);
        }
        
        Arrays.sort(rings);
        for (int i = 0; i < 2*n; i++) {
            rings[i].setIndex(i);
            System.out.println(rings[i]);
        }
        
        solve();
        
        System.out.printf("%d\n", dp[0][2*n-1]);
    }
    
    public static void main(String[] args) {
        P039C solution = new P039C();
    }
};
            