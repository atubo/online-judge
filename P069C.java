import java.util.*;
import java.util.regex.*;

public class P069C {
    private static class Node {
        private HashMap<Integer, Integer> out = new HashMap<Integer, Integer>();
        private HashMap<Integer, Integer> in  = new HashMap<Integer, Integer>();
        
        public void addOut(int dest, int weight) {
            out.put(dest, weight);
        }
        
        public void addIn(int src, int weight) {
            in.put(src, weight);
        }
    }
    
    private Node[] graph;
    private int[][] backpacks;
    private String[] itemNames;
    
    private boolean composeReady(int[] backpack, int item) {
        for (int src: graph[item].in.keySet()) {
            if (backpack[src] < graph[item].in.get(src)) {
                return false;
            }
        }
        return true;
    }
    
    private int canComposeFrom(int[] backpack, int item) {
        int result = -1;
        for (int dest: graph[item].out.keySet()) {
            if (backpack[item] < graph[item].out.get(dest)) {
                continue;
            }
            if (composeReady(backpack, dest)) {
                result = dest;
                break;
            }
        }
        return result;
    }
    
    private void compose(int[] backpack, int item) {
        backpack[item]++;
        for (int src: graph[item].in.keySet()) {
            backpack[src] -= graph[item].in.get(src);
        }
    }
    
    private void purchase(int player, int item) {
        int[] backpack = backpacks[player];
        backpack[item]++;
        int newComposite = canComposeFrom(backpack, item);
        while (newComposite >= 0) {
            compose(backpack, newComposite);
            newComposite = canComposeFrom(backpack, newComposite);
        }
    }
    
    public P069C() {
        Scanner sc = new Scanner(System.in);
        final int K = sc.nextInt();
        final int N = sc.nextInt();
        final int M = sc.nextInt();
        final int Q = sc.nextInt();
        
        graph = new Node[M+N];
        for (int i = 0; i < M + N; i++) {
            graph[i] = new Node();
        }
        
        backpacks = new int[K][M+N];
        itemNames = new String[M+N];
        
        HashMap<String, Integer> dict = new HashMap<String, Integer>();
        for (int i = 0; i < N; i++) {
            String s = sc.next();
            dict.put(s, i);
            itemNames[i] = s;
        }
        
        sc.nextLine();
        for (int i = 0; i < M; i++) {
            String s = sc.nextLine();
            Pattern p = Pattern.compile("^(\\w+): (.*)$");
            Matcher m = p.matcher(s);
            if (m.find()) {
                int artId = i + N;
                String c = m.group(1);
                dict.put(c, artId);
                itemNames[artId] = c;
                String components = m.group(2);
                Pattern p2 = Pattern.compile("(\\w+) ([0-9]+)");
                Matcher m2 = p2.matcher(components);
                while (m2.find()) {
                    String comp = m2.group(1);
                    String quant = m2.group(2);
                    int componentId = dict.get(comp);
                    int quantity    = Integer.parseInt(quant);
                    graph[componentId].addOut(artId, quantity);
                    graph[artId].addIn(componentId, quantity);
                }
            } else {
                assert false;
            }
        }
        
        for (int i = 0; i < Q; i++) {
            int player = sc.nextInt() - 1;
            String item = sc.next();
            int itemId = dict.get(item);
            purchase(player, itemId);
        }
        
        TreeMap<String, Integer> output = new TreeMap<String, Integer>();
        for (int player = 0; player < K; player++) {
            for (int item = 0; item < M + N; item++) {
                int itemNum = backpacks[player][item];
                if (itemNum > 0) {
                    output.put(itemNames[item], itemNum);
                }
            }
            System.out.println(output.size());
            for (Map.Entry<String, Integer> entry: output.entrySet()) {
                System.out.printf("%s %d\n", entry.getKey(), entry.getValue());
            }
            output.clear(); 
        }
    }
    
    public static void main(String[] args) {
        P069C solution = new P069C();
    }
}
    
    