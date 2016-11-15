import java.util.*;

public class P081D {
    private static class Album implements Comparable<Album> {
        private final int id;
        private int size;
        
        public Album(int id, int size) {
            this.id   = id;
            this.size = size;
        }
        
        @Override
        public int compareTo(Album other) {
            if (this.size > other.size) return -1;
            if (this.size < other.size) return 1;
            if (this.id < other.id) return -1;
            if (this.id > other.id) return 1;
            return 0;
        }
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        Album[] a = new Album[m];
        int total = 0;
        for (int i = 0; i < m; i++) {
            int size = sc.nextInt();
            a[i] = new Album(i+1, Math.min(size, n/2));
            total += a[i].size;
        }
        Arrays.sort(a);
        
        if (total < n) {
            System.out.println(-1);
            return;
        }
        
        int[] result = new int[n];
        
        int aIndex = 0;
        int j = 0;
        while (j < n) {
            if (a[aIndex].size == 0) {
                aIndex++;
            }
            result[j] = a[aIndex].id;
            a[aIndex].size--;
            j += 2;
        }
        
        j = 1;
        while (j < n) {
            if (a[aIndex].size == 0) {
                aIndex++;
            }
            result[j] = a[aIndex].id;
            a[aIndex].size--;
            j += 2;
        }
        
        for (int x: result) {
            System.out.printf("%d ", x);
        }
        System.out.println();
    }
}