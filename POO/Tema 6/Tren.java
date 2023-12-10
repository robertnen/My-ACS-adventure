import java.util.Vector;

public class Tren {
    private Vector<Vagon> vagoane = new Vector<Vagon>(0);

    Tren() {}

    public void addVagon(Vagon vagon) {
        vagoane.add(vagon);
    }

    public void showVagons() {
        for(Vagon vagon : vagoane) {
            if(vagon instanceof CalatoriA)System.out.println("Vagon de tip CalatoriA");
            else if(vagon instanceof CalatoriB) System.out.println("Vagon de tip CalatoriB");
            else if(vagon instanceof Marfa) System.out.println("Vagon de tip Marfa");
        }
    }

    public int compTren(Tren T) {
        int colCurr = 0, colT2 = 0;
        for(Vagon v : vagoane) colCurr += v.capCol;
        for(Vagon v : T.vagoane) colT2 += v.capCol;

        return colCurr - colT2;
    }
}