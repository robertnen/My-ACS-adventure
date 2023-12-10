import java.util.Collection;
import java.util.Collections;
import java.util.Scanner;
import java.util.Vector;

public class Test {

    private static Vector<Integer> v = new Vector<Integer>(100);

    public static void myRead() throws Exception {
        Scanner sc = new Scanner(System.in);

        int x = 0;
        while(true) {
            System.out.print("x = ");

            x = sc.nextInt();
            if(x < 0) throw new NumarNegativ(Collections.max(v));

            v.add(x);
        }
    }

    public static void main(String args[]) throws Exception {
        myRead();
    }
}
