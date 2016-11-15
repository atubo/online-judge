import java.util.*;

public class P044C {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        
        int[] water = new int[n];
        for (int i = 0; i < m; i++) {
            int a = sc.nextInt() - 1;
            int b = sc.nextInt() - 1;
            for (int j = a; j <= b; j++) {
                water[j]++;
            }
        }
        
        for (int i = 0; i < n; i++) {
            if (water[i] != 1) {
                System.out.printf("%d %d\n", i+1, water[i]);
                return;
            }
        }
        
        System.out.println("OK");
    }
}
            