public class Paralelogram extends Patrulater {
    public Paralelogram(int latura1, int latura2, int unghi1) {
        super(latura1, latura2, latura1, latura2, unghi1, 180 - unghi1, unghi1, 180 - unghi1);
    }

    public double arie() {
        return latura1 * latura2 * Math.sin(unghi1);
    }
}
