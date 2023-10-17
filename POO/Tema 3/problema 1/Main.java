public class Main {
	public static void main(String args[]) {
        Fractie f = new Fractie(1, 2);
        Fractie g = new Fractie(1, 2);

        f = f.sum(g);
        System.out.println(f.toString());
        System.out.println(g.toString());
        System.out.println(f.equals(g));
	}
}