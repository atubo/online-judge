import java.util.*;

public class P042D {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] a = new int[n];
        a[0] = 1;
        a[1] = 2;
        
        TreeSet<Integer> occu = new TreeSet<Integer>();
        occu.add(3);
        for (int i = 2; i < n; i++) {
            for (int j = a[i-1] + 1; j <= 1000; j++) {
                boolean found = true;
                for (int k = 0; k < i; k++) {
                    if (occu.contains(j + a[k])) {
                        found = false;
                        break;
                    }
                }
                if (found) {
                    a[i] = j;
                    for (int k = 0; k < i; k++) {
                        occu.add(a[i] + a[k]);
                    }
                    break;
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                System.out.printf("%d ", (i == j ? 0 : a[i] + a[j]));
            }
            System.out.println();
        }
    }
}