public class Marfa extends Vagon {
    public Marfa() {
        super(0, 400);
    }

    @Override
    public void openDoor() {
        System.out.println("The doors can't be opened automatically.");
    }

    @Override
    public void closeDoor() {
        System.out.println("The doors can't be closed automatically.");
    }
}
