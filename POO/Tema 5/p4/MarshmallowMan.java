public class MarshmallowMan extends Warrior {
    public MarshmallowMan(int health, String name, int damage) {
        super(health, name, 2);
        this.damage = damage;
    }

    @Override
    public String toString() {
        return "MarshMallowMan " + this.health + " " + getDamage();
    }
}

