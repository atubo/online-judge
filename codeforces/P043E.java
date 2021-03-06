import java.util.*;

public class P043E {
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
        
    private static class Car {
        private int v;
        private int x;
        private final int id;
        
        public Car(int v, int id) {
            this.v  = v;
            this.x  = 0;
            this.id = id;
        }
    }
    
    private static class Event implements Comparable<Event> {
        private int carId;
        private int v;
        
        public Event(int carId, int v) {
            this.carId = carId;
            this.v     = v;
        }
        
        public int compareTo(Event other) {
            if (carId < other.carId) return -1;
            if (carId > other.carId) return 1;
            if (v < other.v) return -1;
            if (v > other.v) return 1;
            return 0;
        }
    }
    
    private static int intComp(int i, int j) {
        if (i < j) return -1;
        if (i > j) return 1;
        return 0;
    }
    
    private class SortBySpeed implements Comparator<Integer> {             
        public int compare(Integer i, Integer j) {
            int cmp1 = -intComp(cars[i].v, cars[j].v);
            if (cmp1 != 0) return cmp1;
            return intComp(cars[i].id, cars[j].id);
        }
        
    }
    
    private class SortByPosition implements Comparator<Integer> {
        
        public int compare(Integer i, Integer j) {
            int cmp1 = -intComp(cars[i].x, cars[j].x);
            if (cmp1 != 0) return cmp1;
            return intComp(prevPos.get(i), prevPos.get(j));
        }
    }
    
    
    private final int N;
    private int prevT = 0;
    private int currT = 0;
    private TreeMap<Integer, TreeSet<Event>> queue = new TreeMap<Integer, TreeSet<Event>>();
    private HashMap<Integer, Integer> prevPos = new HashMap<Integer, Integer>();
    private Car[] cars;
    
    public P043E() {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        int s = sc.nextInt();
        
        cars = new Car[N];
        for (int i = 0; i < N; i++) {
            int k = sc.nextInt();
            int v = sc.nextInt();
            int t = sc.nextInt();
            cars[i] = new Car(v, i);
            for (int j = 1; j < k; j++) {
                v = sc.nextInt();
                if (!queue.containsKey(t)) {
                    queue.put(t, new TreeSet<Event>());
                }
                queue.get(t).add(new Event(i, v));
                t += sc.nextInt();
            }
            if (!queue.containsKey(t)) {
                queue.put(t, new TreeSet<Event>());
            }
            queue.get(t).add(new Event(i, 0));
        }
        
        System.out.println(process());
    }
    
    private void updatePosition() {
        for (int i = 0; i < N; i++) {
            cars[i].x += cars[i].v * (currT - prevT);
        }
    }
    
    private void updateSpeed() {
        Map.Entry<Integer, TreeSet<Event>> entry = queue.pollFirstEntry();
        TreeSet<Event> events = entry.getValue();
        for (Event e: events) {
            cars[e.carId].v = e.v;
        }
    }
    
    private int calcNumOfPasses(ArrayList<Integer> prevRank,
                                ArrayList<Integer> currRank) {
        int result = 0;
        BIT bit = new BIT(N);
        for (int i = 0; i < N; i++) {
            int pos = prevPos.get(currRank.get(i));  // previous position in the rank
            if (pos > 0) {
                result += Math.max(0, pos - bit.get(pos));  // how many it passed
            }
            bit.set(pos+1, 1);
        }
        
        return result;
    }
    
    private int process() {
        ArrayList<Integer> prevRank = new ArrayList<Integer>();
        ArrayList<Integer> currRank = new ArrayList<Integer>();
        for (int i = 0; i < N; i++) {
            prevRank.add(i);
            currRank.add(i);
        }
        
        Collections.sort(currRank, this.new SortBySpeed());
        int numOfPasses = 0;
        while (!queue.isEmpty()) {
            prevT = currT;
            currT = queue.firstKey();
            updatePosition();
            updateSpeed();
            
            ArrayList<Integer> tmp = prevRank;
            prevRank = currRank;
            currRank = tmp;
            
            for (int i = 0; i < prevRank.size(); i++) {
                prevPos.put(prevRank.get(i), i);
            }
            Collections.sort(currRank, this.new SortByPosition());
            
            numOfPasses += calcNumOfPasses(prevRank, currRank);
        }
        
        return numOfPasses;
    }
    
    public static void main(String[] args) {
        P043E solution = new P043E();
    }
}
        
        