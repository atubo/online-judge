import java.util.*;

public class P075D {
    private static class Quad {
        private final int left;
        private final int right;
        private final int middle;
        private final int whole;
        private final int maxValue;
        
        public Quad(int left, int right, int middle, int whole, int maxValue) {
            this.left     = left;
            this.right    = right;
            this.middle   = middle;
            this.whole    = whole;
            this.maxValue = maxValue;
        }
    }
    
    private Quad analyzeSA(int[] a) {
        int len = a.length;
        int left = 0;
        int ps = 0;
        int maxValue = Integer.MIN_VALUE;
        for (int i = 0; i < len; i++) {
            ps += a[i];
            left = Math.max(left, ps);
            maxValue = Math.max(maxValue, a[i]);
        }
        int whole = ps;
        
        int right = 0;
        ps = 0;
        for (int i = len-1; i >= 0; i--) {
            ps += a[i];
            right = Math.max(right, ps);
        }
        
        int middle = 0;
        int dp = 0;
        for (int i = 0; i < len; i++) {
            dp = Math.max(dp + a[i], 0);
            middle = Math.max(middle, dp);
        }
        
        return new Quad(left, right, middle, whole, maxValue);
    }
    
    private long max3(long x1, long x2, long x3) {
        return Math.max(Math.max(x1, x2), x3);
    }
    
    private void solve() {
        long dp = 0;
        long result = 0;
        
        for (int index: indices) {
            Quad q = quads[index];
            result = max3((long)q.middle, dp + q.left, result);
            dp = Math.max(dp + q.whole, q.right);
        }
        result = Math.max(result, dp);
        
        System.out.println(result);
    }
    
    private int findMaxElem() {
        int result = Integer.MIN_VALUE;
        for (int index: indices) {
            Quad q = quads[index];
            result = Math.max(q.maxValue, result);
        }
        
        return result;
    }
        
    private int[][] a;
    private int[] indices;
    private Quad[] quads;
    
    public P075D() {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        a = new int[n][];
        for (int i = 0; i < n; i++) {
            int l = sc.nextInt();
            a[i] = new  int[l];
            for (int j = 0; j < l; j++) {
                a[i][j] = sc.nextInt();
            }
        }
        
        indices = new int[m];
        for (int i = 0; i < m; i++) {
            indices[i] = sc.nextInt() - 1;
        }
        
        quads = new Quad[n];
        for (int i = 0; i < n; i++) {
            quads[i] = analyzeSA(a[i]);
        }
        
        int maxElem = findMaxElem();
        if (maxElem > 0) {
            solve();
        } else {
            System.out.println(maxElem);
        }
    }
    
    public static void main(String[] args) {
        P075D solution = new P075D();
    }
}
            
        
        
            