import java.util.*;

public class P034C {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String s = sc.next().replace(',', ' ');
        sc = new Scanner(s);

        TreeSet<Integer> set = new TreeSet<Integer>();
        while (sc.hasNextInt()) {
            set.add(sc.nextInt());
        }
        
        while (true) {
            int first = set.pollFirst();
            if (!set.contains(first + 1)) {
                System.out.print(first);
            } else {
                int last = first + 1;
                while (set.contains(last)) {
                    set.remove(last);
                    last++;
                }
                System.out.printf("%d-%d", first, last-1);
            }
            if (set.isEmpty()) {
                break;
            } else {
                System.out.print(",");
            }
        }
    }
}
        