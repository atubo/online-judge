import java.util.*;

public class P069D {
    private class Dot implements Comparable<Dot> {
        private final int x;
        private final int y;
        
        public Dot(int x, int y) {
            this.x    = x;
            this.y    = y;
        }
        
        public Dot addVec(MoveVec v) {
            return new Dot(x + v.x, y + v.y);
        }
        
        public Dot subVec(MoveVec v) {
            return new Dot(x - v.x, y - v.y);
        }
        
        public int compareTo(Dot other) {
            int rs1 = distSq(this);
            int rs2 = distSq(other);
            if (rs1 > rs2) return -1;
            if (rs1 < rs2) return 1;
            if (x > other.x) return -1;
            if (x < other.x) return 1;
            return 0;
        }
        
        public boolean equals(Object o) {
            if (o instanceof Dot) {
                Dot other = (Dot)o;
                return (x == other.x && y == other.y);
            }
            return false;
        }
        
        private int distSq(Dot p) {
            int dx = p.x - P0.x;
            int dy = p.y - P0.y;
            return dx * dx + dy * dy;
        }
    }
    
    private static class MoveVec {
        private final int x;
        private final int y;
        
        public MoveVec(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
    
    private static class Board {
        private final int N = 401;
        // shifted by 200
        private final int SHIFT = 200;
        private boolean[][] visited = new boolean[N][N];
        private char[][] flag = new char[N][N];  // 0x1 - lose, 0x2 - win
        
        public boolean isVisited(Dot p) {
            return visited[p.x+SHIFT][p.y+SHIFT];
        }
        
        public void markVisited(Dot p) {
            visited[p.x+SHIFT][p.y+SHIFT] = true;
        }
        
        public void clearVisited() {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    visited[i][j] = false;
                }
            }
        }
        
        public void markFlag(Dot p, char mf) {
            flag[p.x+SHIFT][p.y+SHIFT] |= mf;
        }
        
        public char getFlag(Dot p) {
            return flag[p.x+SHIFT][p.y+SHIFT];
        }
    }
    
    private final MoveVec[] vs;
    private final Dot P0;
    private final int D;
    private Board board = new Board();
    
    private PriorityQueue<Dot> dots = new PriorityQueue<Dot>();
    
    public P069D() {
        Scanner sc = new Scanner(System.in);
        int x0 = sc.nextInt();
        int y0 = sc.nextInt();
        P0 = new Dot(x0, y0);
        int N = sc.nextInt();
        D = sc.nextInt();
        
        vs = new MoveVec[N];
        for (int i = 0; i < N; i++) {
            int x = sc.nextInt();
            int y = sc.nextInt();
            vs[i] = new MoveVec(x, y);
        }
        
        findLossingDots();
        propagate();
    }
            
    
    private boolean inRange(Dot p) {
        return p.x * p.x + p.y * p.y <= D * D;
    }
    
    private void findLossingDots() {
        java.util.Queue<Dot> queue = new ArrayDeque<Dot>();
        
        queue.add(P0);
        board.markVisited(P0);
        while (!queue.isEmpty()) {
            Dot p = queue.poll();
            boolean found = false;
            for (MoveVec v: vs) {
                Dot pnext = p.addVec(v);
                if (!inRange(pnext)) continue;
                found = true;
                if (!board.isVisited(pnext)) {
                    queue.add(pnext);
                    board.markVisited(pnext);
                }
            }
            
            if (!found) {
                dots.add(p);
                board.markFlag(p, (char)1);
            }
        }
        
        board.clearVisited();
    }
    
    private boolean lessThanP0(Dot p) {
        return p.x < P0.x || p.y < P0.y;
    }
    
    private void propagate() {
        Dot p = dots.poll();
        while (!p.equals(P0)) {
            board.markVisited(p);
            char flag = board.getFlag(p);
            for (MoveVec v: vs) {
                Dot pprev = p.subVec(v);
                if (lessThanP0(pprev)) continue;
                
                if ((flag & 0x2) == 0) {  // L -> W
                    assert flag == 1;
                    board.markFlag(pprev, (char)0x2);
                } else {
                    board.markFlag(pprev, (char)0x1);
                }
                if (!board.isVisited(pprev)) {
                    dots.add(pprev);
                    board.markVisited(pprev);
                }
            }
            
            p = dots.poll();
        }
        System.out.println((board.getFlag(p) & 0x2) == 0 ? "Dasha" : "Anton");          
    }
        
    
    public static void main(String[] args) {
        P069D solution = new P069D();
    }
}
        
        