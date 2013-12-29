import java.util.*;

public class P337E {
    private static ArrayList<Integer> primes = new ArrayList<Integer>();
    
    private static void sieve() {
        final int N = 1000003;
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

    private static int getNumPrimes(long x) {
        int result = 0;

        for (int prime: primes) {
            while (x % prime == 0) {
                result++;
                x = x / prime;
            }
            if (x == 1) break;
        }
        
        if (x != 1) result++;
        
        return result;
    }
    
    private static class Node {
        private long x;
        private int numNodes;
        private int numPrimes;
        
        public Node(long x, int numNodes, int numPrimes) {
            this.x         = x;
            this.numNodes  = numNodes;
            this.numPrimes = numPrimes;
        }
    }
    
    private static ArrayList<Node> buildForest(long x, ArrayList<Node> nodes) {
        int numPrimes = getNumPrimes(x);

        ArrayList<Node> result = new ArrayList<Node>();
        if (nodes.isEmpty()) {
            int nnode = (numPrimes == 1 ? numPrimes : numPrimes + 1);
            result.add(new Node(x, nnode, numPrimes));
            return result;
        }
        
        final int N = nodes.size();

        int total = 0;
        for (Node node: nodes) {
            total += node.numNodes;
        }
        total += numPrimes + 1;
        
        int numNodes = total;
        HashSet<Integer> subtreeNodes = new HashSet<Integer>();
        
        int s = 1;
        HashSet<Integer> selected = new HashSet<Integer>();
        while (s < (1 << N)) {
            int numNodesCurr = total;
            selected.clear();
            long xtmp = x;
            boolean found = true;
            for (int i = 0; i < N; i++) {
                if ((s & (1 << i)) != 0) {
                    if (xtmp % nodes.get(i).x != 0) {
                        found = false;
                        break;
                    }
                    xtmp = xtmp / nodes.get(i).x;
                    numNodesCurr -= nodes.get(i).numPrimes;
                    selected.add(i);
                }
            }
            s++;
            if (!found) continue;
            if (numNodesCurr < numNodes) {
                numNodes = numNodesCurr;
                subtreeNodes.clear();
                subtreeNodes.addAll(selected);
            }
        }
        
        numNodes = 1 + numPrimes;
        for (int i: subtreeNodes) {
            numNodes += nodes.get(i).numNodes - nodes.get(i).numPrimes;
        }
        
        result.add(new Node(x, numNodes, numPrimes));
        for (int i = 0; i < N; i++) {
            if (!subtreeNodes.contains(i)) {
                result.add(nodes.get(i));
            }
        }
        
        return result;
    }
    
    public static void main(String[] args) {
        sieve();
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        long[] a = new long[N];
        for (int i = 0; i < N; i++) {
            a[i] = sc.nextLong();
        }
        Arrays.sort(a);
        ArrayList<Node> nodes = new ArrayList<Node>();
        for (int i = 0; i < N; i++) {
            ArrayList<Node> divisible = new ArrayList<Node>();
            for (int j = nodes.size() - 1; j >= 0; j--) {
                if (a[i] % nodes.get(j).x == 0) {
                    divisible.add(nodes.get(j));
                    nodes.remove(j);
                }
            }
            ArrayList<Node> forest = buildForest(a[i], divisible);
            for (Node node: forest) {
                nodes.add(node);
            }
        }
        
        int numNodes = 0;
        for (Node node: nodes) {
            numNodes += node.numNodes;
        }
        
        if (nodes.size() > 1) {
            numNodes++;
        }
        
        System.out.println(numNodes);
    }
}

