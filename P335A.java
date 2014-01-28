import java.util.*;

public class P335A {
    private static class Letter implements Comparable<Letter> {
        char c;
        int total;
        int occu;
        
        public Letter(char c, int total, int occu) {
            this.c     = c;
            this.total = total;
            this.occu  = occu;
        }
        
        @Override
        public int compareTo(Letter other) {
            float x1 = (float)total/occu;
            float x2 = (float)(other.total)/other.occu;
            
            if (x1 > x2) return -1;
            if (x1 < x2) return 1;
            if (c < other.c) return -1;
            if (c > other.c) return 1;
            return 0;
        }
    }
            
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String s = sc.next();
        final int N = sc.nextInt();
        
        HashMap<Character, Integer> count = new HashMap<Character, Integer>();
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (!count.containsKey(c)) {
                count.put(c, 0);
            }
            count.put(c, count.get(c) + 1);
        }
        
        int m = count.size();
        if (m > N) {
            System.out.println(-1);
            return;
        }
        
        PriorityQueue<Letter> queue = new PriorityQueue<Letter>();
        int[] occupied = new int[26];
        for (char c: count.keySet()) {
            occupied[c-'a'] = 1;
            queue.add(new Letter(c, count.get(c), 1));
        }
        
        for (int i = 0; i < N - m; i++) {
            Letter letter = queue.poll();
            occupied[letter.c-'a']++;
            queue.add(new Letter(letter.c, letter.total, letter.occu + 1));
        }
        
        Letter letter = queue.poll();
        if (letter.total % letter.occu == 0) {
            System.out.println(letter.total/letter.occu);
        } else {
            System.out.println(letter.total/letter.occu + 1);
        }
        
        StringBuilder sb = new StringBuilder();
        for (char c: count.keySet()) {
            for (int i = 0; i < occupied[c-'a']; i++) {
                sb.append(c);
            }
        }
        System.out.println(sb.toString());
    }
}
        
        
        
        