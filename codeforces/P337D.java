import java.util.*;

public class P337D {
    private static class Node {
        private final int id;
        private int father;
        private int depth;
        private HashSet<Integer> children = new HashSet<Integer>();
        
        private int depthMax;  // max depth of affected node of its subtree
        private boolean isAffected;
        
        public Node(int id) {
            this.id = id;
            this.depthMax  = -1;
            this.isAffected = false;
        }
    }
    
    private static class Graph {
        private ArrayList<ArrayList<Integer>> edges = new ArrayList<ArrayList<Integer>>();
        private final int N;
        
        public Graph(int N) {
            this.N = N;
            for (int i = 0; i < N; i++) {
                edges.add(new ArrayList<Integer>());
            }
        }
        
        public void addEdge(int i, int j) {
            edges.get(i).add(j);
            edges.get(j).add(i);
        }
    }
    
    private static class Tree {
        private final int N;
        private final Node[] nodes;
        private final Node root;
        
        public Tree(Graph g) {
            this.N = g.N;
            nodes = new Node[N];
            for (int i = 0; i < N; i++) {
                nodes[i] = new Node(i);
            }
            root = nodes[0];  // node 0 is always the root
            root.depth = 0;
            root.father = -1;
            
            boolean[] visited = new boolean[N];
            
            java.util.Queue<Integer> queue = new ArrayDeque<Integer>();
            queue.add(0);
            visited[0] = true;
            
            while (!queue.isEmpty()) {
                int u = queue.poll();
                for (int v: g.edges.get(u)) {
                    if (!visited[v]) {
                        visited[v] = true;
                        queue.add(v);
                        nodes[v].father = u;
                        nodes[u].children.add(v);
                        nodes[v].depth = nodes[u].depth + 1;
                    }
                }
            }  
        }
        
        public void markAffected(Integer[] a) {
            TreeMap<Integer, ArrayList<Integer>> affected = new TreeMap<Integer, ArrayList<Integer>>();
            for (int x: a) {
                int d = - nodes[x].depth;
                if (!affected.containsKey(d)) {
                    affected.put(d, new ArrayList<Integer>());
                }
                affected.get(d).add(x);
            }
            for (int d: affected.keySet()) {
                for (int u: affected.get(d)) {
                    nodes[u].isAffected = true;
                    int v = u;
                    while (v != -1 && nodes[v].depthMax < nodes[u].depth) {
                        nodes[v].depthMax = nodes[u].depth;
                        v = nodes[v].father;
                    }
                }
            }
        }
    }
    
    private Tree tree;
    private final int D;
    private int possible = 0;
    
    private static class InspectItem {
        private final int u;
        private final int distMax;
        
        public InspectItem(int u, int distMax) {
            this.u       = u;
            this.distMax = distMax;
        }
    }
    
    private void inspect() {
        java.util.Queue<InspectItem> queue = new ArrayDeque<InspectItem>();
        queue.add(new InspectItem(0, -1));
        
        while (!queue.isEmpty()) {
            InspectItem item = queue.poll();
            int u       = item.u;
            int distMax = item.distMax;
            if (distMax > D) continue;
            
            Node node = tree.nodes[u];
            if ((node.depthMax - node.depth) <= D) {
                possible++;
            }
            
            int subtreeDepthMax = -1;
            int subtreeMaxDepthId = -1;
            int subtreeDepthNext = -1;
            for (int v: node.children) {
                if (tree.nodes[v].depthMax >= subtreeDepthMax) {
                    subtreeDepthNext = subtreeDepthMax;
                    subtreeDepthMax = tree.nodes[v].depthMax;
                    subtreeMaxDepthId = v;
                }
                else if (tree.nodes[v].depthMax > subtreeDepthNext) {
                    subtreeDepthNext = tree.nodes[v].depthMax;
                }
            }
            
            for (int v: node.children) {
                int d1 = (v == subtreeMaxDepthId ? subtreeDepthNext : subtreeDepthMax);
                if (d1 > -1) {
                    d1 = d1 - node.depth + 1;
                }
                int d2 = (distMax > -1 ? distMax + 1 : -1);
                int d3 = (node.isAffected ? 1 : -1);
                
                int d = Math.max(d1, Math.max(d2, d3));
                queue.add(new InspectItem(v, d));
            }
        }
    }
    
    public P337D() {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int M = sc.nextInt();
        D = sc.nextInt();
        
        Integer[] affected = new Integer[M];
        for (int i = 0; i < M; i++) {
            affected[i] = sc.nextInt() - 1;
        }
        
        Graph g = new Graph(N);
        
        for (int i = 0; i < N - 1; i++) {
            int u = sc.nextInt() - 1;
            int v = sc.nextInt() - 1;
            g.addEdge(u, v);
        }
        
        tree = new Tree(g);
        tree.markAffected(affected);
        inspect();
        
        System.out.println(possible);
    }
    
    public static void main(String[] args) {
        P337D solution = new P337D();
    }       
}
            

            
        