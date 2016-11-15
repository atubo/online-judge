import java.util.*;

public class P046C {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int[] a = new int[N];
        String s = sc.next();
        int L = 0;
        for (int i = 0; i < N; i++) {
            a[i] = (s.charAt(i) == 'H' ?  1 : 0);
            L += a[i];
        }
        
        int hnum = 0;
        for (int i = 0; i < L; i++) {
            hnum += a[i];
        }

        int hmax = hnum;
        for (int i = L; i < L + N - 1; i++) {
            int k1 = i % N;
            int k2 = (i + N - L) % N;
            hnum += a[k1];
            hnum -= a[k2];
            hmax = Math.max(hmax, hnum);
        }
        System.out.println(L - hmax);
    }
}