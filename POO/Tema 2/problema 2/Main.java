import java.util.StringTokenizer;

public class Main {

    private static int strOccu(String text, String cuv) {
        int counter = 0;

        StringTokenizer strToken = new StringTokenizer(text);

        while(strToken.hasMoreTokens()) {
            String word = strToken.nextToken(" ,.?!;:\n");
            if(word.equals(cuv)) counter++;
        }

        return counter;


    }

    public static void main(String args[]) {
        String s1 = "si";
        String s2 = "sir1 si cu sir2 fac un sir3";

        System.out.println(strOccu(s2, s1));

    }
}