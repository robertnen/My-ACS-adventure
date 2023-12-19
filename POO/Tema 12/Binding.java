public class Binding {
    public static void main(String args[]) {
        Hero h1 = new Warrior(), h2 = new Ninja();
        Hero h3 = new Rogue();
        BadLuck bl = new StormFire();
        bl.execute(h1);
        bl.execute(h2);
        bl.execute(h3);
    }
}

abstract class BadLuck {
    abstract void execute(Hero h);
}

abstract class Hero {
    abstract void getRole();
}

class Warrior extends Hero {
    @Override
    void getRole() { System.out.println("Warrior"); }
}

class Ninja extends Hero {
    @Override
    void getRole() { System.out.println("Ninja"); }
}

class Rogue extends Hero {
    @Override
    void getRole() { System.out.println("Rogue"); }
}

class StormFire extends BadLuck {
    @Override
    void execute(Hero h) { h.getRole(); }
}