import java.util.*;

public class P047D {
    private static class Attempt implements Comparable<Attempt> {
        long s;
        int c;
        
        public Attempt(long s, int c) {
            this.s = s;
            this.c = c;
        }
        
        public int compareTo(Attempt other) {
            return this.c - other.c;
        }
    }
    
    private int n;
    private int m;
    private Attempt[] attemps;
    private int result;
    
    private int getMatchDigits(long target, long guess) {
        long mask = ~(((~((1 << n) - 1)) | guess) ^ target);
        int result = 0;
        while (mask != 0) {
            mask = mask & (mask-1);
            result++;
        }

        return result;
    }
    
    private boolean isMatch(long target, Attempt attempt) {
        return getMatchDigits(target, attempt.s) == attempt.c;
    }
    
    private boolean verify(ArrayList<Integer> pos) {
        long mask = (1 << n) - 1;
        for (int i = 0; i < pos.size(); i++) {
            mask = mask & (~ (1 << pos.get(i)));
        }
        long target = attemps[0].s ^ mask;
        
        for (int i = 1; i < m; i++) {
            if (!isMatch(target, attemps[i])) {
                return false;
            }
        }
        
        return true;
    }
    
    private void doTrial(ArrayList<Integer> pos, int depth, int maxDepth) {
        assert pos.size() == depth;

        if (depth == maxDepth) {
            if (verify(pos)) {
                result++;
            }
            return;
        }
        int start = (pos.isEmpty() ? 0 : pos.get(pos.size()-1) + 1);
        for (int i = start; i < n; i++) {
            pos.add(i);
            doTrial(pos, depth + 1, maxDepth);
            pos.remove(pos.size()-1);
        }
    }
  
    private void solve() {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        m = sc.nextInt();
        
        attemps = new Attempt[m];
        
        for (int i = 0; i < m; i++) {
            String sstr = sc.next();
            long s = Long.parseLong(sstr, 2);
            int c = sc.nextInt();
            attemps[i] = new Attempt(s, c);
        }
        
        Arrays.sort(attemps);
        
        ArrayList<Integer> pos = new ArrayList<Integer>();
        doTrial(pos, 0, attemps[0].c);
        
        System.out.println(result);
    }
    
    public static void main(String[] args) {
        P047D solution = new P047D();
        solution.solve();
    }
}