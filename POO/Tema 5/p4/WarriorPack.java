import java.util.*;

public class WarriorPack extends Warrior {
    private Vector<Warrior> warriors ;

    public WarriorPack() {
        super(0, "", -1);
        warriors = new Vector<Warrior>();
    }

    public void addWarrior(Warrior newWarrior) {
        warriors.add(newWarrior);
    }

    public Vector<Warrior> getWarriors() {
        return warriors ;
    }

    public int calculateDamage() {
        int damage = 0;
        for (int i = 0; i < warriors.size(); i++) {
            damage += warriors.get(i).getDamage();
        }
        return damage;
    }
}
