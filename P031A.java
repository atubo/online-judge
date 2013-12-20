import java.util.*;

public class P031A {
    private static class Pair implements Comparable<Pair> {
        private final int a;
        private final int id;
        
        public Pair(int a, int id) {
            this.a  = a;
            this.id = id;
        }
        
        public int compareTo(Pair other) {
            if (a < other.a) return -1;
            if (a > other.a) return 1;
            if (id < other.id) return -1;
            if (id > other.id) return 1;
            return 0;
        }
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        Pair[] a = new Pair[n];
        for (int i = 0; i < n; i++) {
            int x = sc.nextInt();
            a[i] = new Pair(x, i + 1);
        }
        Arrays.sort(a);
        
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                for (int k = j + 1; k < n; k++) {
                    if (a[i].a + a[j].a == a[k].a) {
                        System.out.printf("%d %d %d\n", a[k].id, a[j].id, a[i].id);
                        return;
                    }
                }
            }
        }
        
        System.out.println("-1");
    }
}