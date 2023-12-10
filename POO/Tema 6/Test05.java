/*
 * Programare orientata pe obiecte
 * Seria CC
 * Laboratorul 6
 */

/**
 *
 * @author Nan Mihai
 */
public class Test05
 {
    public static void main(String args[]) {
        Tren t = new Tren();
        t.addVagon(new CalatoriA());
        t.addVagon(new CalatoriB());
        t.addVagon(new CalatoriA());
        t.addVagon(new CalatoriA());
        t.addVagon(new CalatoriA());
        t.addVagon(new CalatoriB());
        t.addVagon(new CalatoriB());
        t.addVagon(new Marfa());
        System.out.println(t);
    }
}
