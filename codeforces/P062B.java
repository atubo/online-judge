import java.util.*;

public class P062B {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int k = sc.nextInt();
        String s = sc.next();
        
        ArrayList<TreeSet<Integer>> position = new ArrayList<>();
        for (int i = 0; i < 26; i++) {
            position.add(new TreeSet<Integer>());
        }
        
        for (int i = 0; i < k; i++) {
            char c = s.charAt(i);
            position.get(c-'a').add(i);
        }
        
        for (int i = 0; i < n; i++) {
            long result = 0;
            String sp = sc.next();
            int length = sp.length();
            for (int j = 0; j < length; j++) {
                char c = sp.charAt(j);
                Integer floor = position.get(c-'a').floor(j);
                int dist1 = (floor == null ? Integer.MAX_VALUE : j - floor);
                Integer ceiling = position.get(c-'a').ceiling(j);
                int dist2 = (ceiling == null ? Integer.MAX_VALUE : ceiling - j);
                int dist = Math.min(dist1, dist2);
                dist = (dist == Integer.MAX_VALUE ? length : dist);
                result += dist;
            }
            System.out.println(result);
        }
    }
}