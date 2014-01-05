import java.util.*;

public class P332C {
    private static class Order implements Comparable<Order> {
        private final int a;
        private final int b;
        private final int id;
        
        public Order(int a, int b, int id) {
            this.a  = a;
            this.b  = b;
            this.id = id;
        }
        
        public int compareTo(Order other) {
            // students' preference
            if (a > other.a) return -1;
            if (a < other.a) return 1;
            if (b > other.b) return -1;
            if (b < other.b) return 1;
            return 0;
        }
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int p = sc.nextInt();
        int k = sc.nextInt();
        
        Order[] orders = new Order[n];
        for (int i = 0; i < n; i++) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            orders[i] = new Order(a, b, i+1);
        }
        
        Arrays.sort(orders, new Comparator<Order>() {
            public int compare(Order o1, Order o2) {
                // chairperson's preference
                if (o1.b > o2.b) return -1;
                if (o1.b < o2.b) return 1;
                if (o1.a < o2.a) return -1;
                if (o1.a > o2.a) return 1;
                return 0;
            }
        });
        
        Order[] candidates = new Order[n-p+k];
        for (int i = 0; i < n-p+k; i++) {
            candidates[i] = orders[i];
        }
        Arrays.sort(candidates);
        
        int min_b = Integer.MAX_VALUE;
        Order[] selected = new Order[p];
        for (int i = 0; i < k; i++) {
            selected[i] = candidates[i];
            min_b = Math.min(min_b, selected[i].b);
        }
        
        // find the remaining p-k orders
        ArrayList<Order> remaining = new ArrayList<Order>();
        for (int i = k; i < n-p+k; i++) {
            if (candidates[i].b <= min_b) {
                remaining.add(candidates[i]);
            }
        }
        for (int i = n-p+k; i < n; i++) {
            remaining.add(orders[i]);
        }
        Collections.sort(remaining, new Comparator<Order>() {
            public int compare(Order o1, Order o2) {
                if (o1.b > o2.b) return -1;
                if (o1.b < o2.b) return 1;
                return 0;
            }
        });
        
        for (int i = 0; i < p-k; i++) {
            selected[k+i] = remaining.get(i);
        }
        
        for (int i = 0; i < p; i++) {
            System.out.printf("%d ", selected[i].id);
        }
        System.out.println();
    }
}
    
    