import java.util.*;

public class P067B {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        final int N = sc.nextInt();
        final int K = sc.nextInt();
        int[] b = new int[N];
        for (int i = 0; i < N; i++) {
            b[i] = sc.nextInt();
        }
        
        for (int i = 0; i < N; i++) {
            int pos = 0;
            for (; pos < N; pos++) {
                if (b[pos] == 0) break;
            }
            System.out.printf("%d ", pos + 1);
            b[pos] = -1;
            for (int j = pos - K; j >= 0; j--) {
                b[j]--;
            }
        }
        System.out.println();
    }
}