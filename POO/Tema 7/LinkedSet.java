import java.util.LinkedList;
import java.util.Set;

public class LinkedSet extends LinkedList implements Set {

    @Override
    public boolean add(Object o) {
        if(this.contains(o)) return false;
        return super.add(o);
    }

    @Override
    public void add(int i, Object o) {
        if(this.contains(o)) return;
        super.add(i, o);
    }

    @Override
    public Object set(int i, Object o) {
        if(this.contains(o)) return null;
        return super.set(i, o);
    }
}
