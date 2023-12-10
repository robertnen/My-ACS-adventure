public class Dreptunghi extends Paralelogram {
        public Dreptunghi(int latura1, int latura2) {
            super(latura1, latura2, 90);
        }

        public double arie() {
            return latura1 * latura2;
        }
}
