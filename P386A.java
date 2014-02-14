import java.util.*;

public class P386A {
    private static class Bid implements Comparable<Bid> {
        private final int id;
        private final int price;
        
        public Bid(int price, int id) {
            this.price = price;
            this.id    = id;
        }
        
        @Override
        public int compareTo(Bid other) {
            if (price > other.price) return -1;
            if (price < other.price) return 1;
            return 0;
        }
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        Bid[] bids = new Bid[n];
        for (int i = 0; i < n; i++) {
            int x = sc.nextInt();
            bids[i] = new Bid(x, i+1);
        }
        Arrays.sort(bids);
        System.out.printf("%d %d\n", bids[0].id, bids[1].price);
    }
}