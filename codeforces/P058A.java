import java.util.*;

public class P058A {
    private static boolean check(String s, int spos, String h, int hpos) {
        if (hpos == h.length()) return true;
        for (int i = spos; i < s.length(); i++) {
            if (s.charAt(i) == h.charAt(hpos)) {
                return check(s, i+1, h, hpos+1);
            }
        }
        return false;
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String s = sc.next();
        boolean result = check(s, 0, "hello", 0);
        System.out.println(result ? "YES" : "NO");
    }
}