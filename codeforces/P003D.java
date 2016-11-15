import java.util.*;

public class P003D {
    private static class RightBracket implements Comparable<RightBracket> {
        private int cost;
        private int pos;
        
        public RightBracket(int cost, int pos) {
            this.cost = cost;
            this.pos  = pos;
        }
        
        public int compareTo(RightBracket other) {
            return cost - other.cost;
        }
    }
    
    private static class Cost {
        private int openCost;
        private int closeCost;
        
        public Cost(int openCost, int closeCost) {
            this.openCost  = openCost;
            this.closeCost = closeCost;
        }
    }
        
    
    private String pattern = new String();
    private StringBuilder resultBuilder = new StringBuilder();
    
    private PriorityQueue<RightBracket> rBrackets = new PriorityQueue<RightBracket>();
    private ArrayList<Cost> bracketCosts = new ArrayList<Cost>();
    
    private long totalCost;
    
    private boolean replace() {
        if (rBrackets.isEmpty()) return false;
        RightBracket bracket = rBrackets.poll();
        resultBuilder.setCharAt(bracket.pos, '(');
        totalCost += bracket.cost;
        return true;
    }        
    
    public boolean solve() {
        Scanner sc = new Scanner(System.in);
        pattern = sc.next();
        
        while (sc.hasNext()) {
            int openCost  = sc.nextInt();
            int closeCost = sc.nextInt();
            bracketCosts.add(new Cost(openCost, closeCost));
        }
        
        int currIndex = 0;
        int balance   = 0;
        totalCost     = 0;
        for (int i = 0; i < pattern.length(); i++) {
            char c = pattern.charAt(i);
            if (c != '?') {
                resultBuilder.append(c);
                if (c == '(') balance++;
                else          balance--;
                assert balance >= -1;
                if (balance < 0) {
                    boolean status = replace();
                    if (!status) return false;
                    balance += 2;
                }
                continue;
            }
            resultBuilder.append(')');
            Cost cost = bracketCosts.get(currIndex++);
            rBrackets.add(new RightBracket(cost.openCost - cost.closeCost, i));
            totalCost += cost.closeCost;
            balance--;
            assert balance >= -1;
            
            if (balance < 0) {
                boolean status = replace();
                if (!status) return false;
                balance += 2;
            }
        }
        
        if (balance != 0) return false;
        
        System.out.printf("%d\n%s\n", totalCost, resultBuilder.toString());
        return true;
    }
    
    public static void main(String[] argv) {
        P003D solution = new P003D();
        boolean status = solution.solve();
        if (!status) {
            System.out.printf("-1\n");
        }
    }
}