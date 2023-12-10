import java.util.Comparator;
import java.util.LinkedList;
import java.util.SortedSet;

public class SListSet extends LinkedList implements SortedSet {

    private Comparator comparator;

    public Comparator comparator() {
        return comparator;
    }

    SListSet(Comparator comparator) {
        this.comparator = comparator;
    }

    @Override
    public boolean add(Object obj) {
        if(this.contains(obj)) return false;
        super.add(obj);
        this.sort(comparator);
        return true;
    }

    public SortedSet subSet(Object fromElement, Object toElement) {
        return this.subSet(fromElement, toElement);
    }

    @Override
    public SortedSet headSet(Object toElement) {
        return this.headSet(toElement);
    }

    @Override
    public SortedSet tailSet(Object fromElement) {
        return this.tailSet(fromElement);
    }

    @Override
    public Object first() {
        return this.get(0);
    }

    @Override
    public Object last() {
        return this.get(this.size());
    }
}
