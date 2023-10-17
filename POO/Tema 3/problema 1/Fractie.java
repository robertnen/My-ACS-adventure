public class Fractie {
    public int a, b;

    public Fractie(int a, int b) {
        this.a = a;
        this.b = b;
    }

    public Fractie sum(Fractie x) {
        Fractie result = new Fractie(this.a * x.b + this.b * x.a, this.b * x.b);
        result = simplify(result);
        return result;
    }

    private Fractie simplify(Fractie x) {
        int a = x.a, b = x.b;

        while(a != b) {
            if(a > b) a -= b;
            else b = b - a;
        }
        x.a = x.a / a;
        x.b = x.b / b;
        return x;
    }

    @Override
    public String toString() {
        return "" + this.a + " / " + this.b;
    }

    @Override
    public boolean equals(Object obj) {
        if(obj instanceof Fractie) return true;
        return false;
    }
}
