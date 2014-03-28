import java.util.*;
import java.io.*;

public class P073E {
    private static ArrayList<Integer> primes = new ArrayList<Integer>();
    
    private static void sieve() {
        // the 100,008th is 1,299,827
        final int N = 1_299_828;
        char[] bit = new char[N];
        for (int i = 2; i < N; i++) {
            bit[i] = 1;
        }
        for (int i = 2; i < N; i++) {
            if (bit[i] == 0) continue;
            int q = i;
            while (q + i < N) {
                q += i;
                bit[q] = 0;
            }
        }
        
        for (int i = 2; i < N; i++) {
            if (bit[i] == 1) {
                primes.add(i);
            }
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

    
    public int solve() throws IOException {
        Reader.init(System.in);
        int N = Reader.nextInt();
        int x = Reader.nextInt();
        TreeSet<Integer> a = new TreeSet<>();
        for (int i = 0; i < N; i++) {
            a.add(Reader.nextInt());
        }
        
        if (x == 2) return 0;
        if (!a.isEmpty() && a.first() == 1) return 1;
        
        int i;
        for (i = 0; i < primes.size(); i++) {
            int p = primes.get(i);
            if (p > x) break;
            if (!a.contains(p)) {
                return -1;
            }
        }
        return i;
    }
    
    public static void main(String[] args) throws IOException {
        P073E solution = new P073E();
        solution.sieve();
        System.out.println(solution.solve());
    }
}
