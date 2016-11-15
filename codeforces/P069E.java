import java.util.*;

public class P069E {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int K = sc.nextInt();
        int[] a = new int[N];
        for (int i = 0; i < N; i++) {
            a[i] = sc.nextInt();
        }
        TreeSet<Integer> candidates = new TreeSet<Integer>();
        TreeMap<Integer, Integer> count = new TreeMap<Integer, Integer>();
        
        for (int i = 0; i < K; i++) {
            int x = a[i];
            if (!count.containsKey(x)) {
                count.put(x, 0);
            }
            count.put(x, count.get(x) + 1);
        }
        for (Map.Entry<Integer, Integer> entry: count.entrySet()) {
            if (entry.getValue() == 1) {
                candidates.add(entry.getKey());
            }
        }
        printResult(candidates);
        
        for (int i = K; i < N; i++) {
            int xIn  = a[i];
            int xOut = a[i-K];
            if (xIn == xOut) {
                printResult(candidates);
                continue;
            }
            
            if (!count.containsKey(xIn)) {
                count.put(xIn, 0);
            }
            count.put(xIn, count.get(xIn) + 1);
            if (count.get(xIn) == 1) {
                candidates.add(xIn);
            } else if (count.get(xIn) == 2) {
                candidates.remove(xIn);
            }
            
            count.put(xOut, count.get(xOut) - 1);
            if (count.get(xOut) == 0) {
                candidates.remove(xOut);
            } else if (count.get(xOut) == 1) {
                candidates.add(xOut);
            }
            
            printResult(candidates);
        }
    }
    
    static void printResult(TreeSet<Integer> candidates) {
        if (candidates.isEmpty()) {
            System.out.println("Nothing");
        } else {
            System.out.println(candidates.last());
        }
    }
}
        
            
            