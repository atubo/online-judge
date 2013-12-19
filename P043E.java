import java.util.*;

public class P043E {
    private static class Event implements Comparable<Event> {
        private final int type;  // 0 - velocity change, 1 - pass
        private final double occurTime;
        private final double addedTime;
        // for velocity change event, car2 is null,
        // for passing event, car1 takes over car2 by convention
        private final Car car1;
        private final Car car2;
        // for type 0, v1 = new speed, v2 = 0
        // for type 1, v1(2) = speed of car1(2)
        private final int v1;
        private final int v2;
        
        public Event(int type, double occurTime, double addedTime, Car car1, Car car2,
                     int v1, int v2) {
            this.type      = type;
            this.occurTime = occurTime;
            this.addedTime = addedTime;
            this.car1      = car1;
            this.car2      = car2;
            this.v1        = v1;
            this.v2        = v2;
        }
        
        public int compareTo(Event other) {
            if (occurTime < other.occurTime) return -1;
            if (occurTime > other.occurTime) return 1;
            if (type < other.type) return -1;
            if (type > other.type) return 1;
            if (addedTime < other.addedTime) return -1;
            if (addedTime > other.addedTime) return 1;
            if (car1.getId() < other.car1.getId()) return -1;
            if (car1.getId() > other.car1.getId()) return 1;
            if (car2 != null) {
                if (car2.getId() < other.car2.getId()) return -1;
                if (car2.getId() > other.car2.getId()) return 1;
            }
            if (v1 < other.v1) return -1;
            if (v1 > other.v1) return 1;
            if (v2 < other.v2) return -1;
            if (v2 > other.v2) return 1;
            return 0;
        }
        
        public String toString() {
            if (type == 0) {
                return String.format("#%d Speed change @%f: new speed = %d", car1.id, occurTime, v1);
            } else {
                return String.format("#%d pass #%d @%f, addtime=%f, v1=%d v2=%d",
                                     car1.id, car2.id, occurTime, addedTime, v1, v2);
            }
        }
    }
    
    private static class Car {
        private final int id;
        private int v;
        private double x;
        private int lastUpdateTime;
        private int rank;
        
        public Car(int id, int v) {
            this.id = id;
            this.v  = v;
            this.x  = 0;
            this.lastUpdateTime = 0;
            this.rank = -1;
        }
        
        public int getId() {
            return id;
        }
    }
    
    private TreeSet<Event> queue = new TreeSet<Event>();
    private double currTime = 0;
    private final int trackLength;
    private ArrayList<Car> standing = new ArrayList<Car>();
    int numPasses = 0;
    
    public P043E() {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        trackLength = sc.nextInt();
        for (int i = 0; i < N; i++) {
            int k = sc.nextInt();
            int v = sc.nextInt();
            int t = sc.nextInt();
            Car car = new Car(i, v);
            standing.add(car);
            int prev_v = v;
            int curr_t = t;
            for (int j = 1; j < k; j++) {
                v = sc.nextInt();
                t = sc.nextInt();
                if (v != prev_v) {
                    queue.add(new Event(0, curr_t, 0, car, null, v, 0));
                    prev_v = v;
                }
                curr_t += t;
            }
        }
        // add two "dummy" cars
        standing.add(new Car(N, 0));
        standing.add(new Car(N + 1, 1001));
        
        Collections.sort(standing, new Comparator<Car>() {
            public int compare(Car car1, Car car2) {
                if (car1.v > car2.v) return -1;
                if (car1.v < car2.v) return 1;
                if (car1.id < car2.id) return -1;
                if (car1.id > car2.id) return 1;
                return 0;
            }
        });
        for (int i = 0; i < standing.size(); i++) {
            Car car = standing.get(i);
            car.rank = i;
        }
    }
    
    public void solve() {
        process();
        System.out.println(numPasses);
    }
    
    private void process() {
        while (!queue.isEmpty()) {
            Event e = queue.pollFirst();
            assert currTime <= e.occurTime;
            currTime = Math.max(currTime, e.occurTime);
            
            if (e.type == 0) {
                processVelocityChange(e);
            } else {
                processPass(e);
            }
        }
    }
                     
    private double passTime(Car car1, Car car2) {
        double x1 = car1.x;
        double x2 = car2.x;
        int t1 = car1.lastUpdateTime;
        int t2 = car2.lastUpdateTime;
        int v1 = car1.v;
        int v2 = car2.v;
        
        double t = ((x2 - x1) + (currTime - t2) * v2 - (currTime - t1) * v1) / (v1 - v2);

        assert t >= 0;
        return t;
    }
    
    private void checkPass(Car car1, Car car2) {
        if (car1.v <= car2.v) return;
        
        double t = passTime(car1, car2);
        queue.add(new Event(1, currTime + t, currTime, car1, car2, car1.v, car2.v));
    }
    
    private void checkFront(Car car1) {
        int i = car1.rank;
        Car car2 = standing.get(i-1);
        checkPass(car1, car2);
    }
    
    private void checkBack(Car car2) {
        int i = car2.rank;
        Car car1 = standing.get(i+1);
        checkPass(car1, car2);
    }
    
    private void processVelocityChange(Event e) {
        Car car = e.car1;
        double currPos = car.x + car.v * (e.occurTime - car.lastUpdateTime);
            
        int old_v = car.v;
        car.v = e.v1;
        car.x = currPos;
        car.lastUpdateTime = (int)e.occurTime;
        
        checkFront(car);
        checkBack(car);
    }
    
    private boolean isValid(Event e) {
        assert e.type == 1;
        Car car1 = e.car1;
        Car car2 = e.car2;
        
        double ta = e.addedTime;
        if (ta < car1.lastUpdateTime || ta < car2.lastUpdateTime) return false;
        if (e.v1 != car1.v || e.v2 != car2.v) return false;
        
        return true;
    }
    
    private void removeCar(Car car) {
        int rank = car.rank;
        standing.remove(rank);
        for (int i = rank; i < standing.size(); i++) {
            assert standing.get(i).rank == i + 1;
            standing.get(i).rank = i;
        }
    }
    
    private void swapRank(Car car1, Car car2) {
        assert car1.rank - 1 == car2.rank;
        car1.rank--;
        car2.rank++;
        standing.set(car1.rank, car1);
        standing.set(car2.rank, car2);
    }
    
    private void processPass(Event e) {
        Car car1 = e.car1;
        Car car2 = e.car2;
        assert car1.rank - 1 == car2.rank;
        
        if (!isValid(e)) return;
        
        double currPos = car1.x + car1.v * (e.occurTime - car1.lastUpdateTime);
        if (currPos >= trackLength) {
            removeCar(car1);
            removeCar(car2);
            return;
        }
        
        numPasses++;
        swapRank(car1, car2);
        checkFront(car1);
        checkBack(car2);
    }
    
    public static void main(String[] args) {
        P043E solution = new P043E();
        solution.solve();
    }
}     
            