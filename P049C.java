import java.util.*;

public class P049C {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] a = new int[n];
        if (n % 2 == 0) {
            a[0]   = n;
            a[n-1] = 1;
            for (int i = 1; i < n-2; i++) {
                a[i] = i + 2;
            }
            a[n-2] = 2;
        } else {
            a[n-1] = 2;
            a[0]   = 1;
            for (int i = 1; i < n-1; i++) {
                a[i] = i + 2;
            }
        }
        for (int x: a) {
            System.out.printf("%d ", x);
        }
        System.out.println();
    }
}