import java.util.*;

public class P074D {
    static class Query {
        private final int type;  // 0 - director, 1 - employee
        private final int i;     // for 1-type it's id
        private final int j;     // for 1-type: 0 - departure, 1 - arrival
        
        public Query(int type, int i, int j) {
            this.type = type;
            this.i    = i;
            this.j    = j;
        }
    }
    
    static class Cloak implements Comparable<Cloak> {
        private final int id;
        private int pos;
        private int left;
        private int right;
        private int space;  // to the left neighbor
        
        public Cloak(int id) {
            this.id = id;
        }
        
        public int compareTo(Cloak other) {
            if (space > other.space) return -1;
            if (space < other.space) return 1;
            if (pos > other.pos) return -1;
            if (pos < other.pos) return 1;
            return 0;
        }
        
        public void setParam(int pos, int left, int right, int space) {
            this.pos   = pos;
            this.left  = left;
            this.right = right;
            this.space = space;
        }
    }
    
    private Cloak[] cloaks;
    private TreeSet<Integer> counter = new TreeSet<Integer>();
    private TreeSet<Cloak> hanger = new TreeSet<Cloak>();
    
    private void addCloak(int id) {
        // find new comer's right neighbor
        Cloak rn = hanger.pollFirst();
        Cloak ln = cloaks[rn.left];
        Cloak clk = cloaks[id];
        int pos = (rn.pos + ln.pos + 1) / 2;
        
        int s1 = pos - ln.pos;
        int s2 = rn.pos - pos;
        
        clk.setParam(pos, ln.id, rn.id, s1);
        ln.right = id;
        rn.left = id;
        rn.space = s2;
        
        hanger.add(clk);
        hanger.add(rn);
        
        counter.add(pos);
    }
    
    private void removeCloak(int id) {
        Cloak clk = cloaks[id];
        hanger.remove(clk);
        
        Cloak rn = cloaks[clk.right];
        Cloak ln = cloaks[clk.left];
        
        hanger.remove(rn);
        
        ln.right = rn.id;
        rn.left  = ln.id;
        
        rn.space = clk.space + rn.space;
        
        hanger.add(rn);
        
        counter.remove(clk.pos);
    }
    
    private int query(int i, int j) {
        return counter.subSet(i, j+1).size();
    }
    
    public P074D() {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int Q = sc.nextInt();
        
        // preprocess to map employee ID to internal id which is consecutive
        // also distinguish arrival and departure
        Query[] queries = new Query[Q];
        HashMap<Integer, Integer> numEmpAppr = new HashMap<Integer, Integer>();
        HashMap<Integer, Integer> empIdMap = new HashMap<Integer, Integer>();
        for (int k = 0; k < Q; k++) {
            int x = sc.nextInt();
            if (x == 0) {
                int i = sc.nextInt();
                int j = sc.nextInt();
                queries[k] = new Query(0, i, j);
            } else {
                if (!numEmpAppr.containsKey(x)) {
                    int id = empIdMap.size() + 1;
                    empIdMap.put(x, id);
                    numEmpAppr.put(x, 0);
                }
                numEmpAppr.put(x, numEmpAppr.get(x) + 1);
                queries[k] = new Query(1, empIdMap.get(x),
                                       numEmpAppr.get(x) % 2);
            }
        }
        
        int M = empIdMap.size();
        cloaks = new Cloak[M+2];
        for (int i = 0; i < M + 2; i++) {
            cloaks[i] = new Cloak(i);
        }
        cloaks[0].setParam(0, 0, M + 1, 0);
        cloaks[M+1].setParam(N + 1, 0, M + 1, N + 1);
        
        hanger.add(cloaks[0]);
        hanger.add(cloaks[M+1]);
        
        for (int k = 0; k < Q; k++) {
            Query q = queries[k];
            if (q.type == 0) {
                System.out.printf("%d\n", query(q.i, q.j));
            } else {
                if (q.j == 1) {
                    addCloak(q.i);
                } else {
                    removeCloak(q.i);
                }
            }
        }  
    }
    
    public static void main(String[] args) {
        P074D solution = new P074D();
    }
}
        
        
        
    
    