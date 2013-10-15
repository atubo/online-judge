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
    
    private double distBetween(int i, int j) {
        return (double)Math.abs(pos[i] - pos[j]);
    }
    
    private double solveC(int i, int j) {
        double d1 = distToC(i);
        double d2 = distToC(j);
        return Math.min(d1, d2) + distBetween(i, j);
    }
    
    private double solveMiddle(int i) {
        assert 0 < i && i < N-1;
        double d1 = distToC(i) + solveC(0, N-1);
        double d2 = distBetween(0, i) + distToC(0) + solveC(i+1, N-1);
        double d3 = distBetween(i, N-1) + distToC(N-1) + solveC(0, i-1);
        return min3(d1, d2, d3);
    }
    
    private double solveLeftEnd() {
        double result = Double.MAX_VALUE;
        for (int i = 0; i < N-1; i++) {
            double d = distBetween(0, i) + distToC(i) + solveC(i+1, N-1);
            result = Math.min(result, d);
        }
        // last one
        double d = distBetween(0, N-1) + distToC(N-1);
        result = Math.min(result, d);
        
        return result;
    }
    
    private double solveRightEnd() {
        double result = Double.MAX_VALUE;
        for (int i = N-1; i > 0; i--) {
            double d = distBetween(i, N-1) + distToC(i) + solveC(0, i-1);
            result = Math.min(result, d);
        }
        double d = distBetween(0, N-1) + distToC(0);
        result = Math.min(result, d);
        
        return result;
    }
    
    private double min3(double x1, double x2, double x3) {
        return Math.min(Math.min(x1, x2), x3);
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
