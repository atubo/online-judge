import java.util.*;

public class P055C {
    private int N;
    private int M;
    
    private int distToBoundary(int row, int col) {
        return Math.min(Math.min(row, N-1-row), Math.min(col, M-1-col));
    }
    
    private void solve() {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        M = sc.nextInt();
        int k = sc.nextInt();
        for (int i = 0; i < k; i++) {
            int row = sc.nextInt() - 1;
            int col = sc.nextInt() - 1;
            if (distToBoundary(row, col) <= 4) {
                System.out.println("YES");
                return;
            }
        }
        System.out.println("NO");
    }
    
    public P055C() {
        solve();
    }
    
    public static void main(String[] args) {
        P055C solution = new P055C();
    }
}