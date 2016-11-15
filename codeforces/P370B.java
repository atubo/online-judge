import java.util.*;

public class P370B {
    private final int N;
    private ArrayList<HashSet<Integer>> players = new ArrayList<HashSet<Integer>>();
    
    public P370B() {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        for (int i = 0; i < N; i++) {
            int m = sc.nextInt();
            HashSet<Integer> player = new HashSet<Integer>();
            for (int j = 0; j < m; j++) {
                int a = sc.nextInt();
                player.add(a);
            }
            players.add(player);
        }
        
        for (int i = 0; i < N; i++) {
            boolean found = false;
            for (int j = 0; j < N; j++) {
                if (j == i) continue;
                if (players.get(i).containsAll(players.get(j))) {
                    System.out.println("NO");
                    found = true;
                    break;
                }
            }
            if (!found) {
                System.out.println("YES");
            }
        }
    }
    
    public static void main(String[] args) {
        P370B solution = new P370B();
    }
}
        