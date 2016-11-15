import java.util.*;

public class P077C {
    private static class NodeInfo {
        private long eaten;
        private long remain;
        
        public NodeInfo(long eaten, long remain) {
            this.eaten  = eaten;
            this.remain = remain;
        }
    }
    
    private ArrayList<ArrayList<Integer>> tree = new ArrayList<ArrayList<Integer>>();
    private NodeInfo[] nodeInfo;
    private int[] beavers;
    private int[] depth;
    private final int N;
    
    private void visit(int u) {
        assert nodeInfo[u] == null;
        
        ArrayList<Integer> children = tree.get(u);
        int n = children.size();
        long[] eaten  = new long[n];
        long[] remain = new long[n];
        
        for (int i = 0; i < n; i++) {
            eaten[i]  = nodeInfo[children.get(i)].eaten;
            remain[i] = nodeInfo[children.get(i)].remain;
        }
        
        int nt = beavers[u] - 1;
        if (nt < n) {
            Arrays.sort(eaten);
            long eTotal = 0;
            for (int j = n-1; j >= n-nt; j--) {
                eTotal += eaten[j];
            }
            nodeInfo[u] = new NodeInfo(eTotal + 1 + nt, 0);
        } else {
            long eTotal = 0;
            long rTotal = 0;
            for (int j = 0; j < n; j++) {
                eTotal += eaten[j];
                rTotal += remain[j];
            }
            
            nodeInfo[u] = new NodeInfo(eTotal + 1 + n + 2 * Math.min(nt - n, rTotal),
                                       Math.max(nt -n - rTotal, 0));
        }
    }
    
    private void solve() {
        TreeMap<Integer, ArrayList<Integer>> nodeByDepth =
            new TreeMap<Integer, ArrayList<Integer>>();
        for (int i = 0; i < N; i++) {
            int d = depth[i];
            if (!nodeByDepth.containsKey(d)) {
                nodeByDepth.put(d, new ArrayList<Integer>());
            }
            nodeByDepth.get(d).add(i);
        }
        
        for (int d: nodeByDepth.descendingKeySet()) {
            for (int u: nodeByDepth.get(d)) {
                visit(u);
            }
        }
    }
    
    public P077C() {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        
        depth   = new int[N];
        beavers = new int[N];
        for (int i = 0; i < N; i++) {
            beavers[i] = sc.nextInt();
        }
        
        ArrayList<ArrayList<Integer>> adj = new ArrayList<ArrayList<Integer>>();
        for (int i = 0; i < N; i++) {
            adj.add(new ArrayList<Integer>());
        }
        for (int i = 0; i < N-1; i++) {
            int u = sc.nextInt() - 1;
            int v = sc.nextInt() - 1;
            adj.get(u).add(v);
            adj.get(v).add(u);
        }
        
        int root = sc.nextInt() - 1;
        
        for (int i = 0; i < N; i++) {
            tree.add(new ArrayList<Integer>());
        }
        
        boolean[] visited = new boolean[N];
        java.util.Queue<Integer> queue = new ArrayDeque<Integer>();
        queue.add(root);
        visited[root] = true;
        depth[root] = 0;
        
        while (!queue.isEmpty()) {
            int u = queue.poll();
            for (int v: adj.get(u)) {
                if (visited[v]) continue;
                tree.get(u).add(v);
                queue.add(v);
                visited[v] = true;
                depth[v] = depth[u] + 1;
            }
        }
        
        // add 1 beaver to root will make it easier
        beavers[root]++;
        
        nodeInfo = new NodeInfo[N];
        
        solve();
        
        System.out.println(nodeInfo[root].eaten-1);
    }
    
    public static void main(String[] args) {
        P077C solution = new P077C();
    }      
        
}
            
        
        
        
        