public class Ogre extends Warrior {
    public Ogre(int health, String name, int damage) {
        super(health, name, 1);
        this.damage = damage;
    }

    @Override
    public String toString() {
        return "Ogre " + this.health + " " + getDamage();
    }
}
