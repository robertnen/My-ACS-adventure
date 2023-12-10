public class Warrior {
    public static final int SNAKE_Warrior = 0;
    public static final int OGRE_Warrior = 1;
    public static final int MARSHMALLOW_MAN_Warrior = 2;

    //Stores one of the three above types
    public int type;
    //0 = dead, 100 = full strength
    public int health;
    public String name;
    public int damage = 0;

    public Warrior(int health, String name, int type) {
        this.health = health;
        this.name = name;
        this.type = type;
    }

    public int getDamage() {
        return damage;
    }

    @Override
    public String toString() {
        String result = "";
        switch (type) {
            case SNAKE_Warrior:
                result += "Snake";
                break;

            case OGRE_Warrior:
                result += "Ogre";
                break;

            case MARSHMALLOW_MAN_Warrior:
                result += "MarshmallowMan";
                break;

            default:
                result += "HOW DID YOU GOT ANOTHER VALUE??";
                break;
        }

        result += " " + name + " " + health;

        return result;
    }
}
