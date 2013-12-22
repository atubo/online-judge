import java.util.*;

public class P359D {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        final int[] a = new int[N];
        Integer[] pos = new Integer[N];
        boolean[] visited = new boolean[N];
        for (int i = 0; i < N; i++) {
            a[i] = sc.nextInt();
            pos[i] = i;
            visited[i] = false;
        }
        Arrays.sort(pos, new Comparator<Integer>() {
            public int compare(Integer i, Integer j) {
                if (a[i] < a[j]) return -1;
                if (a[i] > a[j]) return 1;
                return 0;
            }
        });
        
        TreeMap<Integer, TreeSet<Integer>>  pairs = new TreeMap<Integer, TreeSet<Integer>>();
        
        for (int j: pos) {
            if (visited[j]) continue;
            int l = j;
            int r = j;
            while (l >= 0 && a[l] % a[j] == 0) {
                visited[l] = true;
                l--;
            }
            l++;
            while (r < N && a[r] % a[j] == 0) {
                visited[r] = true;
                r++;
            }
            r--;
            if (!pairs.containsKey(r-l)) {
                pairs.put(r-l, new TreeSet<Integer>());
            }
            pairs.get(r-l).add(l);
        }
        
        Map.Entry<Integer, TreeSet<Integer>> entry = pairs.lastEntry();
        int key = entry.getKey();
        TreeSet<Integer> value = entry.getValue();
        
        System.out.printf("%d %d\n", value.size(), key);
        for (int l: value) {
            System.out.printf("%d ", l + 1);
        }
        System.out.println();      
    }
}