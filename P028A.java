import java.util.*;

public class P028A {
    private class Coord {
        private int x;
        private int y;
        
        public Coord(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
    
    private int dist(int i, int j) {
        Coord c1 = nails.get(i);
        Coord c2 = nails.get(j);
        return Math.abs(c1.x - c2.x) + Math.abs(c1.y - c2.y);
    }
    
    private HashMap<Integer, java.util.Queue<Integer>> rods = new HashMap<Integer, java.util.Queue<Integer>>();
    private final int N;
    private ArrayList<Coord> nails = new ArrayList<Coord>();
    
    private int next(int i) {
        return (i + 1) % N;
    }
    
    private boolean checkPossible(int start) {
        assert 0 <= start && start <= 1;
        HashMap<Integer, Integer> needed = new HashMap<Integer, Integer>();
        for (int i = start; i < N; i += 2) {
            int j = next(i);
            int k = next(j);
            int length = dist(i, j) + dist(j, k);
            if (!needed.containsKey(length)) {
                needed.put(length, 0);
            }
            needed.put(length, needed.get(length) + 1);
        }
        for (Integer length : needed.keySet()) {
            if (!rods.containsKey(length) || rods.get(length).size() < needed.get(length)) {
                return false;
            }
        }
        
        return true;
    }
    
    private Iterable<Integer> getSolution(int start) {
        assert 0 <= start && start <= 1;
        
        ArrayList<Integer> result = new ArrayList<Integer>();
        for (int i = 0; i < N; i++) {
            result.add(-1);
        }

        for (int i = start; i < N; i += 2) {
            int j = next(i);
            int k = next(j);
            int length = dist(i, j) + dist(j, k);
            result.set(j, rods.get(length).poll());
        }
        
        return result;
    }
    
    public P028A() {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        int m = sc.nextInt();
        for (int i = 0; i < N; i++) {
            int x = sc.nextInt();
            int y = sc.nextInt();
            nails.add(new Coord(x, y));
        }
        for (int i = 0; i < m; i++) {
            int length = sc.nextInt();
            if (!rods.containsKey(length)) {
                rods.put(length, new ArrayDeque<Integer>());
            }
            rods.get(length).add(i+1);
        }
   
        boolean solved = false;
        for (int i = 0; i < 2; i++) {
            if (checkPossible(i)) {
                System.out.println("YES");
                for (int rod : getSolution(i)) {
                    System.out.printf("%d ", rod);
                }
                System.out.println();
                solved = true;
                break;
            }
        }
        
        if (!solved) {
            System.out.println("NO");
        }
    }
    
    public static void main(String[] args) {
        P028A solution = new P028A();
    }
}       