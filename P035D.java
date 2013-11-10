import java.util.*;
import java.io.*;

public class P035D {
    private static class Key {
        private int food;
        private int speed;  // food consumption speed
        private int day;
        
        public Key(int food, int speed, int day) {
            this.food  = food;
            this.speed = speed;
            this.day   = day;
        }
        
        // TODO: overwrite hashCode and equal
    }
    
    HashMap<Key, Integer> dp = new HashMap<Key, Integer>();
    private int N;
    private int[] consumption;
    
    private int solve(int food, int speed, int day) {
        Key key = new Key(food, speed, day);
        if (dp.containsKey(key)) return dp.get(key);
        
        if (food < speed) return Integer.MIN_VALUE;
        
        int result;
        if (day == N-1) {
            if (food - speed >= consumption[N-1])  result = 1;
            else result = 0;
            dp.put(key, result);
            return result;
        }
        
        int c = consumption[day];
        result = Math.max(solve(food-speed, speed, day+1),
                          solve(food-speed-c, speed+c, day+1) + 1);
        dp.put(key, result);
        return result;
    }
    
    private void solve() throws FileNotFoundException {
        Scanner sc = new Scanner(new File("input.txt"));
        N = sc.nextInt();
        consumption = new int[N];
        int X = sc.nextInt();
        
        for (int i = 0; i < N; i++) {
            consumption[i] = sc.nextInt();
        }
        
        int result = Math.max(0, solve(X, 0, 0));
        
        PrintWriter writer = new PrintWriter("output.txt");
        writer.println(result);
        writer.close();
    }
    
    public P035D() {
        try {
            solve();
        }
        catch(FileNotFoundException e) {
            System.out.println("Input file not found");
        }
    }
    
    public static void main(String[] args) {
        P035D solution = new P035D();
    }
}
   