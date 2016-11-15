import java.util.*;

public class P022C {
    public P022C(int n, int m, int v) {
        this.N = n;
        this.M = m;
        this.V = v;
    }
    
    public void solve() {
        int n2 = N - 1;
        if (M < g(n2) + 1 || M > f(n2) + 1) {
            System.out.println(-1);
            return;
        }

        if (V > 1) {
            connect(2, N, M-1);
            connect(1, V);
        }
        else {
            connect(1, N-1, M-1);
            connect(1, N);
        }
    }
    
    private int f(int n) {
        return n * (n-1) / 2;
    }
    
    private int g(int n) {
        return n - 1;
    }
    
    private void connect(int i, int j, int m) {
        if (m == 0) return;
        for (int k = i+1; k <= j; k++) {
            if (m == 0) return;
            System.out.printf("%d %d\n", i, k);
            m--;
        }
        connect(i+1, j, m);
    }
    
    private void connect(int i, int j) {
        System.out.printf("%d %d\n", i, j);
    }
            
    private int N;
    private int M;
    private int V;
    
    public static void main(String[] argv) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        int v = sc.nextInt();
        
        P022C solution = new P022C(n, m, v);
        solution.solve();
    }
}