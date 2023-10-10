import java.util.TreeSet;
import java.util.Vector;

public class Main {

    private static Vector<Integer> unionVect(Vector<Integer> a, Vector<Integer> b) {
        Vector<Integer> c = new Vector<>(20);

        int pos = 0;

        for(int num : a) c.add(pos++, num);
        for(int num : b) c.add(pos++, num);

        TreeSet<Integer> treeSet = new TreeSet<Integer>(c);
        c.clear();
        c.addAll(treeSet);

        return c;
    }

    private static Vector<Integer> interVect(Vector<Integer> a, Vector<Integer> b) {
        Vector<Integer> c = new Vector<Integer>(20);

        for(int num : a) if(b.indexOf(num) != -1) c.add(num);
        for(int num : b) if(a.indexOf(num) != -1) c.add(num);

        TreeSet<Integer> treeSet = new TreeSet<Integer>(c);
        c.clear();
        c.addAll(treeSet);

        return c;
    }

    private static Vector<Integer> diffVect(Vector<Integer> a, Vector<Integer> b) {
        Vector<Integer> c = new Vector<Integer>(20);
        Vector<Integer> d = new Vector<Integer>(20);

        d = interVect(a, b); // fac A - (A ^ B)

        for(int num : a)
            if(d.indexOf(num) == -1) c.add(num);

        return c;
    }
    public static void main(String args[]) {
        Vector<Integer> a = new Vector<Integer>(10);
        for(int i = 0; i < 10; i++) a.add(i, i);

        Vector<Integer> b = new Vector<Integer>(10);
        for(int i = 0; i < 10; i++) b.add(i, i + 5);

        System.out.println("a = " + a);
        System.out.println("b = " + b);

        System.out.println(unionVect(a, b));
        System.out.println(interVect(a, b));
        System.out.println(diffVect(a, b));

    }
}