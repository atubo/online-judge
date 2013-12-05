import java.util.*;

public class P098A {
    private static class UnionFind {
        private final int N;
        private int[] rank;
        private int[] parent;
        
        public UnionFind(int n) {
            N = n;
            rank   = new int[n];
            parent = new int[n];
            
            for (int i = 0; i < n; i++) {
                makeSet(i);
            }
        }
        
        private void makeSet(int k) {
            assert 0 <= k && k < N;
            
            parent[k] = k;
            rank[k]   = 0;
        }
        
        public int find(int k) {
            if (parent[k] != k) {
                parent[k] = find(parent[k]);
            }
            return parent[k];
        }
        
        private void link(int u, int v) {
            if (rank[u] > rank[v]) {
                parent[v] = u;
            } else {
                parent[u] = v;
                if (rank[u] == rank[v]) {
                    rank[v]++;
                }
            }
        }
        
        public void join(int u, int v) {
            link(find(u), find(v));
        }
    }
    
    private HashMap<String, Integer> dec2Id = new HashMap<String, Integer>();
    private String gems;
    private UnionFind uf;
    
    private void permutation(int start, int end, StringBuilder sb) {
        if (start == end) {
            if (!dec2Id.containsKey(sb.toString())) {
                int id = dec2Id.size();
                dec2Id.put(sb.toString(), id);
            }
            return;
        }
        char c0 = sb.charAt(start);
        for (int i = start; i < end; i++) {
            char c1 = sb.charAt(i);
            sb.setCharAt(start, c1);
            sb.setCharAt(i, c0);
            permutation(start + 1, end, sb);
            sb.setCharAt(start, c0);
            sb.setCharAt(i, c1);
        }
    }
    
    private void solve() {
        StringBuilder sb = new StringBuilder(gems);
        permutation(0, 6, sb);
        
        int sz = dec2Id.size();
        uf = new UnionFind(sz);
        
        for (String s: dec2Id.keySet()) {
            rotateMerge(s);
        }
        
        HashSet<Integer> unique = new HashSet<Integer>();
        for (int i = 0; i < sz; i++) {
            unique.add(uf.find(i));
        }
        System.out.printf("%d\n", unique.size());
    }
    
    private void rotate1(StringBuilder sb) {
        char c0 = sb.charAt(0);
        char c3 = sb.charAt(3);
        char c5 = sb.charAt(5);
        char c1 = sb.charAt(1);
        
        sb.setCharAt(0, c1);
        sb.setCharAt(3, c0);
        sb.setCharAt(5, c3);
        sb.setCharAt(1, c5);
    }
    
    private void rotate2(StringBuilder sb) {
        char c1 = sb.charAt(1);
        char c2 = sb.charAt(2);
        char c3 = sb.charAt(3);
        char c4 = sb.charAt(4);
        
        sb.setCharAt(1, c4);
        sb.setCharAt(2, c1);
        sb.setCharAt(3, c2);
        sb.setCharAt(4, c3);
    }
    
    private void rotateMerge(String s0) {
        StringBuilder sb = new StringBuilder(s0);
        int id0 = dec2Id.get(s0);
        for (int i = 0; i < 3; i++) {
            rotate1(sb);
            String s1 = sb.toString();
            int id1 = dec2Id.get(s1);
            uf.join(id0, id1);
        }
        rotate1(sb);
        assert s0.equals(sb.toString());
        
        for (int i = 0; i < 3; i++) {
            rotate2(sb);
            String s1 = sb.toString();
            int id1 = dec2Id.get(s1);
            uf.join(id0, id1);
        }
    }
    
    public P098A() {
        Scanner sc = new Scanner(System.in);
        gems = sc.next();
        solve();
    }
    
    public static void main(String[] args) {
        P098A solution = new P098A();
    }
    
    
}
    