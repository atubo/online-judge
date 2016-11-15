import java.util.*;

public class P386B {
    private static class BIT {
        private final int N;
        private int[] tree;
        
        public BIT(int N) {
            this.N = N;
            tree = new int[N + 1];
        }
        
        private void set(int x, int v) {
            while (x <= N) {
                tree[x] += v;
                x += (x & -x);
            }
        }
        
        private int get(int x) {
            int res = 0;
            while (x != 0) {
                res += tree[x];
                x -= (x & -x);
            }
            return res;
        }
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        final int N = sc.nextInt();
        int tmax = 0;
        int[] t = new int[N];
        for (int i = 0; i < N; i++) {
            t[i] = sc.nextInt();
            tmax = Math.max(tmax, t[i]);
        }
        
        BIT counter = new BIT(tmax);
        for (int i = 0; i < N; i++) {
            counter.set(t[i], 1);
        }
        
        int T = sc.nextInt();
        int result = counter.get(Math.min(tmax, 1+T));
        for (int i = 2; i <= tmax - T; i++) {
            result = Math.max(result, counter.get(i+T) - counter.get(i-1));
        }
        System.out.println(result);
    }
}
