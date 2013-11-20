import java.util.*;

public class P059C {
    private StringBuilder s;
    
    public boolean solve() {
        Scanner sc = new Scanner(System.in);
        int k = sc.nextInt();
        sc.nextLine();
        s = new StringBuilder(sc.next());
        int N = s.length();
        
        TreeSet<Character> alpha = new TreeSet<Character>();
        for (int i = 0; i < k; i++) {
            alpha.add((char)(i+'a'));
        }
        
        // first round
        for (int i = 0; i < N; i++) {
            char c = s.charAt(i);
            if (c != '?') {
                char c2 = s.charAt(N-1-i);
                if (c2 != '?' && c2 != c) {
                    return false;
                }
                if (c2 == '?') {
                    s.setCharAt(N-1-i, c);
                }
                if (alpha.contains(c)) {
                    alpha.remove(c);
                }
            }
        }
        
        
        for (int i = N/2; i < N; i++) {
            if (s.charAt(i) == '?') {
                assert s.charAt(N-1-i) == '?';
                char c;
                if (alpha.isEmpty()) {
                    c = 'a';
                }
                else {
                    c = alpha.pollLast();
                }
                s.setCharAt(i, c);
                s.setCharAt(N-1-i, c);
            }
        }
        
        return alpha.isEmpty();
    }
    
    public P059C() {
        boolean ans = solve();
        if (ans) {
            System.out.println(s);
        }
        else {
            System.out.println("IMPOSSIBLE");
        }
    }
    
    public static void main(String[] args) {
        P059C solution = new P059C();
    }
}
                
        