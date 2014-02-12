import java.util.*;

public class P389E {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[][] c = new int[n][];
        for (int i = 0; i < n; i++) {
            int s = sc.nextInt();
            c[i] = new int[s];
            for (int j = 0; j < s; j++) {
                c[i][j] = sc.nextInt();
            }
        }
        
        int ciel = 0;
        int jiro = 0;
        
        ArrayList<Integer> middle = new ArrayList<Integer>();
        for (int i = 0; i < n; i++) {
            int s = c[i].length;
            for (int j = 0; j < s/2; j++) {
                ciel += c[i][j];
            }
            for (int j = (s-1)/2 + 1; j < s; j++) {
                jiro += c[i][j];
            }
            if (s % 2 == 1) {
                middle.add(c[i][s/2]);
            }
        }
        
        Collections.sort(middle, Collections.reverseOrder());
        for (int i = 0; i < middle.size(); i += 2) {
            ciel += middle.get(i);
        }
        for (int i = 1; i < middle.size(); i += 2) {
            jiro += middle.get(i);
        }
        
        System.out.printf("%d %d\n", ciel, jiro);            
    }
}