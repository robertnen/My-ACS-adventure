abstract class Vagon {
    int capPers, capCol;

    public Vagon(int capPers, int capCol) {
        this.capPers = capPers;
        this.capCol = capCol;
    }

    public void openDoor() {
        System.out.println("The doors are opened.");
    }

    public void closeDoor() {
        System.out.println("The doors are closed.");
    }

    public void blockWindow() {
        System.out.println("Windows are blocked.");
    }
}
