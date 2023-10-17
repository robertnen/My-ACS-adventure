public class Train {
    private Route r;
    private Schedule s;
    private boolean local;

    Train(Schedule s, Route r, boolean local) {
        this.s = s;
        this.r = r;
        this.local = local;
    }

    @Override
    public String toString() {
        String result = "" + local + " ";
        ClockTime timeDepart = s.getDepartTime(), timeArr = s.getArrivTime();

        result += r.getOrigin() + " (" + timeDepart.getHour() + ":" + timeDepart.getMinute() + ")";
        result += " -> " + r.getDestination() + " (" + timeArr.getHour() + ":" + timeArr.getMinute();
        result += ")";
        return result;
    }

    public static void main(String args[]) {
        ClockTime depart, arr;
        depart = new ClockTime(13, 51);
        arr = new ClockTime(15, 31);
		Schedule s = new Schedule(depart, arr);
        Route r = new Route("Pitesti", "Bucuresti Nord");
        Train thomas = new Train(s, r, true);
        System.out.println(thomas.toString());
	}

}
