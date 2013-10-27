import java.util.*;

public class P039C {
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
    
    private static class Segment implements Comparable<Segment> {
        private int left;
        private int right;
        private int id;
        
        public Segment(int left, int right, int id) {
            this.left  = left;
            this.right = right;
            this.id    = id;
        }
        
        public int compareTo(Segment other) {
            if      (right < other.right) return -1;
            else if (right > other.right) return 1;
            else if (left  > other.left)  return -1;
            else                          return 1;
        }
    }
    
    private Segment[] segments;
    private int[][] dp;
    private boolean[][] r;
    private int[] prev;
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
    
    /*private void solve() {
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
    }*/
    
    private int solve(int i, int j) {
        if (j < 0) return 0;
        if (segments[j].right <= segments[i].left) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        
        int res = solve(i, j-1);
        if (segments[j].left >= segments[i].left) {
            int cur = solve(i, prev[j]) + solve(j, j-1) + 1;
            if (cur > res) {
                res = cur;
                r[i][j] = true;
            }
        }
        return dp[i][j] = res;
    }
    
    private void build(int i, int j) {
        if (j < 0) return;
        if (segments[j].right <= segments[i].left) return;
        if (r[i][j]) {
            System.out.printf("%d ", segments[j].id);
            build(i, prev[j]);
            build(j, j-1);
        }
        else {
            build(i, j-1);
        }
    }
        
    
    public P039C() {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        
        segments = new Segment[N];
        dp = new int[N][N];
        r  = new boolean[N][N];
        prev = new int[N];
        for (int[] row: dp) {
            Arrays.fill(row, -1);
        }
        pred = new Predecessor[2*N][2*N];

        for (int i = 0; i < N; i++) {
            int c = sc.nextInt();
            int r = sc.nextInt();
            segments[i] = new Segment(c-r, c+r, i+1);
        }
        
        Arrays.sort(segments);
        int minLeft = segments[0].left;
        int minIndex = 0;
        for (int i = 1; i < N; i++) {
            if (segments[i].left < minLeft) {
                minLeft = segments[i].left;
                minIndex = i;
            }
        }
        
        for (int i = N-1; i >= 0; i--) {
            int left = segments[i].left;
            int p = i-1;
            while (p >= 0 && segments[p].right > left) p--;
            prev[i] = p;
        }
        
        System.out.println(solve(minIndex, N-1));
        build(minIndex, N-1);

        
        //solve();
        
        //System.out.printf("%d\n", dp[2*N-1][0]);
        
        // print crater list
        /*java.util.Queue<Predecessor> queue = new ArrayDeque<Predecessor>();
        queue.add(pred[2*N-1][0]);
        while (!queue.isEmpty()) {
            Predecessor p = queue.poll();
            System.out.printf("%d ", p.id);
            if (p.p1 != null) queue.add(p.p1);
            if (p.p2 != null) queue.add(p.p2);
        }
        System.out.println();*/
    }
    
    public static void main(String[] args) {
        P039C solution = new P039C();
    }
};
            