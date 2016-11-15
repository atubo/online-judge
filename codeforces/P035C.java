import java.io.*;
import java.util.*;

public class P035C {
    private class Pair {
        private int x;
        private int y;
        
        private Pair(int x, int y) {
            this.x = x;
            this.y = y;
        }
        
        public int hashCode() {
            return 37 * x + y;
        }
        
        public boolean equals(Object other) {
            if (other instanceof Pair) {
                Pair otherPair = (Pair)other;
                return x == otherPair.x && y == otherPair.y;
            }
            
            return false;
        }
    }
    
    private boolean[][] visited;
    private final int N;
    private final int M;
    private final int k;
    private ArrayList<Pair> fires = new ArrayList<Pair>();
    private ArrayList<Pair> neighbors = new ArrayList<Pair>();
    
    public P035C() throws IOException {
        Scanner sc = new Scanner(new File("input.txt"));

        N = sc.nextInt();
        M = sc.nextInt();
        visited = new boolean[N][M];
        k = sc.nextInt();
        for (int i = 0; i < k; i++) {
            int x = sc.nextInt() - 1;
            int y = sc.nextInt() - 1;
            fires.add(new Pair(x, y));
        }
        bfs();
    }
    
    private void bfs() throws IOException{
        java.util.Queue<Pair> queue = new ArrayDeque<Pair>();
        for (Pair p : fires) {
            queue.add(p);
            visited[p.x][p.y] = true;
        }
        
        Pair last = fires.get(0);
        while (!queue.isEmpty()) {
            Pair p = last = queue.poll();            
            for (Pair pn : getNeighbors(p)) {
                if (!visited[pn.x][pn.y]) {
                    queue.add(pn);
                    visited[pn.x][pn.y] = true;
                }
            }
        }
        
        PrintWriter output = new PrintWriter(new FileWriter(new File("output.txt")));
        output.printf("%d %d\n", last.x + 1, last.y + 1);
        output.close();
    }
    
    private Collection<Pair> getNeighbors(Pair p) {
        neighbors.clear();
        if (p.x > 0)   neighbors.add(new Pair(p.x-1, p.y));
        if (p.x < N-1) neighbors.add(new Pair(p.x+1, p.y));
        if (p.y > 0)   neighbors.add(new Pair(p.x, p.y-1));
        if (p.y < M-1) neighbors.add(new Pair(p.x, p.y+1));
        
        return neighbors;
    }
    
    public static void main(String[] args) throws IOException {
        P035C solution = new P035C();
    }
}
        
      