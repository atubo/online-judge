import java.util.*;

public class P022A {
    private TreeSet<Integer> numbers = new TreeSet<Integer>();
    
    public void solve() {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        for (int i = 0; i < n; i++) {
            int x = sc.nextInt();
            numbers.add(x);
        }
        if (numbers.size() < 2) {
            System.out.println("NO");
            return;
        }
        numbers.pollFirst();
        System.out.println(numbers.first());
    }
    
    public static void main(String[] argv) {
        P022A solution = new P022A();
        solution.solve();
    }
}