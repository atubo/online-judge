import java.util.*;

public class P002A {
    private class Round {
        public int index;
        public int points;
        public Round(int index, int points) {
            this.index = index;
            this.points = points;
        }
    }
    
    public static void main(String[] argv) {
        P002A solution = new P002A();
        solution.solve();
    }
        
    public void solve() {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
                
        int maxScore = -1;
        for (int i = 0; i < n; i++) {
            String name = sc.next();
            int score = sc.nextInt();
            if (!currentScores.containsKey(name)) {
                currentScores.put(name, 0);
                players.put(name, new ArrayList<Round>());
            }
            currentScores.put(name, currentScores.get(name) + score);
            players.get(name).add(new Round(i, score));
        }
        for (Map.Entry<String, Integer> entry : currentScores.entrySet()) {
                maxScore = Math.max(maxScore, entry.getValue());
        }
        
        //System.out.printf("maxScore = %d\n", maxScore);
        Set<String> candidates = getCandidates(maxScore);
        /*for (String c : candidates) {
            System.out.printf("candidate: %s\n", c);
        }*/

        String winner = findWinner(candidates, maxScore);
        System.out.printf("%s\n", winner);
    }
    
    private Set<String> getCandidates(int maxScore) {
        Set<String> candidates = new HashSet<String>();
        for (Map.Entry<String, Integer> entry : currentScores.entrySet()) {
            if (entry.getValue() == maxScore) {
                candidates.add(entry.getKey());
            }
        }
        return candidates;
    }
    
    private int checkCandidate(ArrayList<Round> player, int maxScore) {
        int accu = 0;
        for (int i = 0; i < player.size(); i++) {
            accu += player.get(i).points;
            if (accu >= maxScore) {
                return player.get(i).index;
            }
        }
        assert(false);
        return Integer.MAX_VALUE;
    }
    
    private String findWinner(Set<String> candidates, int maxScore) {
        String winner = null;
        int minIndex = Integer.MAX_VALUE;
        for (String c : candidates) {
            int index = checkCandidate(players.get(c), maxScore);
            if (index < minIndex) {
                winner = c;
                minIndex = index;
            }
        }
        return winner;
    }
    
    private HashMap<String, Integer> currentScores = new HashMap<String, Integer>();
    private HashMap<String, ArrayList<Round> > players = new HashMap<String, ArrayList<Round> >();
    
}
            