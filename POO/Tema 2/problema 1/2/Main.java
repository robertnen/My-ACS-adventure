public class Main {

    public static void main(String args[]) {
        String s1 = "si";
        String s2 = "sir1 si cu sir2 fac un sir3";

        int strOccu = (s2.split(s1).length - 1);
        System.out.println(strOccu);
    }
}