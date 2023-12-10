import java.util.*;

public class ArrayMap<K, V> extends AbstractMap<K, V> {
    private List<ArrayMapEntry<K, V>> entries = new ArrayList<>();

    @Override
    public Set<Entry<K, V>> entrySet() {return new HashSet<>(entries);}

    @Override
    public int size() {return entries.size();}

    @Override
    public V put(K key, V value) {
        for(ArrayMapEntry<K, V> entry: entries) {
            if(entry.getKey().equals(key)) {
                V oldValue = entry.getValue();
                entry.setValue(value);
                return oldValue;
            }
        }
        ArrayMapEntry<K, V> newEntry = new ArrayMapEntry<>(key, value);
        entries.add(newEntry);
        return null;
    }

    public class ArrayMapEntry<K, V> implements Map.Entry<K, V> {
        private K key;
        private V value;

        public ArrayMapEntry(K key, V value) {
            this.key = key;
            this.value = value;
        }

        @Override
        public K getKey() {return key;}

        @Override
        public V getValue() {return value;}

        @Override
        public V setValue(V value) {
            V oldValue = this.value;
            this.value = value;
            return oldValue;
        }

        @Override
        public String toString() {return "(" + key + ", " + value + ")";}

        @Override
        public boolean equals(Object o) {
            if(this == o) return true;
            if(o == null || getClass() != o.getClass()) return false;

            ArrayMapEntry<?, ?> that = (ArrayMapEntry<?, ?>) o;

            if(key != null ? !key.equals(that.key) : that.key != null) return false;
            return value != null ? value.equals(that.value) : that.value == null;
        }

        @Override
        public int hashCode() {
            int result = key != null ? key.hashCode() : 0;
            result = 31 * result + (value != null ? value.hashCode() : 0);
            return result;
        }
    }
}