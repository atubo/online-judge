import java.util.*;

public class P335B {
    private static class Link {
        private final int pos;
        private final int index;
        
        public Link(int pos, int index) {
            this.pos   = pos;
            this.index = index;
        }
    }
    
    private int[] markPrev;
    private int[] markCurr;
    private ArrayList<ArrayList<Link>> next;
    private final String s;
    private ArrayList<TreeSet<Integer>> letterPos = new ArrayList<TreeSet<Integer>>();
    
    private void process(int pos) {
        char c = s.charAt(pos);
        TreeSet<Integer> letterPosSet = letterPos.get(c - 'a');
        letterPosSet.add(pos);
        
        for (int len = 100; len >= 2; len--) {
            int mj = markPrev[len-2];
            Integer oppo = letterPosSet.floor(mj - 1);
            if (oppo == null || oppo <= markPrev[len]) {
                markCurr[len] = markPrev[len];
                continue;
            }
            markCurr[len] = oppo;
            putTail(len, oppo, next.get(len-2).size()-1);
        }
        
        markCurr[1] = pos;
        putTail(1, pos, -1);
        markCurr[0] = pos + 1;
        putTail(0, pos + 1, -1);
        
        int[] temp = markPrev;
        markPrev   = markCurr;
        markCurr   = temp;
    }
    
    private void putTail(int length, int pos, int index) {
        next.get(length).add(new Link(pos, index));
    }
    
    private Link getTail(int length) {
        ArrayList<Link> list = next.get(length);
        return list.get(list.size()-1);
    }
    
    private Link getLink(int length, int index) {
        return next.get(length).get(index);
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
        
        next = new ArrayList<ArrayList<Link>>();
        for (int i = 0; i < 101; i++) {
            next.add(new ArrayList<Link>());
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
        
        int length = 0;
        for (int i = 100; i >= 1; i--) {
            if (markPrev[i] >= 0) {
                length = i;
                break;
            }
        }
        
        Link link = getTail(length);
        char[] result = new char[length];
        int len = length;
        int pos = link.pos;
        result[0] = result[length-1] = s.charAt(pos);
        for (int i = 1; i < (length+1)/2; i++) {
            len -= 2;
            link = getLink(len, link.index);
            pos = link.pos;
            result[i] = result[length-i-1] = s.charAt(pos);
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
        
        
        