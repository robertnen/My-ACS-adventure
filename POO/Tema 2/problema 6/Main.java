import java.util.Vector;

public class Main {

    private static Vector instanVector(Vector v) {
        Vector result = new Vector<>(6);

        int i, d, f, s, c, b;
        i = d = f = s = c = b = 0;

        for(int j = 0; j < v.size(); j++) {

            String str = v.get(j).getClass().toString();
            int index = str.indexOf("g");
            str = str.substring(index + 2);

            if(str.equals("Integer")) i++;
            if(str.equals("Double")) d++;
            if(str.equals("Float")) f++;
            if(str.equals("String")) s++;
            if(str.equals("Character")) c++;
            if(str.equals("Boolean")) b++;
        }

        result.add(0, i);
        result.add(1, d);
        result.add(2, f);
        result.add(3, s);
        result.add(4, c);
        result.add(5, b);

        return result;
    }

    public static void main(String args[]) {
        Vector v = new Vector();
        v.add(7.5);
        v.add(7.1);
        v.add(7.2);
        v.add("String");
        v.add("Test");
        v.add(true);
        v.add(false);
        v.add(false);
        v.add(true);
        v.add(1.e2f);
        v.add('c');
        System.out.println(instanVector(v));
    }
}