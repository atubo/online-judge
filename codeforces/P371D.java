import java.util.*;

public class P371D {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] capacity = new int[n];
        TreeMap<Integer, Integer> residual = new TreeMap<Integer, Integer>();
        for (int i = 0; i < n; i++) {
            capacity[i] = sc.nextInt();
            residual.put(i, capacity[i]);
        }
        
        int m = sc.nextInt();
        for (int i = 0; i < m; i++) {
            int q = sc.nextInt();
            if (q == 1) {
                int p = sc.nextInt() - 1;
                int x = sc.nextInt();
                Map.Entry<Integer, Integer> entry = residual.ceilingEntry(p);
                while (entry != null) {
                    int k = entry.getKey();
                    int v = entry.getValue();
                    if (x < v) {
                        residual.put(k, v-x);
                        break;
                    } else {
                        x -= v;
                        entry = residual.higherEntry(k);
                        residual.remove(k);
                    }
                }
            } else {
                int k = sc.nextInt() - 1;
                Integer ri = residual.get(k);
                int r = (ri != null ? ri : 0);
                System.out.println(capacity[k] - r);
            }
        }
    }
}
                        
                