import java.util.*;

public class P016A {
    public static void main(String[] argv) {
        P016A solution = new P016A();
        boolean result = solution.solve();
        String out = result ? "YES" : "NO";
        System.out.println(out);
    }
    
    public boolean solve() {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        
        for (int i = 0; i < n; i++) {
            flag.add(sc.next());
        }
        
        for (String s : flag) {
            if (!isValidStrip(s)) {
                return false;
            }
        }
        
        for (int i = 0; i < n; i++) {
            if (!isValidRow(i)) {
                return false;
            }
        }
        
        return true;
    }
    
    private boolean isValidStrip(String strip) {
        char c = strip.charAt(0);
        for (int i = 1; i < strip.length(); i++) {
            if (strip.charAt(i) != c) return false;
        }
        return true;
    }
    
    private boolean isValidRow(int row) {
        if (row == 0) return true;
        return (flag.get(row).charAt(0) != flag.get(row-1).charAt(0));
    }
    
    private ArrayList<String> flag = new ArrayList<String>();        
}