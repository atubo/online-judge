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
        private HashMap<Integer, HashSet<Integer>> edges = new HashMap<Integer, HashSet<Integer>>();
        private final int N;
        
        public Graph(int N) {
            this.N = N;
            for (int i = 0; i < N; i++) {
                edges.put(i, new HashSet<Integer>());
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
            Arrays.sort(a, new Comparator<Integer>() {
                public int compare(Integer i, Integer j) {
                    if (nodes[i].depth > nodes[j].depth) return -1;
                    if (nodes[i].depth < nodes[j].depth) return 1;
                    return 0;
                }
            });
            for (int u: a) {
                nodes[u].isAffected = true;
                int v = u;
                while (v != -1 && nodes[v].depthMax < nodes[u].depth) {
                    nodes[v].depthMax = nodes[u].depth;
                    v = nodes[v].father;
                }
            }
        }
    }
    
    private Tree tree;
    private final int D;
    private int possible = 0;
    
    private void inspect(int u, int distMax) {
        if (distMax > D) return;
        
        Node node = tree.nodes[u];
        if ((node.depthMax - node.depth) <= D) {
            possible++;
        }
        
        Integer[] children = new Integer[node.children.size()];
        children = node.children.toArray(children);
        Arrays.sort(children, new Comparator<Integer>() {
            public int compare(Integer i, Integer j) {
                if (tree.nodes[i].depthMax > tree.nodes[j].depthMax) return -1;
                if (tree.nodes[i].depthMax < tree.nodes[j].depthMax) return 1;
                return 0;
            }
        });
        

        for (int v: node.children) {
            int d1 = -1;
            if (children.length > 1) {
                if (v == children[0]) {
                    d1 = tree.nodes[children[1]].depthMax;
                } else {
                    d1 = tree.nodes[children[0]].depthMax;
                }
            }
            if (d1 > -1) {
                d1 = d1 - node.depth + 1;
            }
            int d2 = (distMax > -1 ? distMax + 1 : -1);
            int d3 = (node.isAffected ? 1 : -1);
            
            inspect(v, Math.max(d1, Math.max(d2, d3)));
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
        inspect(0, -1);
        
        System.out.println(possible);
    }
    
    public static void main(String[] args) {
        P337D solution = new P337D();
    }       
}
            

            
        