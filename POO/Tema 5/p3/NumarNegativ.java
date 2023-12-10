
public class NumarNegativ extends Exception {
    public NumarNegativ(int maxim) {
        super("Numarul introdus este negativ!");
        System.out.println("Numarul cel mai mare este " + maxim);
    }
}
