public class ClockTime {
    private int hour, minute;

    ClockTime(int h, int m) {hour = h; minute = m;}
    public int getHour() {return hour;}
    public int getMinute() {return minute;}
    public int compTime(ClockTime x) {
        if(x.hour > hour) return -1;
        if(x.hour < hour) return 1;
        if(x.minute > minute) return -1;
        if(x.minute < minute) return 1;
        return 0;
    }
}
