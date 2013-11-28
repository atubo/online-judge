import java.util.*;

public class P044B {
    private static int f1(int a, int x) {
        if (a < x) return 0;
        return (a-x)/2 + 1;
    }
    
    private static int f2(int a, int b, int n) {
        int ap = Math.min(a, n);
        int x  = Math.max(n-2*b, n%2);
        
        return f1(ap, x);
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt() * 2;
        int a = sc.nextInt();
        int b = sc.nextInt();
        int c = sc.nextInt();
        int result = 0;
        for (int i = 0; i <= c; i++) {
            int np = n - i*4;
            if (np < 0) break;
            result += f2(a, b, np);
        }
        System.out.println(result);
    }
}