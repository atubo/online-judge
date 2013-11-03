import java.util.*;
import java.io.*;

public class P035E {
    private static class Segment implements Comparable<Segment> {
        private final int height;
        private final int left;
        private final int right;
        
        public Segment(int height, int left, int right) {
            this.height = height;
            this.left   = left;
            this.right  = right;
        }
        
        public int compareTo(Segment other) {
            // From top to bottom and left to right
            if      (height > other.height) return -1;
            else if (height < other.height) return 1;
            else if (left < other.left) return -1;
            else if (left > other.left) return 1;
            else if (right < other.right) return -1;
            else if (right > other.right) return 1;
            else                          return 0;
        }
        
        public String toString() {
            return String.format("Segment: %d %d %d\n", height, left, right);
        }
    }
    
    private static class Vertex implements Comparable<Vertex> {
        private final int x;
        private final int y;
        private final int type; // 0 - left, 1 - right
        private Vertex next;
        
        public Vertex(int x, int y, int type) {
            this.x    = x;
            this.y    = y;
            this.type = type;
        }
        
        public int compareTo(Vertex other) {
            // left -> right, top - > bottom, rightend -> leftend
            if      (x < other.x) return -1;
            else if (x > other.x) return 1;
            else if (y > other.y) return -1;
            else if (y < other.y) return 1;
            else if (type > other.type) return -1;
            else if (type < other.type) return 1;
            else                        return 0;
        }
        
        public String toString() {
            return String.format("Vertex: %d %d %d\n", x, y, type);
        }
    }
    
    private Segment[] segments;
    private TreeSet<Vertex> vertices = new TreeSet<Vertex>();
    
    private Vertex process() {
        Vertex vStart = null;
        for (Segment s: segments) {
            Vertex v1 = new Vertex(s.left, s.height, 0);
            Vertex v2 = new Vertex(s.right, s.height, 1);
            
            if (vStart == null || vStart.x > v1.x) vStart = v1;
            
            Vertex toAppend = null;
            Vertex vCurr = null;
            if (!vertices.contains(v1)) {
                Vertex vPrev = vertices.lower(v1);
                if (vPrev == null) {
                    vertices.add(v1);
                    toAppend = v1;
                    vCurr = vertices.higher(v1);
                }
                else if (vPrev.type == 0 && vPrev.x == v1.x) {
                    v1.next = vPrev;
                    vertices.remove(vPrev);
                    vertices.add(v1);
                    vCurr = vertices.higher(v1);
                }
                else if (vPrev.type == 0 && vPrev.x < v1.x) {
                    vCurr = vertices.higher(v1);
                }
                else if (vPrev.type == 1 && vPrev.x == v1.x) {
                    assert vPrev.next == null;
                    vPrev.next = v1;
                    vertices.remove(vPrev);
                    toAppend = v1;
                    vCurr = vertices.higher(v1);
                }
                else if (vPrev.type == 1 && vPrev.x < v1.x) {
                    vertices.add(v1);
                    toAppend = v1;
                    vCurr = vertices.higher(v1);
                }
                else {
                    assert false;
                }
            }
            else {
                vCurr = vertices.higher(v1);
            }
            
            while (vCurr != null && vCurr.x < v2.x) {
                if (vCurr.type == 0) {
                    assert toAppend != null;
                    if (vCurr.y == toAppend.y) {
                        toAppend.next = vCurr;
                    }
                    else {
                        Vertex vtmp = new Vertex(vCurr.x, toAppend.y, 0);
                        toAppend.next = vtmp;
                        vtmp.next = vCurr;
                    }
                    vertices.remove(vCurr);
                    toAppend = null;
                }
                else {
                    assert toAppend == null;
                    assert vCurr.next == null;
                    if (vCurr.y == v1.y) {
                        toAppend = vCurr;
                    }
                    else {
                        Vertex vtmp = new Vertex(vCurr.x, v1.y, 1);
                        vCurr.next = vtmp;
                        toAppend = vtmp;
                    }
                    vertices.remove(vCurr);
                }
                vCurr = vertices.higher(vCurr);
            }
            
            if (vCurr == null) {
                assert toAppend != null;
                toAppend.next = v2;
                vertices.add(v2);
            }
            else if (vCurr.x == v2.x) {
                assert vCurr.y >= v2.y;

                if (vCurr.y > v2.y) {
                    if (vCurr.type == 0) {
                        assert toAppend != null;
                        toAppend.next = v2;
                        v2.next = vCurr;
                        vertices.remove(vCurr);
                    }
                    else {
                        assert toAppend == null;
                        assert vCurr.next == null;
                        vCurr.next = v2;
                        vertices.remove(vCurr);
                        vertices.add(v2);
                    }
                }
                else if (vCurr.type == 0) {
                    assert toAppend != null;
                    toAppend.next = vCurr;
                    vertices.remove(vCurr);
                }
            }
            else if (vCurr.type == 0) {
                assert toAppend != null;
                toAppend.next = v2;
                vertices.add(v2);
            }
            
        }
        
        return vStart;
    }
    
    private int orient(Vertex v1, Vertex v2) {
        // 0 - horizontal, 1 - vertical
        assert (v1.x == v2.x || v1.y == v2.y);
        assert !(v1.x == v2.x && v1.y == v2.y);
        if (v1.y == v2.y) return 0;
        else              return 1;
    }
    
    private void normalize(Vertex v0) {
        Vertex prev = v0;
        Vertex curr = v0.next;
        
        // first pass removes all duplicates
        while (curr != null) {
            if (curr.x == prev.x && curr.y == prev.y) {
                prev.next = curr = curr.next;
            }
            else {
                prev = curr;
                curr = curr.next;
            }
        }
        
        // second pass removes collinear points
        prev = v0;
        curr = v0.next;
        while (curr.next != null) {
            if (orient(prev, curr) == orient(curr, curr.next)) {
                prev.next = curr = curr.next;
            }
            else {
                prev = curr;
                curr = curr.next;
            }
        }
    }
        
        
    private void solve() {
        try {
            Scanner sc = new Scanner(new File("input.txt"));
            int n = sc.nextInt();
            segments = new Segment[n+1];
            
            int MAX_VAL = 1000000001;
            for (int i = 0; i < n; i++) {
                int h = sc.nextInt();
                int l = sc.nextInt();
                int r = sc.nextInt();
                segments[i] = new Segment(h, l, r);
            }
            segments[n] = new Segment(0, -MAX_VAL, MAX_VAL);
            Arrays.sort(segments);
                        
            Vertex v = process();
            normalize(v);
            
            ArrayList<Vertex> result = new ArrayList<Vertex>();
            while (v != null) {
                if (Math.abs(v.x) != MAX_VAL) {
                    result.add(v);
                }
                v = v.next;
            }
            
            PrintWriter writer = new PrintWriter("output.txt", "UTF-8");
            writer.println(result.size());
            for (int i = 0; i < result.size(); i++) {
                writer.printf("%d %d\n", result.get(i).x, result.get(i).y);
            }
            writer.close();
        }
        catch (FileNotFoundException e) {
            System.out.println("File not found");
        }
        catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
    }
    
    public P035E() {
        solve();
    }
    
    public static void main(String[] args) {
        P035E solution = new P035E();
    }
}
            
            

            