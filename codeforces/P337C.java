import java.util.*;

public class P337C {
    // a ^ b mod n
    private static int modExp(int a, int b, int n) {
        long c = 0;
        long d = 1;
        ArrayList<Integer> bRep = new ArrayList<Integer>();
        int bp = b;
        while (bp > 0) {
            bRep.add(bp & 1);
            bp = bp >> 1;
        }
        for (int i = bRep.size() - 1; i >= 0; i--) {
            c *= 2;
            d = (d * d) % n;
            if (bRep.get(i) == 1) {
                c += 1;
                d = (d * a) % n;
            }
        }
        
        return (int)d;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        int k = sc.nextInt();
        
        int nDouble = Math.max(0, n/k - (n - m));
        
        final int MOD = 1000000009;
        
        long a = (long)modExp(2, nDouble + 1, MOD);

        a = (((a + MOD - 2) % MOD) * k) % MOD;
        a = (a + m - nDouble * k) % MOD;
        
        System.out.println(a);
    }
}
        