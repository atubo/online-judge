import java.util.*;

public class P026C {
    private char[][] floor;
    private int n;
    private int m;
    private int a;
    private int b;
    private int c;
    
    public P026C() {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        m = sc.nextInt();
        a = sc.nextInt();
        b = sc.nextInt();
        c = sc.nextInt();
        floor = new char[n][m];
        
        if (!solve()) {
            System.out.println("IMPOSSIBLE");
        }
    }
    
    private boolean solve() {
        if (n % 2 == 1 && m % 2 == 1) {
            return false;
        }

        if (n % 2 == 1) {
            for (int i = 0; i < m; i+=2) {
                floor[n-1][i] = floor[n-1][i+1] = (i % 4 == 2 ? 'a' : 'b');
            }
            a -= m/2;
        }
        if (m % 2 == 1) {
            for (int i = 0; i < n; i+=2) {
                floor[i][m-1] = floor[i+1][m-1] = (i % 4 == 2 ? 'a' : 'b');
            }
            b -= n/2;
        }
        if (a < 0 || b < 0) return false;
        if (a % 2 == 1) --a;
        if (b % 2 == 1) --b;
        
        if (a*2 + b*2 + c*4 < (n/2*2)*(m/2*2)) return false;
        for (int i = n/2*2-1; i >= 0; i-=2) {
            for (int j = m/2*2-1; j >= 0; j-=2) {
                if (a > 0) {
                    parquetTypeA(i, j);
                }
                else if (b > 0) {
                    parquetTypeB(i, j);
                }
                else {
                    parquetTypeC(i, j);
                }
            }
        }
        printLayout();
        return true;
    }
    
    private void parquetTypeA(int i, int j) {
        ArrayList<Character> colors = getColors(i, j);
        floor[i][j] = floor[i][j-1] = colors.get(0);
        floor[i-1][j] = floor[i-1][j-1] = colors.get(1);
        a -= 2;
    }
    
    private void parquetTypeB(int i, int j) {
        ArrayList<Character> colors = getColors(i, j);
        floor[i][j] = floor[i-1][j] = colors.get(0);
        floor[i][j-1] = floor[i-1][j-1] = colors.get(1);
        b -= 2;
    }
    
    private void parquetTypeC(int i, int j) {
        ArrayList<Character> colors = getColors(i, j);
        floor[i][j] = floor[i][j-1] = floor[i-1][j] = floor[i-1][j-1] = colors.get(0);
        --c;
    }
    
    private void printLayout() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                System.out.print(floor[i][j]);
            }
            System.out.println();
        }
    }
    
    private ArrayList<Character> getColors(int i, int j) {
        Character[] cand = {'a', 'b', 'c', 'd', 'e', 'f'};
        HashSet<Character> candidates = new HashSet<Character>(Arrays.asList(cand));
        if (i < n-1) {
            candidates.remove(floor[i+1][j]);
            candidates.remove(floor[i+1][j-1]);
        }
        if (j < m-1) {
            candidates.remove(floor[i][j+1]);
            candidates.remove(floor[i-1][j+1]);
        }
        
        return new ArrayList<Character>(candidates);
    }
    
    public static void main(String[] args) {
        P026C solution = new P026C();
    }
    
}
        