import java.util.*;

public class P039C {
    
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
    }
    
    public static void main(String[] args) {
        P039C solution = new P039C();
    }
};
            