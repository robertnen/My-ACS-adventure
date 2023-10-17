public class Produs {
    private String nume;
    private double pret;
    private int cantitate;

    Produs(String nume, double pret, int cantitate) {
        this.nume = nume;
        this.pret = pret;
        this.cantitate = cantitate;
    }

    public String getName() {
        return this.nume;
    }

    public double getPrice() {
        return this.pret;
    }

    @Override
    public String toString() {
        return "Produs " + nume + " " + pret + " " + cantitate;
    }
}
