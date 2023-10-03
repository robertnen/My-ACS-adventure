package problema7;

import java.util.Scanner;

public class Main {
    public static void main(String args[]) {

        final int MAX_SIZE = 1000;

        boolean[] prims = new boolean[MAX_SIZE];


        prims[0] = true;

        for(int i = 2; i < MAX_SIZE; i++)
            for(int j = 2; j < MAX_SIZE / i; j++)
                prims[i * j] = true;

        Scanner sn = new Scanner(System.in);
        int n = Integer.parseInt(sn.nextLine());

        for(int i = 2; i <= 2 * n; i += 2) {
            for(int j = 1; j < i; j++)
                if(prims[j] == false && prims[i - j] == false) {
                    System.out.println("" + i + " = " + j + " + " + (i - j));
                    break;
                }
        }
    }
}
