import java.util.*;
import java.io.*;

public class P387E {
    private static class BIT {
        private final int N;
        private int[] tree;
        
        public BIT(int N) {
            this.N = N;
            tree = new int[N + 1];
        }
        
        private void set(int x, int v) {
            while (x <= N) {
                tree[x] += v;
                x += (x & -x);
            }
        }
        
        private int get(int x) {
            int res = 0;
            while (x != 0) {
                res += tree[x];
                x -= (x & -x);
            }
            return res;
        }
    }
    
    /** Class for buffered reading int and double values */
    private static class Reader {
        static BufferedReader reader;
        static StringTokenizer tokenizer;
        
        /** call this method to initialize reader for InputStream */
        static void init(InputStream input) {
            reader = new BufferedReader(
                                        new InputStreamReader(input) );
            tokenizer = new StringTokenizer("");
        }
        
        /** get next word */
        static String next() throws IOException {
            while ( ! tokenizer.hasMoreTokens() ) {
                //TODO add check for eof if necessary
                tokenizer = new StringTokenizer(
                                                reader.readLine() );
            }
            return tokenizer.nextToken();
        }
        
        static int nextInt() throws IOException {
            return Integer.parseInt( next() );
        }
        
        static double nextDouble() throws IOException {
            return Double.parseDouble( next() );
        }
    }
    
    private static int getDiscarded(BIT bit, int left, int right) {
        int x1 = (left-1 == 0 ? 0 : bit.get(left-1));
        int x2 = (right == 0 ? 0 : bit.get(right));
        return x2 - x1;
    }
    
    public static void main(String[] args) throws IOException {
        Reader.init(System.in);
        int n = Reader.nextInt();
        int k = Reader.nextInt();
        
        int[] a = new int[n+1];
        int[] pos = new int[n+1];
        for (int i = 0; i < n; i++) {
            int x = Reader.nextInt();
            a[i+1] = x;
            pos[x] = i + 1;
        }
        
        int[] remain = new int[k];
        for (int i = 0; i < k; i++) {
            remain[i] = Reader.nextInt();
        }
        
        HashSet<Integer> togo = new HashSet<Integer>();
        int cur = 1;
        for (int i = 0; i < k; i++) {
            while (a[cur] != remain[i]) {
                togo.add(a[cur]);
                cur++;
            }
            cur++;
        }
        for (; cur < n+1; cur++) {
            togo.add(a[cur]);
        }
        
        BIT bit = new BIT(n);
        TreeSet<Integer> occu = new TreeSet<Integer>();
        long result = 0;
        for (int i = 1; i < n+1; i++) {
            int x = pos[i];
            if (togo.contains(i)) {
                int right = (occu.ceiling(x+1) == null ? n : occu.ceiling(x+1)-1);
                int left  = (occu.floor(x-1) == null ? 1 : occu.floor(x-1)+1);
                int discarded = getDiscarded(bit, left, right);
                result += right - left + 1 - discarded;
                bit.set(x, 1);
            } else {
                occu.add(x);
            }
        }
        
        System.out.println(result);
    }
}
                
        
        
