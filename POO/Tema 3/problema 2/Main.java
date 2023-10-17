public class Main {
	public static void main(String args[]) {
        Magazin m = new Magazin(new Produs("Lapte", 10.99, 14), new Produs("Apa", 7.62, 8), new Produs("Iaurt", 13.29, 20), "La Dorel");
        System.out.println(m.getName());
        System.out.println(m.getTotalProdus());
	}
}