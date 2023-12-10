public class CalatoriA extends Vagon {
    public CalatoriA() {
        super(40, 300);
    }

    @Override
    public void blockWindow() {
        System.out.println("The windows can't be blocked. Enjoy fresh air!");
    }
}
