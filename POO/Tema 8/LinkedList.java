import java.util.Iterator;

public class LinkedList<T> implements Iterable<T> {
    private static class Node<T> {
        private T data;
        private Node<T> next;

        public Node(T data, Node<T> next) {
            this.data = data;
            this.next = next;
        }

        public Node(T data) {this(data, null);}
    }

    private Node<T> first, last;

    public LinkedList() {
        this.first = null;
        this.last = null;
    }

    public void addFirst(T data) {
        Node<T> newNode = new Node<>(data);
        if(isEmpty()) {first = last = newNode;}
        else {
            newNode.next = first;
            first = newNode;
        }
    }

    public void add(T data) {
        Node<T> newNode = new Node<>(data);
        if(isEmpty()) first = last = newNode;
        else {
            last.next = newNode;
            last = newNode;
        }
    }

    private boolean isEmpty() {return first == null;}

    private class ListIterator implements Iterator<T> {
        private Node<T> current = first;

        @Override
        public boolean hasNext() {return current != null;}

        @Override
        public T next() {
            if(!hasNext()) throw new java.util.NoSuchElementException();
            T data = current.data;
            current = current.next;
            return data;
        }
    }

    @Override
    public Iterator<T> iterator() {return new ListIterator();}
}