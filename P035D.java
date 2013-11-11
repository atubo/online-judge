import java.util.*;
import java.io.*;

public class P035D {
    private PriorityQueue<Integer> queue = new PriorityQueue<Integer>(1, Collections.reverseOrder());
    private final int N;
    private final int X;
    private int[] consumption;
    
    private void solve() {
        queue.add(0);
        int food = X;
        for (int i = 0; i < N; i++) {
            int cost = consumption[i] * (N-i);
            if (food >= cost) {
                queue.add(cost);
                food -= cost;
            }
            else {
                int largestSaving = queue.peek();
                if (largestSaving > cost) {
                    queue.poll();
                    queue.add(cost);
                    food = food + largestSaving - cost;
                }
            }
        }
    }
    
    public P035D() throws FileNotFoundException {
        Scanner sc = new Scanner(new File("input.txt"));
        N = sc.nextInt();
        consumption = new int[N];
        X = sc.nextInt();
        
        for (int i = 0; i < N; i++) {
            consumption[i] = sc.nextInt();
        }
        
        solve();
        
        PrintWriter writer = new PrintWriter("output.txt");
        writer.println(queue.size()-1);
        writer.close();
    }
    
    public static void main(String[] args) {
        try {
            P035D solution = new P035D();
        }
        catch(FileNotFoundException e) {
            System.out.println("Input file not found");
        }
    }
}
   