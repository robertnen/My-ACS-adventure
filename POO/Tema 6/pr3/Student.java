package pr3;

import java.util.Vector;

public class Student implements Persoana {

    private String nume;
    private Vector<Double> m = new Vector<Double>(0);

    @Override
    public int compareTo(Object o) {
        Student obj = (Student) o;
        if(this.nume.compareTo(obj.nume) != 0) return this.nume.compareTo(obj.nume);
        if(this.calculMedieGenerala() > obj.calculMedieGenerala()) return 1;
        return -1;
    }

    @Override
    public double calculMedieGenerala() {
        int sum = 0, t = 0;
        for(double med : m) {
            sum += med;
            t++;
        }
        return ((double) sum) / t;
    }

    @Override
    public String getNume() {
        return nume;
    }

    @Override
    public void setNume(String nume) {
        this.nume = nume;
    }

    @Override
    public void addMedie(double medie) {
        m.add(medie);
    }
}
