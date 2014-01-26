import java.util.*;

public class P076E {
    private static long getSumSquare(int[] x) {
        long sum    = x[0];
        long sumSq  = x[0] * x[0];
        long result = 0;
        for (int i = 1; i < x.length; i++) {
            result += ((long) i) * x[i] * x[i] - ((long) 2) * x[i] * sum + sumSq;
            sum += x[i];
            sumSq += x[i] * x[i];
        }
        return result;
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        final int N = sc.nextInt();
        int[] x = new int[N];
        int[] y = new int[N];
        for (int i = 0; i < N; i++) {
            x[i] = sc.nextInt();
            y[i] = sc.nextInt();
        }
        System.out.println(getSumSquare(x) + getSumSquare(y));
    }
}