import java.util.*;

public class P402E {
    public static class SCCKosaraju {
        
        static void dfs(List<Integer>[] graph, boolean[] used, List<Integer> res, int u) {
            used[u] = true;
            for (int v : graph[u])
                if (!used[v])
                dfs(graph, used, res, v);
            res.add(u);
        }
        
        public static List<List<Integer>> scc(List<Integer>[] graph) {
            int n = graph.length;
            boolean[] used = new boolean[n];
            List<Integer> order = new ArrayList<>();
            for (int i = 0; i < n; i++)
                if (!used[i])
                dfs(graph, used, order, i);
            
            List<Integer>[] reverseGraph = new List[n];
            for (int i = 0; i < n; i++)
                reverseGraph[i] = new ArrayList<>();
            for (int i = 0; i < n; i++)
            for (int j : graph[i])
                reverseGraph[j].add(i);
            
            List<List<Integer>> components = new ArrayList<>();
            Arrays.fill(used, false);
            Collections.reverse(order);
            
            for (int u : order)
                if (!used[u]) {
                List<Integer> component = new ArrayList<>();
                dfs(reverseGraph, used, component, u);
                components.add(component);
            }
            
            return components;
        }
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        sc.nextLine();
        List<Integer>[] graph = new List[N];
        for (int i = 0; i < N; i++) {
            graph[i] = new ArrayList<>();
            StringTokenizer st = new StringTokenizer(sc.nextLine());
            for (int j = 0; j < N; j++) {
                int a = Integer.parseInt(st.nextToken());
                if (a > 0) {
                    graph[i].add(j);
                }
            }
        }
        List<List<Integer>> scc = SCCKosaraju.scc(graph);
        System.out.println(scc.size() == 1 ? "YES" : "NO");
    }
}