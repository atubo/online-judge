import java.util.*;

public class P353D {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.next();
        int N = line.length();
        int[] dp = new int[N];
        int k;
        for (k = 0; k < N; k++) {
            if (line.charAt(k) == 'F') {
                dp[0] = k;
                break;
            }
        }
        if (k == N) {
            System.out.println(0);
            return;
        }
        int i = 1;
        for (k = dp[0] + 1; k < N; k++) {
            if (line.charAt(k) == 'F') {
                int l = k - i;
                dp[i] = Math.max(l, (dp[i-1] == 0 ? 0 : dp[i-1] + 1));
                i++;
            }
        }
        System.out.println(dp[i-1]);
    }
}