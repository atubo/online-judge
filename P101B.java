import java.util.*;
import java.io.*;

public class P101B {
    public static class Bus {
        private int id;
        private int s;
        private int t;
        public Bus(int id, int s, int t) {
            this.id = id;
            this.s = s;
            this.t = t;
        }
    }
    
    public static class EndPoint implements Comparable<EndPoint> {
        private int pos;
        private int type;  // 0 - left, 1 - right
        private int id;    // bus id
        public EndPoint(int pos, int type, int id) {
            this.pos  = pos;
            this.type = type;
            this.id   = id;
        }
        
        public int compareTo(EndPoint other) {
            if (type > other.type) return -1;
            if (type < other.type) return 1;
            return Integer.compare(id, other.id);
        }
    }
    
    /** Class for buffered reading int and double values */
    private static class Reader {
        static BufferedReader reader;
        static StringTokenizer tokenizer;
        
        /** call this method to initialize reader for InputStream */
        static void init(InputStream input) {
            reader = new BufferedReader(
                                        new InputStreamReader(input) );
            tokenizer = new StringTokenizer("");
        }
        
        /** get next word */
        static String next() throws IOException {
            while ( ! tokenizer.hasMoreTokens() ) {
                //TODO add check for eof if necessary
                tokenizer = new StringTokenizer(
                                                reader.readLine() );
            }
            return tokenizer.nextToken();
        }
        
        static int nextInt() throws IOException {
            return Integer.parseInt( next() );
        }
        
        static double nextDouble() throws IOException {
            return Double.parseDouble( next() );
        }
    }

    
    private int N;
    private final int M;
    private Bus[] buses;
    private int[] count;
    private final int MOD = 1000000007;
    private int total = 0;
    private ArrayList<TreeSet<EndPoint>> stops = new ArrayList<>();
    
    public void processStop(TreeSet<EndPoint> eps) {
        int totalTmp = total;
        for (EndPoint ep: eps) {
            if (ep.type == 0) {
                total = (total + MOD - count[ep.pos]) % MOD;
            } else {
                int x = buses[ep.id].s;
                int incr = (ep.pos == N ? 1 : total);
                count[x] = (count[x] + incr) % MOD;
                totalTmp = (totalTmp + incr) % MOD;
            }
        }
        total = totalTmp;
    }
    
    private void remap() {
        TreeSet<Integer> pos = new TreeSet<>();
        for (Bus b: buses) {
            pos.add(b.s);
            pos.add(b.t);
        }
        if (pos.contains(N)) {
            N = pos.size() - 1;
        } else {
            N = pos.size();
        }
        
        int i = 0;
        TreeMap<Integer, Integer> posMap = new TreeMap<>();
        for (Integer p: pos) {
            posMap.put(p, i);
            i++;
        }
        
        for (Bus b: buses) {
            b.s = posMap.get(b.s);
            b.t = posMap.get(b.t);
        }
    }
    
    private void createStops() {
        for (int i = 0; i < N+1; i++) {
            stops.add(new TreeSet<EndPoint>());
        }
        
        for (int i = 0; i < M; i++) {
            Bus bus = buses[i];
            int s = bus.s;
            int t = bus.t;
            int id = bus.id;
            stops.get(s).add(new EndPoint(s, 0, id));
            stops.get(t).add(new EndPoint(t, 1, id));
        }
    }
    
    public P101B() throws IOException {
        Reader.init(System.in);
        N = Reader.nextInt();
        M = Reader.nextInt();
        buses = new Bus[M];
        
        for (int i = 0; i < M; i++) {
            int s = Reader.nextInt();
            int t = Reader.nextInt();
            buses[i] = new Bus(i, s, t);
        }
        
        remap();
        count = new int[N+1];
        
        createStops();
        
        for (int i = N; i >= 0; i--) {
            processStop(stops.get(i));
        }
        
        System.out.printf("%d\n", count[0]);
    }
    
    public static void main(String[] args) throws IOException {
        P101B solution = new P101B();
    }
}
            
                
        