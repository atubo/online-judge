import java.util.*;

public class P015C {
    private static long xorRecur(long x, long mask, long currResult) {
        if (x <= 1) return (currResult ^ x);
        if (x >= mask && (x + 1 - mask) % 2 == 1) {
            currResult = currResult | mask;
        }
        if (x >= mask && mask == 2) {
            currResult = currResult ^ 1;
        }
        return xorRecur(x & (mask-1), mask>>1, currResult);
    }
        
    private static long xorSum(long x) {
        long mask = 1;
        while (x >= (mask << 1)) {
            mask = mask << 1;
        }
        return xorRecur(x, mask, 0);
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        long result = 0;
        for (int i = 0; i < n; i++) {
            long x = sc.nextLong();
            long m = sc.nextLong();
            result = result ^ (xorSum(x + m - 1) ^ xorSum(x - 1));
        }
        
        System.out.println(result == 0 ? "bolik" : "tolik");
    }
}
            
        