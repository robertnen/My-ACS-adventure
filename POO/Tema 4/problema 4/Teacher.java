import java.util.Vector;

public class Teacher extends Person {
    private Vector<String> courses;

    public Teacher(String name, String adress) {
        super(name, adress);
    }

    public boolean addCourse(String course) {
        if(courses.contains(course)) return false;
        courses.add(course);
        return true;
    }

    public boolean removeCourse(String course) {
        if(courses.contains(course)) {
            courses.remove(course);
            return true;
        }
        return false;
    }

    @Override
    public String toString() {
        String result = "";
        for(String c : courses) result += c + " ";
        return result;
    }
}
