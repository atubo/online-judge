import java.util.*;

public class P370C {
    private static class Mitten implements Comparable<Mitten> {
        private final int color;
        private int number;
        
        public Mitten(int color, int number) {
            this.color  = color;
            this.number = number;
        }
        
        @Override
        public int compareTo(Mitten other) {
            if (number > other.number) return -1;
            if (number < other.number) return 1;
            if (color < other.color) return -1;
            if (color > other.color) return 1;
            return 0;
        }
    }
    
    public static void pairMittens(ArrayList<Mitten> mittens) {
        if (mittens.size() == 0) return;
        
        int c0 = mittens.get(0).color;
        for (int i = 1; i < mittens.size(); i++) {
            Mitten m = mittens.get(i);
            for (int j = 0; j < m.number; j++) {
                System.out.printf("%d %d\n", c0, m.color);
                System.out.printf("%d %d\n", m.color, c0);
            }
        }
    }
    
    public static void cascade(ArrayList<Mitten> mittens) {
        int cPrev = mittens.get(0).color;
        for (int i = mittens.size() - 1; i >= 0; i--) {
            Mitten m = mittens.get(i);
            System.out.printf("%d %d\n", m.color, cPrev);
            cPrev = m.color;
            m.number--;
            if (m.number == 0) {
                mittens.remove(i);
            }
        }
    }
    
    public static void cascade(ArrayList<Mitten> mittens, int t) {
        int cPrev = mittens.get(0).color;
        int n = mittens.size() - 1;
        for (int i = n; i >= n-t+1; i--) {
            Mitten m = mittens.get(i);
            System.out.printf("%d %d\n", m.color, cPrev);
            cPrev = m.color;
            m.number--;
            if (m.number == 0) {
                mittens.remove(i);
            }
        }
        Mitten m0 = mittens.get(0);
        m0.number--;
        System.out.printf("%d %d\n", m0.color, cPrev);
    }
            
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        
        HashMap<Integer, Integer> colorNum = new HashMap<Integer, Integer>();
        for (int i = 0; i < n; i++) {
            int color = sc.nextInt();
            if (!colorNum.containsKey(color)) {
                colorNum.put(color, 0);
            }
            colorNum.put(color, colorNum.get(color)+1);
        }
        
        ArrayList<Mitten> mittens = new ArrayList<Mitten>();
        
        for (Map.Entry<Integer, Integer> entry: colorNum.entrySet()) {
            mittens.add(new Mitten(entry.getKey(), entry.getValue()));
        }
        
        Collections.sort(mittens);
        
        int n_max = mittens.get(0).number;
        int c_max = mittens.get(0).color;
        int n_t = 0;
        for (int i = 1; i < mittens.size(); i++) {
            n_t = n_t + mittens.get(i).number;
        }
        
        if (n_max >= n_t) {
            System.out.printf("%d\n", 2 * n_t);
            pairMittens(mittens);
            for (int i = 0; i < (n_max - n_t); i++) {
                System.out.printf("%d %d\n", c_max, c_max);
            }
            return;
        }
        
        System.out.printf("%d\n", n_max + n_t);
        int sz = mittens.size() - 1;
        while (n_t > n_max && n_t - n_max >= sz - 1) {
            cascade(mittens);
            n_max--;
            n_t -= sz;
            sz = mittens.size() - 1;
        }
        if (n_t > n_max) {
            int t = n_t - n_max + 1;
            cascade(mittens, t);
        }
        pairMittens(mittens);
    }
}