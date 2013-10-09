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
    private ArrayList<HashSet<Pair>> distArray = new ArrayList<HashSet<Pair>>(1001);
    private final int N;
    private Scanner sc = new Scanner(System.in);
    
    public P025C() {
        for (int i = 0; i <= 1000; i++) {
            distArray.add(new HashSet<Pair>());
        }
        N = sc.nextInt();
        distMatrix = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                distMatrix[i][j] = sc.nextInt();
                if (i < j) {
                    distArray.get(dist(i, j)).add(new Pair(i, j));
                }
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
        Pair pair = new Pair(i, j);

        distMatrix[i][j] = distMatrix[j][i] = d_new;
        distArray.get(d_old).remove(pair);
        distArray.get(d_new).add(pair);
    }
    
    private int dist(int i, int j) {
        return distMatrix[i][j];
    }
    
    private void updateEntry(int i, int j, int k, int l) {
        int d = Math.min(dist(k, i) + dist(i, j) + dist(j, l),
                         dist(k, j) + dist(j, i) + dist(i, l));
        d = Math.min(d, dist(k, l));
        if (d < dist(k, l)) {
            update(k, l, dist(k, l), d);
        }
    }
    
    private int sum() {
        int total = 0;
        for (int i = 1; i <= 1000; i++) {
            total += i * distArray.get(i).size();
        }
        return total;
    }
    
    private void connect(int a, int b, int c) {
        if (c >= dist(a, b)) return;
        update(a, b, dist(a, b), c);
        for (int i = 1; i <= 1000; i++) {
            for (Pair p: distArray.get(i)) {
                updateEntry(a, b, p.i, p.j);
            }
        }
    }
        
    public static void main(String[] argv) {
        P025C solution = new P025C();
        solution.solve();
    }
        
}