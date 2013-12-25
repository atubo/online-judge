import java.util.*;

public class P355B {
    public static void main(String[] args) {
        int sumBus = 0;
        int sumTro = 0;
        
        Scanner sc = new Scanner(System.in);
        int c1 = sc.nextInt();
        int c2 = sc.nextInt();
        int c3 = sc.nextInt();
        int c4 = sc.nextInt();
        
        int n = sc.nextInt();
        int m = sc.nextInt();
   
        for (int i = 0; i < n; i++) {
            int a = sc.nextInt();
            sumBus += Math.min(a * c1, c2);
        }
        sumBus = Math.min(sumBus, c3);
        
        for (int i = 0; i < m; i++) {
            int a = sc.nextInt();
            sumTro += Math.min(a * c1, c2);
        }
        sumTro = Math.min(sumTro, c3);
        
        System.out.println(Math.min(sumBus + sumTro, c4));
    }
}
        
        