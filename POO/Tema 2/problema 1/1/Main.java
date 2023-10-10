public class Main {

    private static int strOccu(String str1, String str2) {
        int counter = 0, index;

        index = str1.indexOf(str2);

        while(index != -1) {
            counter++;
            str1 = str1.substring(index + 1);
            index = str1.indexOf(str2);
        }

        return counter;
    }

    public static void main(String args[]) {
        String s2 = "si";
        String s1 = "sir1 si cu sir2 fac un sir3";
        System.out.println(strOccu(s1, s2));
    }
}