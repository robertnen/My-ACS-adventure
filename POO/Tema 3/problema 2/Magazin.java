public class Magazin {
    private String nume;
    private Produs p1;// = new Produs("Lapte", 10.99, 14);
    private Produs p2; //= new Produs("Apa", 7.62, 8);
    private Produs p3; //= new Produs("Iaurt", 13.29, 20);

    Magazin(Produs p1, Produs p2, Produs p3, String nume) {
        this.p1 = p1;
        this.p2 = p2;
        this.p3 = p3;
        this.nume = nume;
    }

    public String getName() {
        return this.nume;
    }

    public double getTotalProdus() {
        return p1.getPrice() + p2.getPrice() + p3.getPrice();
    }

    @Override
    public String toString() {
        return p1.getName() + " " + p2.getName() + " " + p3.getName();
    }
}
