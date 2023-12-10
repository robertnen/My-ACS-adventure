import java.util.Hashtable;
import java.util.Map;

public class HSet extends Hashtable<Object, Object> {
    //Adauga un element in multime, daca nu exista deja
    public boolean add(Object value) {
        return super.put(value, value) != null;
    }

    //returneaza un String cu elementele multimii (doar cheile, nu perechi)
    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder("");
        for(Map.Entry<Object, Object> e : this.entrySet()) {
            stringBuilder.append(e.getKey() + " ");
        }
        return stringBuilder.toString();
    }

    //Sterge perechea corespunzatoare cheii, intorcand valoarea
    public Object remove(Object key) {
        return super.remove(key);
    }
}

class Test3 {
    public static void main(String args[]) {
        HSet set = new HSet();
        set.add("Laborator");
        set.add("Agregare");
        set.add("Mostenire");
        System.out.println(set);
        System.out.println(set.size());
        set.add("Laborator");
        if(set.size() == 4) {
            System.out.println("Multimea nu trebuie sa contina duplicate!");
        }
        System.out.println(set.remove("POO"));
        System.out.println(set.remove("Laborator"));
        if(set.size() != 2) {
            System.out.println("Stergerea nu functioneaza!");
        }
        set.add("Supradefinire");
        set.add("Supraincarcare");
        System.out.println(set);
    }
}