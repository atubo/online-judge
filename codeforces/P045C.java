import java.util.*;

public class P045C {
    private static class Pair implements Comparable<Pair> {
        private int left;
        private int right;
        private int skillDiff;
        
        public Pair(int left, int right, int skillDiff) {
            this.left      = left;
            this.right     = right;
            this.skillDiff = skillDiff;
        }
        
        public int compareTo(Pair other) {
            if (skillDiff < other.skillDiff) return -1;
            if (skillDiff > other.skillDiff) return 1;
            return left - other.left;
        }
    }
        
    private int[] skill;
    private char[] gender;
    private boolean[] out;
    private int[] prev;
    private int[] next;
    private PriorityQueue<Pair> queue = new PriorityQueue<Pair>();
    
    private int calcSkillDiff(int i, int j) {
        return Math.abs(skill[i] - skill[j]);
    }
    
    private void processPair(Pair pair) {
        int l = pair.left;
        int r = pair.right;
        if (out[l] || out[r]) return;
        if (prev[l] != l && next[r] != r) {
            next[prev[l]] = next[r];
            prev[next[r]] = prev[l];
            int l2 = prev[l];
            int r2 = next[r];
            if (gender[l2] != gender[r2]) {
                queue.add(new Pair(l2, r2, calcSkillDiff(l2, r2)));
            }
        } else if (next[r] != r) {
            prev[next[r]] = next[r];
        } else if (prev[l] != l) {
            next[prev[l]] = prev[l];
        }
        System.out.printf("%d %d\n", l+1, r+1);
        out[l] = out[r] = true;
    }
    
    private void solve() {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        skill  = new int[n];
        gender = new char[n];
        out    = new boolean[n];
        prev   = new int[n];
        next   = new int[n];
        
        prev[0] = 0;
        next[0] = 1;
        prev[n-1] = n-2;
        next[n-1] = n-1;
        
        for (int i = 1; i <= n-2; i++) {
            prev[i] = i-1;
            next[i] = i+1;
        }
        
        String s = sc.next();
        int numBoy = 0;
        for (int i = 0; i < n; i++) {
            gender[i] = s.charAt(i);
            if (gender[i] == 'B') numBoy++;
        }
        
        for (int i = 0; i < n; i++) {
            skill[i] = sc.nextInt();
        }
        
        System.out.println(Math.min(numBoy, n-numBoy));
        
        for (int i = 0; i < n-1; i++) {
            if (gender[i] != gender[i+1]) {
                queue.add(new Pair(i, i+1, calcSkillDiff(i, i+1)));
            }
        }
        
        while(!queue.isEmpty()) {
            Pair pair = queue.poll();
            processPair(pair);
        }
    }
    
    public static void main(String[] args) {
        P045C solution = new P045C();
        solution.solve();
    }
}
        