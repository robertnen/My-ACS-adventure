public class Route {
    private String origin, destination;

    Route(String origin, String destination) {
        this.origin = origin;
        this.destination = destination;
    }

    public String getOrigin() {return origin;}
    public String getDestination() {return destination;}

    public boolean compRoute(Route R) {
        if(!R.origin.equals(origin)) return false;
        if(!R.destination.equals(destination)) return false;
        return true;
    }
}
