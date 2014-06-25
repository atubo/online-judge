import java.util.*;

public class P442B {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        double[] p = new double[N];
        for (int i = 0; i < N; i++) {
            p[i] = sc.nextDouble();
        }
        Arrays.sort(p);
        if (p[N-1] == 1.0) {
            System.out.printf("%.9f\n", 1.0);
            return;
        }
        
        double S = 0;
        double P = 1;
        for (int i = N-1; i >= 0; i--) {
            if (S >= 1) break;
            P *= 1-p[i];
            S += p[i]/(1-p[i]);
        }
        System.out.printf("%.9f\n", P*S);
    }
}
            