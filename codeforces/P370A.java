import java.util.*;

public class P370A {
    private final int r1;
    private final int c1;
    private final int r2;
    private final int c2;
    
    private int rookMoves() {
        if (r1 == r2 || c1 == c2) {
            return 1;
        } else {
            return 2;
        }
    }
    
    private int bishopMoves() {
        if ((r1 + c1) % 2 != (r2 + c2) % 2) {
            return 0;
        }
        if (Math.abs(r1-r2) == Math.abs(c1-c2)) {
            return 1;
        } else {
            return 2;
        }
    }
    
    private int kingMoves() {
        return Math.max(Math.abs(r1-r2), Math.abs(c1-c2));
    }
    
    public P370A() {
        Scanner sc = new Scanner(System.in);
        r1 = sc.nextInt();
        c1 = sc.nextInt();
        r2 = sc.nextInt();
        c2 = sc.nextInt();
        
        System.out.printf("%d %d %d\n", rookMoves(), bishopMoves(), kingMoves());
    }
    
    public static void main(String[] args) {
        P370A solution = new P370A();
    }
}