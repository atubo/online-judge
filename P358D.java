import java.util.*;

public class P358D {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int[] a = new int[N];
        int[] b = new int[N];
        int[] c = new int[N];
        for (int i = 0; i < N; i++) {
            a[i] = sc.nextInt();
        }
        for (int i = 0; i < N; i++) {
            b[i] = sc.nextInt();
        }
        for (int i = 0; i < N; i++) {
            c[i] = sc.nextInt();
        }
        int[] dpFirst = new int[N];  // if the last hare is the first to be fed
        int[] dpLast  = new int[N];
        dpFirst[0] = dpLast[0] = a[0];
        
        for (int i = 1; i < N; i++) {
            if (i == 1) {
                dpFirst[i] = a[i] + dpFirst[i-1] + b[i-1] - a[i-1];
            } else {
                dpFirst[i] = a[i] + Math.max(dpFirst[i-1] + b[i-1] - a[i-1],
                                             dpLast[i-1] + c[i-1] - b[i-1]);
            }
            dpLast[i] = b[i] + Math.max(dpFirst[i-1], dpLast[i-1]);
        }
        
        System.out.println(Math.max(dpFirst[N-1], dpLast[N-1]));
    }
}