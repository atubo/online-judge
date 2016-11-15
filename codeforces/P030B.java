import java.util.*;


public class P030B {
    private static int[] numOfDaysNormYear = new int[]{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    private static int[] numOfDaysLeapYear = new int[]{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    private static class Date {
        private final int year;
        private final int month;
        private final int day;

        
        public Date(int year, int month, int day) {
            this.year  = year;
            this.month = month;
            this.day   = day;
        }
        
        public boolean isLegal() {
            return monthIsLegal() && dayIsLegal();
        }
        
        public boolean eighteenYearsEarlier(Date other) {
            if (other.year < 19) return false;
            Date deadline = new Date(other.year - 18, other.month, other.day);
            return earlierThan(deadline);
        }
        
        private boolean earlierThan(Date other) {
            return year < other.year || year == other.year && month < other.month ||
                year == other.year && month == other.month && day <= other.day;
        }
        
        private boolean monthIsLegal() {
            return 1 <= month && month <= 12;
        }
        
        private boolean dayIsLegal() {
            if (year % 4 == 0) {
                return day <= numOfDaysLeapYear[month];
            }
            else {
                return day <= numOfDaysNormYear[month];
            }
        }
    }
    
    private final int[] field;
    private final Date finalDate;
    
    private boolean solve() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    if (i == j || j == k || i == k) continue;
                    Date date = new Date(field[i], field[j], field[k]);
                    if (date.isLegal() && date.eighteenYearsEarlier(finalDate)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    ArrayList<Integer> getFields(String s) {
        String[] strFields = s.split("\\.");
        ArrayList<Integer> result = new ArrayList<Integer>();
        for (int i = 0; i < 3; i++) {
            result.add(Integer.parseInt(strFields[i]));
        }
        return result;
    }
    
    public P030B() {
        Scanner sc = new Scanner(System.in);
        String s1 = sc.next();
        String s2 = sc.next();
        ArrayList<Integer> s1Fields = getFields(s1);
        finalDate = new Date(s1Fields.get(2), s1Fields.get(1), s1Fields.get(0));
        ArrayList<Integer> s2Fields = getFields(s2);
        field = new int[3];
        field[0] = s2Fields.get(0);
        field[1] = s2Fields.get(1);
        field[2] = s2Fields.get(2);
        
        boolean success = solve();
        System.out.println(success ? "YES" : "NO");
    }
    
    public static void main(String[] args) {
        P030B solution = new P030B();
    }
}
