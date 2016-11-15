import java.util.*;

public class P386C {
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
    
    private BIT[] letterCount = new BIT[26];
    private long[][] dp;
    private int[] prev;
    private int divMax;
    private final int N;
    
    private int letterInRange(int letter, int i, int j) {
        if (i == 0) {
            return letterCount[letter].get(j+1);
        } else {
            return letterCount[letter].get(j+1) - letterCount[letter].get(i);
        }
    }
    
    // get diversity in range [i, j] inclusive
    private int divInRange(int i, int j) {
        int result = 0;
        for (int letter = 0; letter < 26; letter++) {
            result += (letterInRange(letter, i, j) > 0 ? 1 : 0);
        }
        return result;
    }
    
    private void process(int pos) {
        int prevPos = prev[pos];
        int div = divInRange(prevPos+1, pos-1);
        for (int d = 1; d <= div + 1; d++) {
            dp[pos][d] = dp[pos-1][d-1];
        }
        for (int d = div + 1; d <= divMax; d++) {
            dp[pos][d] += dp[pos-1][d];
        }
    }
    
    public P386C() {
        Scanner sc = new Scanner(System.in);
        String s = sc.next();
        N = s.length();
        
        for (int i = 0; i < 26; i++) {
            letterCount[i] = new BIT(N);
        }
        
        dp = new long[N][];
        prev = new int[N];
        
        int[] last = new int[26];
        for (int i = 0; i < 26; i++) {
            last[i] = -1;
        }
        
        for (int i = 0; i < N; i++) {
            int c = s.charAt(i) - 'a';
            prev[i] = last[c];
            last[c] = i;
            letterCount[c].set(i+1, 1);
        }
        
        divMax = 0;
        for (int i = 0; i < 26; i++) {
            if (last[i] >= 0) divMax++;
        }
        
        System.out.println(divMax);
        
        for (int i = 0; i < N; i++) {
            dp[i] = new long[divMax+1];
            dp[i][0] = 1;
        }
        dp[0][1] = 1;
        
        for (int i = 1; i < N; i++) {
            process(i);
        }
        
        for (int d = 1; d <= divMax; d++) {
            long result = 0;
            for (int i = 0; i < N; i++) {
                result += dp[i][d];
            }
            System.out.println(result);
        }
    }
    
    public static void main(String[] args) {
        P386C solution = new P386C();
    }
}
