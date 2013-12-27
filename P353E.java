import java.util.*;

public class P353E {
    private static class Result {
        private boolean whiteMarkable;
        private int endPos;
        
        public Result(boolean whiteMarkable, int endPos) {
            this.whiteMarkable = whiteMarkable;
            this.endPos        = endPos;
        }
    }
    
    private final int N;
    private final int[] dir;
    private final int[] color;
    
    private static final int BLACK = 0;
    private static final int WHITE = 1;
    private static final int GREY  = 2;
    
    private int next(int i) {
        return (i + 1) % N;
    }
    
    private Result isWhiteMarkable(int start) {
        int pos = start;

        while (color[pos] != WHITE && dir[pos] == dir[start]) {
            pos = next(pos);
        }
        if (color[pos] == WHITE) {
            return new Result(false, -1);
        } else {
            return new Result(true, pos);
        }
    }
    
    private int solve(int start) {
        for (int i = 0; i < N; i++) {
            color[i] = GREY;
        }
        
        int pos = start;
        while (true) {
            Result result = isWhiteMarkable(pos);
            if (!result.whiteMarkable) break;

            color[pos] = WHITE;
            int endPos = result.endPos;
            for (int i = next(pos); i != endPos; i = next(i)) {
                color[pos] = BLACK;
            }
            pos = next(endPos);
        }
        int rt = 0;
        for (int i = 0; i < N; i++) {
            if (color[i] == WHITE) rt++;
        }
        
        return rt;
    }
    
    public P353E() {
        Scanner sc = new Scanner(System.in);
        String s = sc.nextLine();
        N = s.length();
        dir = new int[N];
        color = new int[N];
        int i;
        for (i = 0; i < N; i++) {
            dir[i] = s.charAt(i) - '0';
        }
        for (i = 0; i < N; i++) {
            if (dir[i] != dir[next(i)]) {
                System.out.println(Math.max(solve(i), solve(next(i))));
                break;
            }
        }
        if (i == N) {
            System.out.println(0);
        }
    }
    
    public static void main(String[] args) {
        P353E solution = new P353E();
    }
}