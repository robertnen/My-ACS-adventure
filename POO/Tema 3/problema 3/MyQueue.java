public class MyQueue {
    private final int INFINIT = 9500; // ???
    private MyArray arr;
    private int first = 0, last, size = 0;

    MyQueue() {
        arr = new MyArray();
    }

    public int getSize() {return size;}
    public void enqueue(int value) {arr.set(arr.getSize(), value); size++; last++;}
    public int dequeue() {size--; first++; return arr.get(first - 1);}
    public boolean isEmpty() {return (size > 0 ? true : false);}

    @Override
    public String toString() {
        String result = "";
        for(int i = 0; i < size; i++) result += arr.get(i) + " ";
        return result;
    }
}
