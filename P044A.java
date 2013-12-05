import java.util.*;

public class P044A {
    private static class Key {
        private String specie;
        private String color;
        
        public Key(String specie, String color) {
            this.specie = specie;
            this.color  = color;
        }
        
        public int hashCode() {
            return 37 * specie.hashCode() + color.hashCode();
        }
        
        public boolean equals(Object other) {
            if (other instanceof Key) {
                Key otherKey = (Key) other;
                return specie.equals(otherKey.specie) && color.equals(otherKey.color);
            }
            
            return false;
        }
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        HashSet<Key> collected = new HashSet<Key>();
        for (int i = 0; i < n; i++) {
            String specie = sc.next();
            String color  = sc.next();
            collected.add(new Key(specie, color));
        }
        
        System.out.println(collected.size());
    }
}