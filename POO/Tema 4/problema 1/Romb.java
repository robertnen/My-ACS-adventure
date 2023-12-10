public class Romb extends Paralelogram {

    private int diag1;
    private int diag2;

    public Romb(int latura1, int diag1, int diag2, int unghi1) {
        super(latura1, latura1, unghi1);
        this.diag1 = diag1;
        this.diag2 = diag2;
    }

    public double arie() {
        return (diag1 + diag2) / 2;
    }
}
