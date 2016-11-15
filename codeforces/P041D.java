import java.util.*;

public class P041D {
    private ArrayList<ArrayList<HashMap<Integer, Character>>> pred;
    private ArrayList<ArrayList<HashMap<Integer, Integer>>> dp;
    private int[][] board;
    private final int N;
    private final int M;
    private final int k;
    
    public P041D() {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        M = sc.nextInt();
        k = sc.nextInt();

        pred = new ArrayList<ArrayList<HashMap<Integer, Character>>>();
        dp   = new ArrayList<ArrayList<HashMap<Integer, Integer>>>();
        for (int i = 0; i < N; i++) {
            pred.add(new ArrayList<HashMap<Integer, Character>>());
            dp.add(new ArrayList<HashMap<Integer, Integer>>());
            for (int j = 0; j < M; j++) {
                pred.get(i).add(new HashMap<Integer, Character>());
                dp.get(i).add(new HashMap<Integer, Integer>());
            }
        }
        
        board  = new int[N][M];
        for (int i = N-1; i >= 0; i--) {
            String s = sc.next();
            for (int j = 0; j < M; j++) {
                board[i][j] = s.charAt(j) - 48;
            }
        }
    }
    
    Set<Integer> neighbors(int col) {
        HashSet<Integer> result = new HashSet<Integer>();
        if (col > 0) {
            result.add(col-1);
        }
        if (col < M - 1) {
            result.add(col+1);
        }
        return result;
    }
    
    char getDirection(int jp, int j) {
        assert Math.abs(jp - j) == 1;
        if (jp < j) return 'R';
        else        return 'L';
    }
    
    public void solve() {
        for (int j = 0; j < M; j++) {
            HashMap<Integer, Character> predEntry = pred.get(0).get(j);
            HashMap<Integer, Integer> dpEntry = dp.get(0).get(j);
            int numPeas = board[0][j];
            for (int r = 0; r < k+1; r++) {
                if (numPeas % (k+1) == r) {
                    dpEntry.put(r, numPeas);
                } else {
                    dpEntry.put(r, Integer.MIN_VALUE);
                }
                predEntry.put(r, '\0');
            }
        }
        
        for (int i = 1; i < N; i++) {
            for (int j = 0; j < M; j++) {
                for (int r = 0; r < k+1; r++) {
                    int numPeas = board[i][j];
                    int rp = (r + k + 1 - (numPeas%(k+1))) % (k + 1);
                    int maxVal = Integer.MIN_VALUE;
                    char maxDir = '\0';
                    for (int jp: neighbors(j)) {
                        HashMap<Integer, Integer> dpEntry = dp.get(i-1).get(jp);
                        if (dpEntry.get(rp) >= maxVal) {
                            maxVal = dpEntry.get(rp);
                            maxDir = getDirection(jp, j);
                        }
                    }

                    if (maxVal >= 0) {
                        assert maxDir == 'R' || maxDir == 'L';
                        pred.get(i).get(j).put(r, maxDir);
                        dp.get(i).get(j).put(r, maxVal + numPeas);
                    } else {
                        assert maxVal == Integer.MIN_VALUE;
                        pred.get(i).get(j).put(r, '\0');
                        dp.get(i).get(j).put(r, maxVal);
                    }
                                                   
                }
            }
        }
        
        int maxVal = Integer.MIN_VALUE;
        int maxPos = -1;
        for (int j = 0; j < M; j++) {
            if (dp.get(N-1).get(j).get(0) > maxVal) {
                maxVal = dp.get(N-1).get(j).get(0);
                maxPos = j;
            }
        }
        
        if (maxPos == -1) {
            System.out.println(maxPos);
            return;
        }
        
        int pos = maxPos;
        char[] path = new char[N-1];
        int r = 0;
        for (int j = N - 1; j > 0; j--) {
            char dir = pred.get(j).get(pos).get(r);
            r = (r + k + 1 - (board[j][pos]%(k+1))) % (k+1);
            path[j-1] = dir;
            assert dir == 'R' || dir == 'L';
            if (dir == 'R') pos--;
            else            pos++;
        }
        
        System.out.println(maxVal);
        System.out.println(pos + 1);
        for (int i = 0; i < N - 1; i++) {
            System.out.printf("%c", path[i]);
        }
        System.out.println();
           
        
        assert maxVal == Integer.MIN_VALUE || maxVal >= 0;
                        
    }
    
    public static void main(String[] args) {
        P041D solution = new P041D();
        solution.solve();
    }
            
}

                
    
    