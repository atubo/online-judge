import java.util.*;

public class P366E {
    private final int[][] highest;
    private final int[][] lowest;
    private final int[] upper;  // minimum x - y
    private final int[] lower;  // minimum x + y
    
    private final int N;
    private final int M;
    private final int K;
    
    private final boolean[][] neighbor;
    private final int[][] dist;
    
    private void solve() {
        for (int i = 0; i < K; i++) {
            upper[i] = Integer.MAX_VALUE;
            lower[i] = Integer.MAX_VALUE;
        }
        
        for (int i = 0; i < K; i++) {
            if (highest[0][i] >= 0) {
                assert lowest[0][i] >= 0;
                upper[i] = - highest[0][i];
                lower[i] = lowest[0][i];
            }
        }
        
        for (int col = 1; col < M; col++) {
            for (int i = 0; i < K; i++) {
                if (highest[col][i] == -1) continue;
                assert lowest[col][i] != -1;
                
                int h = highest[col][i];
                int l = lowest[col][i];
                
                for (int j = 0; j < K; j++) {
                    if (upper[j] == Integer.MAX_VALUE) continue;
                    assert lower[j] != Integer.MAX_VALUE;
                    
                    int dh = Math.max(col - h - upper[j], col + h - lower[j]);
                    int dl = Math.max(col - l - upper[j], col + l - lower[j]);
                    int d = Math.max(dh, dl);
                    
                    if (i < j) dist[i][j] = Math.max(dist[i][j], d);
                    else       dist[j][i] = Math.max(dist[j][i], d);
                }
                
                upper[i] = Math.min(upper[i], col - h);
                lower[i] = Math.min(lower[i], col + l);
            }
        }
        
        int distMax = -1;
        for (int i = 0; i < K; i++) {
            for (int j = i; j < K; j++) {
                if (neighbor[i][j]) {
                    distMax = Math.max(distMax, dist[i][j]);
                }
            }
        }
        
        System.out.println(distMax);
    }
    
    public P366E() {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        M = sc.nextInt();
        K = sc.nextInt();
        int s = sc.nextInt();
        
        upper = new int[K];
        lower = new int[K];
        
        highest = new int[M][K];
        lowest  = new int[M][K];
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < K; j++) {
                highest[i][j] = lowest[i][j] = -1;
            }
        }
        
        for (int i = N-1; i >= 0; i--) {
            for (int j = 0; j < M; j++) {
                int a = sc.nextInt() - 1;
                if (highest[j][a] == -1) highest[j][a] = i;
                lowest[j][a] = i;
            }
        }
        
        neighbor = new boolean[K][K];
        dist     = new int[K][K];
        int[] q = new int[s];
        for (int i = 0; i < s; i++) {
            q[i] = sc.nextInt() - 1;
        }
        for (int i = 1; i < s; i++) {
            int a = q[i-1];
            int b = q[i];
            if (a < b) neighbor[a][b] = true;
            else       neighbor[b][a] = true;
        }
    }
    
    public static void main(String[] args) {
        P366E solution = new P366E();
        solution.solve();
    }
}
                    