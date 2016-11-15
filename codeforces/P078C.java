import java.util.*;

public class P078C {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        int k = sc.nextInt();
        
        boolean divisible = false;
        if (m > 1 && k == 1) divisible = true;
        for (int j = 2; j <= Math.sqrt(m); j++) {
            if (m % j == 0  && (m/j) >= k) {
                divisible = true;
                break;
            }
        }
        
        if (divisible && n % 2 == 1) {
            System.out.println("Timur");
        } else {
            System.out.println("Marsel");
        }
    }
}