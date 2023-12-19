import java.util.ArrayList;
import java.util.List;

public class Catalog {
    private static Catalog instance = null;
    private List<Course> courses = new ArrayList<Course>();
    private List<Observer> observers;

    private Catalog() {
        // what should be inside
        System.out.println("New catalog");
        this.observers = new ArrayList<>();
    }

    public static Catalog getInstance() {
        if(instance == null) instance = new Catalog();
        return instance;
    }

    public void addCourse(String name, int grade) {
        Course course = new Course.CourseBuilder(name).build();
        courses.add(course);
    }

    public void addCourse(Course course) {
        this.courses.add(course);
    }

    @Override
    public void addObserver(Observer observer) {
        observers.add(observer);
    }

    @Override
    public void removeObserver(Observer observer) {
        observers.remove(observer);
    }

    @Override
    public void notifyObservers(Notification notification) {
        for (Observer observer : observers) {
            observer.update(notification);
        }
    }

    @Override
    public String toString() {
        String result = "";

        for(Course course : courses)
            result += course.getName() + " ";

        return result;
    }

    public static void main(String args[]) {
        Catalog catalog = Catalog.getInstance();

        catalog.addCourse("mate", 7);
        catalog.addCourse("mate2", 7);
        catalog.addCourse("mate3", 7);
        catalog.addCourse("mate4", 7);

        catalog.toString();
    }


}


