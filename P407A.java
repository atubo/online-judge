import java.util.*;

public class P407A {
    private static int sqrtInt(int x) {
        int y = (int)(Math.sqrt(x) + 0.5);
        if (y * y == x) return y;
        return -1;
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int a = sc.nextInt();
        int b = sc.nextInt();
        boolean found = false;
        for (int x1 = 1; x1 < a; x1++) {
            int y1 = sqrtInt(a*a - x1*x1);
            if (y1 == -1) continue;
            if ((b*b*x1*x1) % (x1*x1+y1*y1) != 0) continue;
            int y2 = sqrtInt((b*b*x1*x1)/(x1*x1+y1*y1));
            if (y2 == -1) continue;
            if (y1 == y2) continue;
            if (y1*y2 % x1 != 0) continue;
            int x2 = -y1*y2/x1;
            found = true;
            System.out.println("YES");
            System.out.printf("%d %d\n", 0, 0);
            System.out.printf("%d %d\n", x1, y1);
            System.out.printf("%d %d\n", x2, y2);
            break;
        }
        if (!found) {
            System.out.println("NO");
        }
    }
}
        