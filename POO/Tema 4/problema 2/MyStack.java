import java.util.Vector;

public class MyStack extends Array {
    public MyStack(Vector vector) {
        this.vector = vector;
    }

    public void push(int x) {
        addElement(x, getSize());
    }

    public void pop() {
        remove(getSize());
    }
}
