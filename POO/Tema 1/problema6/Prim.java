package problema6;

public class Prim {
    public boolean isPrim(int x) {
        if(x < 2 || x % 2 == 0) return false;
        if(x == 2) return true;

        for(int i = 3; i <= x / 2; i += 2)
            if(x % i == 0) return false;

        return true;
    }
}
