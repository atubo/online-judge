import java.util.*;

public class P055B {
    private long solve(long[] a, char[] op) {
        assert a.length == op.length + 1;
        if (op.length == 1) {
            return eval(a[0], a[1], op[0]);
        }
        long minVal = Long.MAX_VALUE;
        int N = a.length;
        for (int i = 0; i < N-1; i++) {
            for (int j = i+1; j < N; j++) {
                long result = eval(a[i], a[j], op[0]);
                // construct a and op array for recursive call
                long[] ap = new long[N-1];
                char[] opp = new char[N-2];
                for (int k = 0; k < N-2; k++) {
                    opp[k] = op[k+1];
                }
                ap[0] = result;
                int k = 1;
                for (int m = 0; m < N; m++) {
                    if (m != i && m != j) ap[k++] = a[m];
                }
                minVal = Math.min(minVal, solve(ap, opp));
            }
        }
        
        return minVal;
    }
    
    private long eval(long a, long b, char op) {
        switch (op) {
            case '+':
                return a + b;
            case '*':
                return a * b;
            default:
                assert false;
        }
        return 0;
    }
    
    public P055B() {
        Scanner sc = new Scanner(System.in);
        long[] a = new long[4];
        for (int i = 0; i < 4; i++) {
            a[i] = sc.nextLong();
        }
        sc.nextLine();
        String s = sc.nextLine();
        char[] op = new char[3];
        assert s.length() == 5;
        for (int i = 0; i < 3; i++) {
            op[i] = s.charAt(2*i);
        }
        System.out.println(solve(a, op));
    }
    
    public static void main(String[] args) {
        P055B solution = new P055B();
    }
}
    
    