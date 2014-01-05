import java.util.*;

public class P371E {
    private final int N;
    private final int k;
    private final int[] d;
    
    private class Pos implements Comparable<Pos> {
        private final int x;
        private final int id;
        
        public Pos(int x, int id) {
            this.x  = x;
            this.id = id;
        }
        
        public int compareTo(Pos other) {
            if (x < other.x) return -1;
            if (x > other.x) return 1;
            return 0;
        }
    }
    
    public P371E() {
        Scanner sc = new Scanner(System.in);
        // because we will deal with segments
        N = sc.nextInt() - 1;
        
        Pos[] pos = new Pos[N+1];
        for (int i = 0; i < N+1; i++) {
            int x = sc.nextInt();
            pos[i] = new Pos(x, i+1);
        }
        Arrays.sort(pos);
        
        d = new int[N];
        for (int i = 1; i < N+1; i++) {
            d[i-1] = pos[i].x - pos[i-1].x;
        }
        k = sc.nextInt() - 1;
        
        long D1 = 0;
        long D2 = 0;
        for (int i = k-1; i >= 0; i--) {
            D1 += d[i];
            D2 += (2*k - 2*i) * (long)d[i];
        }
        
        long T = 0;
        long Tmin = 0;
        int posMin = k-1;
        
        java.util.Deque<Integer> deque = new ArrayDeque<Integer>();
        for (int i = 0; i < k; i++) {
            deque.add(d[i]);
        }
        
        for (int i = k; i < N; i++) {
            int d0 = deque.pollFirst();
            int dn = d[i];
            deque.add(dn);
            T = T + k*(D1 + dn) - D2;
            D1 = D1 - d0 + dn;
            D2 = D2 - 2*k*d0 + 2*D1;
            if (T < Tmin) {
                Tmin = T;
                posMin = i;
            }
        }
        
        for (int i = posMin - k + 1; i <= posMin + 1; i++) {
            System.out.printf("%d ", pos[i].id);
        }
        System.out.println();
    }
    
    public static void main(String[] args) {
        P371E solution = new P371E();
    }
}