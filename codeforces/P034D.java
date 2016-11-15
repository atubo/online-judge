import java.util.*;

public class P034D {
    private int[] parent1;  // old roadmap
    private int[] parent2;  // new roadmap
    private final int N;
    private final int r1;
    private final int r2;
    
    private ArrayList<TreeSet<Integer>> neighbors = new ArrayList<TreeSet<Integer>>();
    
    private void setupTree() {
        for (int i = 0; i < N; i++) {
            if (i == r1) continue;
            int p = parent1[i];

            neighbors.get(i).add(p);
            neighbors.get(p).add(i);
        }
    }
    
    private void moveRoot() {
        boolean[] visited = new boolean[N];       
        java.util.Queue<Integer> queue = new ArrayDeque<Integer>();
        
        queue.add(r2);
        visited[r2] = true;
        
        while (!queue.isEmpty()) {
            int u = queue.poll();
            for (int v: neighbors.get(u)) {
                if (!visited[v]) {
                    parent2[v] = u;
                    visited[v] = true;
                    queue.add(v);
                }
            }
        }
    }
    
    public P034D() {
        Scanner sc = new Scanner(System.in);
        N  = sc.nextInt();
        r1 = sc.nextInt() - 1;
        r2 = sc.nextInt() - 1;
        parent1 = new int[N];
        parent2 = new int[N];
        
        for (int i = 0; i < N; i++) {
            neighbors.add(new TreeSet<Integer>());
            if (i == r1) continue;
            parent1[i] = sc.nextInt() - 1;
        }
        
        setupTree();
        
        moveRoot();
        
        for (int i = 0; i < N; i++) {
            if (i == r2) continue;
            System.out.printf("%d ", parent2[i] + 1);
        }
    }
    
    public static void main(String[] args) {
        P034D solution = new P034D();
    }
}