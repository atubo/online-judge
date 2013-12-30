import java.util.*;

public class P337E {
    private static ArrayList<Integer> primes = new ArrayList<Integer>();
    
    private static void sieve() {
        final int N = 1000003;
        char[] bit = new char[N];
        for (int i = 2; i < N; i++) {
            bit[i] = 1;
        }
        for (int i = 2; i < N; i++) {
            if (bit[i] == 0) continue;
            int q = i;
            while (q + i < N) {
                q += i;
                bit[q] = 0;
            }
        }

        for (int i = 2; i < N; i++) {
            if (bit[i] == 1) {
                primes.add(i);
            }
        }

    }

    private static int getNumPrimes(long x) {
        int result = 0;

        for (int prime: primes) {
            while (x % prime == 0) {
                result++;
                x = x / prime;
            }
            if (x == 1) break;
        }
        
        if (x != 1) result++;
        
        return result;
    }
   
    private void checkDivisible(TreeSet<Integer> divisible,
                                TreeSet<Integer> selected,
                                int s, int i) {
        if (divisible.isEmpty()) {
            if (selected.isEmpty()) return;
            long x = a[i];
            for (int j: selected) {
                long fct = a[j];
                if (x % fct != 0) return;
                x = x / fct;
            }
            int nNodes = 1 + np[i] + dp[s];
            int sp = (1 << i) | s;
            for (int j: selected) {
                sp &= ~(1 << j);
                nNodes -= np[j];
            }
            dp[sp] = Math.min(dp[sp], nNodes);
            return;
        }
        
        int x = divisible.pollFirst();
        
        checkDivisible(divisible, selected, s, i);
        selected.add(x);
        checkDivisible(divisible, selected, s, i);
        selected.remove(x);
        divisible.add(x);
    }
        
            
    
    private final int N;
    private final long[] a;
    private final int[] np;
    private final int[] dp;
    
    public P337E() {
        sieve();
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        a = new long[N];
        for (int i = 0; i < N; i++) {
            a[i] = sc.nextLong();
        }
        Arrays.sort(a);
        np = new int[N];
        for (int i = 0; i < N; i++) {
            np[i] = getNumPrimes(a[i]);
        }
        
        final int M = 1 << N;
        dp = new int[M];
        
        for (int i = 0; i < M; i++) {
            dp[i] = Integer.MAX_VALUE;
        }
        
        dp[1] = (np[0] > 1 ? 1 + np[0] : 1);
        
        for (int i = 1; i < N; i++) {
            int NI = (1 << i);
            for (int s = (1 << i-1); s < NI; s++) {
                if (dp[s] != Integer.MAX_VALUE) {
                    dp[NI|s] = Math.min(dp[NI|s], (np[i] == 1 ? 1 : 1 + np[i]) + dp[s]);
                
                    // find all j in s such that ai|aj
                    TreeSet<Integer> divisible = new TreeSet<Integer>();
                    for (int j = 0; j < i; j++) {
                        if (((s & (1 << j)) != 0) && (a[i] % a[j] == 0)) {
                            divisible.add(j);
                        }
                    }
                    TreeSet<Integer> selected = new TreeSet<Integer>();
                    checkDivisible(divisible, selected, s, i);
                }
            }
        }
        
        int result = Integer.MAX_VALUE;
        for (int s = 1 << (N-1); s < M; s++) {
            result = Math.min(result, dp[s]);
        }
        
        if (dp[1 << (N-1)] != result) {
            result++;
        }
        
        System.out.println(result);
    }
    
    public static void main(String[] args) {
        P337E solution = new P337E();
    }
}

