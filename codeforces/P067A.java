import java.util.*;

public class P067A {  
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int[] a  = new int[N];
        sc.nextLine();
        String r = sc.nextLine();
        
        a[0] = 1;
        for (int i = 1; i < N; i++) {
            char c = r.charAt(i-1);
            if (c == 'R') {
                a[i] = a[i-1] + 1;
            }
            else if (c == '=') {
                a[i] = a[i-1];
            }
            else {
                a[i] = 1;
                int j = i - 1;
                while (j >= 0 && (r.charAt(j) == 'L' && a[j] <= a[j+1] || r.charAt(j) == '=' && a[j] != a[j+1])) {
                    if (r.charAt(j) == 'L') {
                        a[j] = a[j+1] + 1;
                    }
                    else {
                        a[j] = a[j+1];
                    }
                    j--;
                }
            }
        }
        for (int x: a) {
            System.out.printf("%d ", x);
        }
    }
}