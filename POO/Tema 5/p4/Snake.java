public class Snake extends Warrior {
    public Snake(int health, String name, int damage) {
        super(health, name, 0);
        this.damage = damage;
    }

    @Override
    public String toString() {
        return "Snake " + this.health + " " + getDamage();
    }
}
