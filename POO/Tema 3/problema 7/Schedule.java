public class Schedule {
    private ClockTime departure, arrival;

    Schedule(ClockTime departure, ClockTime arrival) {
        this.departure = departure;
        this.arrival = arrival;
    }

    public ClockTime getDepartTime() {return departure;}
    public ClockTime getArrivTime() {return arrival;}

    public int totalMin() {
        int result = (arrival.getHour() - departure.getHour()) * 60 + arrival.getMinute() - departure.getMinute();
        if(result < 0) result += 1440;
        return result;
    }
}
