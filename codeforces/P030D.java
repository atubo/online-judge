import java.util.*;

public class P030D {
    private long[] pos;
    private long cx;
    private long cy;
    private final int N;
    
    private double distToC(int i) {
        long dx = cx - pos[i];
        return Math.sqrt(dx*dx + cy*cy);
    }
    
    private double dist(int i, int j) {
        return (double)Math.abs(pos[i] - pos[j]);
    }
    
    private double solveC(int i, int j) {
        double d1 = distToC(i);
        double d2 = distToC(j);
        return Math.min(d1, d2) + dist(i, j);
    }
    
    private double solveMiddle(int k) {
        assert 0 < k && k < N-1;
        double result = dist(0, k) + distToC(0) + solveC(k+1, N-1);
        result = Math.min(result, dist(k, N-1) + distToC(N-1) + solveC(0, k-1));
        for (int i = 0; i < N; i++) {
            if (i <= k) {
                double d0 = (i > 0 ? solveC(0, i-1) : 0);
                result = Math.min(result, 2 * dist(k, N-1) + dist(i, k) + distToC(i) + d0);
                result = Math.min(result, 2 * dist(i, k) + dist(k, N-1) + distToC(N-1) + d0);
            }
            else {
                double d0 = (i < N-1 ? solveC(i+1, N-1) : 0);
                result = Math.min(result, 2 * dist(0, k) + dist(k, i) + distToC(i) + d0);
                result = Math.min(result, 2 * dist(k, i) + dist(0, k) + distToC(0) + d0);
            }
        }
        return result;
    }
    
    private double solveLeftEnd() {
        double result = Double.MAX_VALUE;
        for (int i = 0; i < N-1; i++) {
            double d = dist(0, i) + distToC(i) + solveC(i+1, N-1);
            result = Math.min(result, d);
        }
        // last one
        double d = dist(0, N-1) + distToC(N-1);
        result = Math.min(result, d);
        
        return result;
    }
    
    private double solveRightEnd() {
        double result = Double.MAX_VALUE;
        for (int i = N-1; i > 0; i--) {
            double d = dist(i, N-1) + distToC(i) + solveC(0, i-1);
            result = Math.min(result, d);
        }
        double d = dist(0, N-1) + distToC(0);
        result = Math.min(result, d);
        
        return result;
    }
    
    private double solve(int k) {
        if (k == N) {
            Arrays.sort(pos);
            return solveC(0, N-1);
        }

        long xk = pos[k];
        int k2 = -1;
        Arrays.sort(pos);

        for (int i = 0; i < pos.length; i++) {
            if (pos[i] == xk) {
                k2 = i;
                break;
            }
        }

        if (k2 == 0) {
            return solveLeftEnd();
        }
        else if (k2 == N-1) {
            return solveRightEnd();
        }
        else {
            return solveMiddle(k2);
        }
    }
    
    public P030D() {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        int k = sc.nextInt() - 1;
        pos = new long[N];
        for (int i = 0; i < N; i++) {
            pos[i] = sc.nextInt();
        }
        cx = sc.nextInt();
        cy = sc.nextInt();
        
        double result = solve(k);
        System.out.printf("%.10f\n", result);
    }
    
    public static void main(String[] args) {
        P030D solution = new P030D();
    }
}
