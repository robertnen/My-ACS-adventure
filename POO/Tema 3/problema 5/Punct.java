public class Punct {
    private int x, y;

    Punct() {x = 0; y = 0;}

    public int getX() {return x;}
    public int getY() {return y;}

    public void setX(int x) {this.x = x;}
    public void setY(int y) {this.y = y;}

    public double distance(int x, int y) {
        return Math.sqrt((this.x - x) * (this.x - x) - (this.y - y) * (this.y - y));
    }

    public double distance(Punct p) {
        return Math.sqrt((p.x - x) * (p.x - x) - (p.y - y) * (p.y - y));
    }
}

class Test {
    public static void main(String args[]) {
        Punct A, B;
        A = new Punct();
        B = new Punct();

        A.setX(1); A.setY(2);
        B.setX(-1); B.setY(3);

        System.out.println(A.distance(B));
        System.out.println(A.distance(-1, 3));
    }
}
