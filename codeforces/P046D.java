import java.util.*;

public class P046D {
    private static class Segment implements Comparable<Segment> {
        private final int x;
        private final int l;
        
        public Segment(int x, int l) {
            this.x = x;
            this.l = l;
        }
        
        @Override
        public int compareTo(Segment other) {
            if (x < other.x) return -1;
            if (x > other.x) return 1;
            return 0;
        }
    }
    
    private TreeSet<Segment> parkingLot = new TreeSet<Segment>();
    private HashMap<Integer, Segment> cars = new HashMap<Integer, Segment>();
    private final int L;
    private final int b;
    private final int f;
    
    private int park(int i, int length) {
        if (parkingLot.isEmpty()) {
            return -1;
        }
        
        Segment s1 = parkingLot.first();
        if (s1.x == 0 && s1.l == L) {
            if (length <= L) {
                cars.put(i, new Segment(0, length));
                parkingLot.remove(s1);
                if (L - length > 0) {
                    parkingLot.add(new Segment(length, L - length));
                }
                return 0;
            } else {
                return -1;
            }
        }
        
        if (s1.x == 0 && length + f <= s1.l) {
            cars.put(i, new Segment(0, length));
            parkingLot.remove(s1);
            parkingLot.add(new Segment(length, s1.l - length));
            return 0;
        }
        
        for (Segment s: parkingLot) {
            if (length + b + f <= s.l) {
                cars.put(i, new Segment(s.x + b, length));
                parkingLot.remove(s);
                parkingLot.add(new Segment(s.x, b));
                parkingLot.add(new Segment(s.x + b + length, s.l - b - length));
                return s.x + b;
            }
        }
        
        Segment sn = parkingLot.last();
        if (sn.x + sn.l == L && length + b <= sn.l) {
            cars.put(i, new Segment(sn.x + b, length));
            parkingLot.remove(sn);
            parkingLot.add(new Segment(sn.x, b));
            int ln = sn.l - length - b;
            if (ln > 0) {
                parkingLot.add(new Segment(sn.x + b + length, ln));
            }
            return sn.x + b;
        }
        
        return -1;
    }
    
    private void leave(int i) {
        Segment car = cars.get(i);
        cars.remove(i);
        if (car.x == 0 && car.l == L) {
            assert parkingLot.isEmpty();
            parkingLot.add(new Segment(0, L));
        } else if (car.x == 0) {
            Segment s = parkingLot.ceiling(car);
            parkingLot.remove(s);
            parkingLot.add(new Segment(0, car.l + s.l));
        } else if (car.x + car.l == L) {
            Segment s = parkingLot.floor(car);
            parkingLot.remove(s);
            parkingLot.add(new Segment(s.x, s.l + car.l));
        } else {
            Segment s1 = parkingLot.floor(car);
            Segment s2 = parkingLot.ceiling(car);
            parkingLot.remove(s1);
            parkingLot.remove(s2);
            parkingLot.add(new Segment(s1.x, s1.l + s2.l + car.l));
        }
    }
            
        
    
    public P046D() {
        Scanner sc = new Scanner(System.in);
        L = sc.nextInt();
        b = sc.nextInt();
        f = sc.nextInt();
        parkingLot.add(new Segment(0, L));
        
        int n = sc.nextInt();
        for (int i = 0; i < n; i++) {
            int rt = sc.nextInt();
            if (rt == 1) {
                int length = sc.nextInt();
                int pos = park(i, length);
                System.out.println(pos);
            } else {
                int carId = sc.nextInt();
                leave(carId-1);
            }
        }
    }
    
    public static void main(String[] args) {
        P046D solution = new P046D();
    }
}