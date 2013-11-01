import java.util.*;

public class P034E {
    private static class Ball {
        private double x;
        private double v;
        private double m;
        private int id;
        private double t = 0;    // last time x updated
        private double tLastCollision = 0;
        
        public Ball(double x, double v, double m, int id) {
            this.x = x;
            this.v = v;
            this.m = m;
            this.id = id;
        }
        
        public void updatePosition(double t1) {
            assert t <= t1;
            x += v * (t1 - t);
            t = t1;
        }
        
        public void recordCollision(double t1) {
            assert tLastCollision < t1;
            tLastCollision = t1;
        }
        
        public String toString() {
            //return "Ball " + id + " x = " + x + " v = " + v + " t = " + t;
            return String.format("Ball %d: x = %.2f v = %.2f t = %.2f\n", id, x, v, t);
        }
    }
    
    private static class Event implements Comparable<Event> {
        private int i;     // ball i will collide with ball i+1
        private double t;  // at time t
        private double t0; // the time it is calculated
        
        public Event(int i, double t, double t0) {
            this.i  = i;
            this.t  = t;
            this.t0 = t0;
        }
        
        public int compareTo(Event other) {
            return Double.compare(t, other.t);
        }
    }
    
    private Ball[] balls;
    private double currTime;
    private final double stopTime;
    private final int N;
    private PriorityQueue<Event> eventQueue = new PriorityQueue<Event>();
    
    private static final double MAXTIME = 10000;
    
    private void checkCandidate(int i) {
        if (i < 0 || i >= N-1) return;
        double t = currTime + timeToNextCollision(i);

        if (t < stopTime) {
            eventQueue.add(new Event(i, t, currTime));
        }
    }
    
    private void init() {
        for (int i = 0; i < N - 1; i++) {
            checkCandidate(i);
        }
    }
    
    private void process() {
        while (!eventQueue.isEmpty()) {
            Event event = eventQueue.poll();
            assert event.t > currTime;
            
            int i = event.i;
            assert i < N - 1;
            if (event.t0 < balls[i].tLastCollision ||
                event.t0 < balls[i+1].tLastCollision) {
                continue;
            }
            
            currTime = event.t;
            
            collide(i);
            
            checkCandidate(i-1);
            checkCandidate(i+1);               
        }
        
        for (int i = 0; i < N; i++) {
            balls[i].updatePosition(stopTime);
        }
    }   
   
    
    // ball i collide with ball i+1
    private void collide(int i) {
        int j = i + 1;
        assert balls[j].v < balls[i].v;
        
        balls[i].updatePosition(currTime);
        balls[j].updatePosition(currTime);
        balls[i].recordCollision(currTime);
        balls[j].recordCollision(currTime);
        
        double m1 = balls[i].m;
        double v1 = balls[i].v;
        
        double m2 = balls[j].m;
        double v2 = balls[j].v;
        
        double v1p = ((m1-m2)*v1 + 2*m2*v2)/(m1+m2);
        double v2p = ((m2-m1)*v2 + 2*m1*v1)/(m1+m2);
        
        balls[i].v = v1p;
        balls[j].v = v2p;
    }
    
    // time to next collision between ball i and ball i+1
    private double timeToNextCollision(int i) {
        if (i == N-1) return MAXTIME;
        
        int j = i + 1;
        
        balls[i].updatePosition(currTime);
        balls[j].updatePosition(currTime);
        
        double x1 = balls[i].x;
        double v1 = balls[i].v;
        
        double x2 = balls[j].x;
        double v2 = balls[j].v;
        
        assert x1 < x2;
        
        if (v2 >= v1) return MAXTIME;
        
        return (x2 - x1) / (v1 - v2);
    }
    
    public P034E() {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        stopTime = sc.nextInt();
        currTime = 0;
        
        balls = new Ball[N];
        for (int i = 0; i < N; i++) {
            int x = sc.nextInt();
            int v = sc.nextInt();
            int m = sc.nextInt();
            balls[i] = new Ball(x, v, m, i);
        }
        
        Arrays.sort(balls, new Comparator<Ball>() {
            public int compare(Ball b1, Ball b2) {
                return Double.compare(b1.x, b2.x);
            }
        });
        
        init();
        process();
        
        double[] result = new double[N];
        for (int i = 0; i < N; i++) {
            result[balls[i].id] = balls[i].x;
        }
        
        for (int i = 0; i < N; i++) {
            System.out.printf("%.8f\n", result[i]);
        }
    }
    
    public static void main(String[] args) {
        P034E solution = new P034E();
    }
}
        