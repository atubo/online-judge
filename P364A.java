import java.util.*;

public class P364A {
    private static void increment(HashMap<Integer, Integer> count, int key) {
        if (!count.containsKey(key)) {
            count.put(key, 0);
        }
        count.put(key, count.get(key) + 1);
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int a = sc.nextInt();
        String str = sc.next();
        int N = str.length();
        int[] s = new int[N];
        for (int i = 0; i < N; i++) {
            s[i] = str.charAt(i) - '0';
        }
        int[] ps = new int[N];
        ps[0] = s[0];
        for (int i = 1; i < N; i++) {
            ps[i] = s[i] + ps[i-1];
        }
        
        int[][] b = new int[N][N];
        HashMap<Integer, Integer> count = new HashMap<Integer, Integer>();
        for (int j = 0; j < N; j++) {
            b[0][j] = ps[j];
            increment(count, b[0][j]);
        }
        for (int i = 1; i < N; i++) {
            for (int j = i; j < N; j++) {
                b[i][j] = ps[j] - ps[i-1];
                increment(count, b[i][j]);
            }
        }
        
        long result = 0;
        for (int i = 0; i < N; i++) {
            for (int j = i; j < N; j++) {
                if (a % b[i][j] == 0) {
                    int key = a / b[i][j];
                    if (!count.containsKey(key)) continue;
                    result += count.get(key);
                }
            }
        }
        
        System.out.println(result);
    }
}
        