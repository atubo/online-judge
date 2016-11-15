import java.util.*;

public class P043D {
    private static void solveOneLine(int m, boolean switched) {
        if (m > 2) {
            System.out.println(1);
            if (switched) {
                System.out.printf("%d %d %d %d\n", m, 1, 1, 1);
            } else {
                System.out.printf("%d %d %d %d\n", 1, m, 1, 1);
            }
        } else {
            System.out.println(0);
        }
        for (int i = 1; i <= m; i++) {
            print(1, i, switched);
        }
        print(1, 1, switched);
    }
    
    private static void solveEven(int n, int m, boolean switched) {
        System.out.println(0);
        for (int i = 1; i <= m; i++) {
            print(1, i, switched);
        }
        for (int j = 2; j <= n-1; j++) {
            boolean evenRow = (j % 2 == 0);
            int start = (evenRow ? m : 2);
            int end   = (evenRow ? 1 : m+1);
            int step  = (evenRow ? -1: 1);
            for (int i = start; i != end; i += step) {
                print(j, i, switched);
            }
        }
        for (int i = m; i >= 1; i--) {
            print(n, i, switched);
        }
        for (int j = n-1; j >= 1; j--) {
            print(j, 1, switched);
        }
    }
    
    private static void print(int i, int j, boolean switched) {
        if (switched) {
            System.out.printf("%d %d\n", j, i);
        } else {
            System.out.printf("%d %d\n", i, j);
        }
    }
    
    private static void solveOdd(int n, int m) {
        System.out.println(1);
        System.out.printf("%d %d %d %d\n", n, m, 1, 1);
        for (int j = 1; j <= n; j++) {
            boolean evenRow = (j % 2 == 0);
            int start = (evenRow ? m : 1);
            int end   = (evenRow ? 0 : m+1);
            int step  = (evenRow ? -1: 1);
            for (int i = start; i != end; i += step) {
                print(j, i, false);
            }
        }
        print(1, 1, false);
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        if (n == 1) {
            solveOneLine(m, false);
        } else if (m == 1) {
            solveOneLine(n, true);
        } else if (n % 2 == 0) {
            solveEven(n, m, false);
        } else if (m % 2 == 0) {
            solveEven(m, n, true);
        } else {
            solveOdd(n, m);
        }
    }
}
            