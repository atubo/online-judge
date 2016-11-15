import java.util.*;
import java.io.*;

public class P402E {
    // optimized version of http://en.wikipedia.org/wiki/Tarjan's_strongly_connected_components_algorithm
    public static class SCCTarjan {
        
        int time;
        List<Integer>[] graph;
        int[] lowlink;
        boolean[] used;
        List<Integer> stack;
        List<List<Integer>> components;
        
        public List<List<Integer>> scc(List<Integer>[] graph) {
            int n = graph.length;
            this.graph = graph;
            lowlink = new int[n];
            used = new boolean[n];
            stack = new ArrayList<>();
            components = new ArrayList<>();
            
            for (int u = 0; u < n; u++)
                if (!used[u])
                dfs(u);
            
            return components;
        }
        
        void dfs(int u) {
            lowlink[u] = time++;
            used[u] = true;
            stack.add(u);
            boolean isComponentRoot = true;
            
            for (int v : graph[u]) {
                if (!used[v])
                    dfs(v);
                if (lowlink[u] > lowlink[v]) {
                    lowlink[u] = lowlink[v];
                    isComponentRoot = false;
                }
            }
            
            if (isComponentRoot) {
                List<Integer> component = new ArrayList<>();
                while (true) {
                    int k = stack.remove(stack.size() - 1);
                    component.add(k);
                    lowlink[k] = Integer.MAX_VALUE;
                    if (k == u)
                        break;
                }
                components.add(component);
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
    
    public static void main(String[] args) throws IOException {
        Reader.init(System.in);
        int N = Reader.nextInt();
        List<Integer>[] graph = new List[N];
        for (int i = 0; i < N; i++) {
            graph[i] = new ArrayList<>(N);
            for (int j = 0; j < N; j++) {
                int a = Reader.nextInt();
                if (a > 0) {
                    graph[i].add(j);
                }
            }
        }
        List<List<Integer>> scc = new SCCTarjan().scc(graph);
        System.out.println(scc.size() == 1 ? "YES" : "NO");
    }
}