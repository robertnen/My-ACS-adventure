package problema6;

public class Main {
	public static void main(String args[]) {
		Prim pr = new Prim();

		for(int i = 0; i < 20; i++)
			System.out.println("" + i + " este " + (pr.isPrim(i) ? "prim" : "nu e prim"));
	}
}
