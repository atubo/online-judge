import java.util.*;

public class P407B {
    // dp(i) is the number of jumps need to return to node i
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        final int N = sc.nextInt();
        final int MOD = 1000000007;
        
        int[] p = new int[N];
        for (int i = 0; i < N; i++) {
            p[i] = sc.nextInt() - 1;
        }
        
        int[] dp = new int[N];
        for (int i = 0; i < N; i++) {
            dp[i] = i - p[i] + 1;
            for (int j = p[i]; j < i; j++) {
                dp[i] = (dp[i] + dp[j]) % MOD;
            }
        }
        
        int result = N;
        for (int i = 0; i < N; i++) {
            result = (result + dp[i]) % MOD;
        }
        
        System.out.println(result);
    }
}
        
        