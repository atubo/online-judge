import java.util.*;

public class P335B {
    private int[] markPrev;
    private int[] markCurr;
    private int[] next;
    private final String s;
    private ArrayList<TreeSet<Integer>> letterPos = new ArrayList<TreeSet<Integer>>();
    
    private void process(int pos) {
        char c = s.charAt(pos);
        TreeSet<Integer> letterPosSet = letterPos.get(c - 'a');
        letterPosSet.add(pos);
        
        markCurr[0] = pos + 1;
        markCurr[1] = pos;
        
        for (int len = 2; len <= 100; len++) {
            int mj = markPrev[len-2];
            Integer oppo = letterPosSet.floor(mj - 1);
            if (oppo == null || oppo <= markPrev[len]) {
                markCurr[len] = markPrev[len];
                continue;
            }
            markCurr[len] = oppo;
            next[oppo] = mj;
        }
        
        int[] temp = markPrev;
        markPrev   = markCurr;
        markCurr   = temp;
    }
    
    public P335B() {
        Scanner sc = new Scanner(System.in);
        s = sc.next();
        final int N = s.length();
        markPrev = new int[101];
        markCurr = new int[101];
        for (int i = 0; i < 101; i++) {
            markPrev[i] = markCurr[i] = -1;
        }
        
        next = new int[N];
        for (int i = 0; i < N; i++) {
            next[i] = -1;
        }
        
        for (int i = 0; i < 26; i++) {
            letterPos.add(new TreeSet<Integer>());
        }
        
        for (int i = 0; i < N; i++) {
            process(i);
            if (markPrev[100] >= 0) {
                break;
            }
        }
        
        int pos = -1;
        int length = 0;
        for (int i = 100; i >= 1; i--) {
            if (markPrev[i] >= 0) {
                pos    = markPrev[i];
                length = i;
                break;
            }
        }
        
        char[] result = new char[length];
        for (int i = 0; i < (length+1)/2; i++) {
            result[i] = result[length-i-1] = s.charAt(pos);
            pos = next[pos];
        }
        
        for (int i = 0; i < length; i++) {
            System.out.printf("%c", result[i]);
        }
        System.out.println();
    }
    
    public static void main(String[] args) {
        P335B solution = new P335B();
    }
}
        
        
        