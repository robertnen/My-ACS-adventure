import java.util.AbstractMap;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class ArrayMap<K, V> extends AbstractMap<K, V> {

    private List<K> keys = new ArrayList<>();
    private List<V> values = new ArrayList<>();

   @Override
    public Set<Map.Entry<K, V>> entrySet() {
        Set<Entry<K, V>> set = new HashSet<>();
        for(int i = 0; i < keys.size(); i++) {
            K key = keys.get(i);
            V value = values.get(i);
            set.add(new SimpleEntry<>(key, value));
        }
        return set;
    }

    @Override
    public String toString() {
        String result = "";
        for(int i = 0; i < keys.size(); i++)
            result += "(" + keys.get(i) + ": " + values.get(i) + "), ";

        return result;
    }

@Override
    public V put(K key, V value) {
        if(key == null) throw new NullPointerException("Key can not be null");

        int i = keys.indexOf(key);
        if(i != -1) {
            V oldValue = values.get(i);
            values.set(i, value);
            return oldValue;
        } else{
            keys.add(key);
            values.add(value);
            return null;
        }
    }

 @Override
    public V get(Object key) {
        int i = keys.indexOf(key);
        return (i != -1) ? values.get(i) : null;
    }

    @Override
    public Set<K> keySet() {
        return new HashSet<>(keys);
    }

    @Override
    public Collection<V> values() {
        return new ArrayList<>(values);
    }

    public static void main(String[] args) {
        ArrayMap<String, Integer> map = new ArrayMap<>();
        map.put("a", 1);
        map.put("b", 2);
        map.put("c", 3);
        map.put("d", 4);
        map.put("e", 5);
        map.put("f", 6);

        System.out.println(map);

        Iterator<Map.Entry<String, Integer>> iterator = map.entrySet().iterator();
        while(iterator.hasNext()) {
            Entry<String, Integer> entry = iterator.next();
            System.out.println("(" + entry.getKey() + " = " + entry.getValue() + ")");
        }
    }
}
