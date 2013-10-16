import java.util.*;

public class P032D {
    private static class Con {
        private int row;
        private int col;
        private int r;
        
        public Con(int row, int col, int r) {
            this.row = row;
            this.col = col;
            this.r   = r;
        }
        
        public void print() {
            int rp = row + 1;
            int cp = col + 1;
            System.out.printf("%d %d\n", rp, cp);
            System.out.printf("%d %d\n", rp-r, cp);
            System.out.printf("%d %d\n", rp+r, cp);
            System.out.printf("%d %d\n", rp, cp-r);
            System.out.printf("%d %d\n", rp, cp+r);
        }
    }
    
    private static class Pair {
        private int r;
        private int k;
        
        Pair(int r, int k) {
            this.r = r;
            this.k = k;
        }
    }
    
    private final int N;
    private final int M;
    private short[][] sMap;
    private int[] nRad;
    
    private int min4(int a, int b, int c, int d) {
        return Math.min(Math.min(a, b), Math.min(c, d));
    }
    
    private int getRMax(int i, int j) {
        return min4(i, j, N-1-i, M-1-j);
    }
    
    private boolean isCon(int i, int j , int r) {
        return sMap[i][j] == 1 &&
               sMap[i-r][j] == 1 && sMap[i+r][j] == 1 &&
               sMap[i][j-r] == 1 && sMap[i][j+r] == 1;
    }
    
    
    private void check(int i, int j) {
        if (sMap[i][j] == 0) return;
        
        int rMax = getRMax(i, j);
        for (int r = 1; r <= rMax; r++) {
            if (isCon(i, j, r)) ++nRad[r];
        }
    }
    
    private void scan() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                check(i, j);
            }
        }
    }
    
    private Pair searchRadius(int k) {
        int curr = 0;
        for (int i = 1; i < nRad.length; i++) {
            if (curr <= k && k < curr + nRad[i]) return new Pair(i, k-curr);
            curr += nRad[i];
        }
        return null;
    }
    
    private Con searchCon(int r, int k) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (getRMax(i, j) >= r && isCon(i, j, r)) {
                    if (k == 0) return new Con(i, j, r);
                    --k;
                }
            }
        }
        return null;
    }
    
    private void solve(int k) {
        scan();
        
        Pair p = searchRadius(k);
        if (p == null) {
            System.out.println(-1);
            return;
        }
        
        Con con = searchCon(p.r, p.k);
        con.print();
    }
    
    public P032D() {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        M = sc.nextInt();
        int k = sc.nextInt() - 1;
        nRad = new int[Math.min(N, M)];
        sMap = new short[N][M];
        for (int i = 0; i < N; i++) {
            String s = sc.next();
            for (int j = 0; j < M; j++) {
                if (s.charAt(j) == '*') sMap[i][j] = 1;
            }
        }
        
        solve(k);
    }
    
    public static void main(String[] args) {
        P032D solution = new P032D();
    }
}
        
        
        