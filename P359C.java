import java.util.*;

public class P359C {
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
        int N = sc.nextInt();
        int x = sc.nextInt();
        long[] a  = new long[N];
        long[] ap = new long[N];
        long aSum = 0;
        for (int i = 0; i < N; i++) {
            a[i] = sc.nextInt();
            aSum += a[i];
        }
        for (int i = 0; i < N; i++) {
            ap[i] = aSum - a[i];
        }
        Arrays.sort(ap);
        TreeMap<Long, Integer> digits = new TreeMap<Long, Integer>();
        for (long p: ap) {
            if (!digits.containsKey(p)) {
                digits.put(p, 0);
            }
            int d = digits.get(p);
            assert d < x;
            if (d == x - 1) {
                long q = p;
                while (digits.containsKey(q) && digits.get(q) == x - 1) {
                    digits.remove(q++);
                }
                if (!digits.containsKey(q)) {
                    digits.put(q, 0);
                }
                digits.put(q, digits.get(q) + 1);
            } else {
                digits.put(p, d + 1);
            }
        }
        
        long y = digits.firstKey();
        
        final int MVAL = 1000000007;
        
        int result = 0;
        
        if (x % MVAL == 0) {
            result = (Math.min(y, aSum) == 0 ? 1 : 0);
        } else {
            int xp = x % MVAL;
            int yp;
            if (y >= aSum) {
                yp = (int)(aSum % (MVAL - 1));
            } else {
                yp = (int)(y % (MVAL - 1));
            }
            result = modExp(xp, yp, MVAL);
        }
        
        System.out.println(result);
    }
}
