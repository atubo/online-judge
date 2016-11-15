import java.util.*;

public class P025C {
    private class Pair {
        private int i;
        private int j;
        private Pair(int i, int j) {
            this.i = Math.min(i, j);
            this.j = Math.max(i, j);
        }
        public int hashCode() {
            
            return 37 * i + j;
        }
        
        public boolean equals(Object other) {
            if (other instanceof Pair) {
                Pair otherPair = (Pair) other;
                return i == otherPair.i && j == otherPair.j;
            }
            
            return false;
        }
    }
    
    private int[][] distMatrix;

    private final int N;
    private Scanner sc = new Scanner(System.in);
    
    public P025C() {
        N = sc.nextInt();
        distMatrix = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                distMatrix[i][j] = sc.nextInt();
            }
        }
    }
    
    public void solve() {
        int k = sc.nextInt();
        for (int i = 0; i < k; i++) {
            int a = sc.nextInt() - 1;
            int b = sc.nextInt() - 1;
            int c = sc.nextInt();
            connect(a, b, c);
            System.out.printf("%d ", sum());
        }
        System.out.println();
    }
    
    private void update(int i, int j, int d_old, int d_new) {
        int d = Math.min(d_old, d_new);
        distMatrix[i][j] = distMatrix[j][i] = d;

    }
    
    private int dist(int i, int j) {
        return distMatrix[i][j];
    }
    
    private void updateEntry(int i, int j, int k, int l) {
        int d = Math.min(dist(k, i) + dist(i, j) + dist(j, l),
                         dist(k, j) + dist(j, i) + dist(i, l));
        d = Math.min(d, dist(k, l));
 
        update(k, l, dist(k, l), d);
        
    }
    
    private long sum() {
        long total = 0;

        for (int i = 0; i < N-1; i++) {
            for (int j = i+1; j < N; j++) {
                total += dist(i, j);
            }
        }
        return total;
    }
    
    private void connect(int a, int b, int c) {
        if (c >= dist(a, b)) return;

        update(a, b, dist(a, b), c);

        for (int i = 0; i < N-1; i++) {
            for (int j = i+1; j < N; j++) {
                updateEntry(a, b, i, j);
            }
        }
    }
        
    public static void main(String[] argv) {
        P025C solution = new P025C();
        solution.solve();
    }
        
}