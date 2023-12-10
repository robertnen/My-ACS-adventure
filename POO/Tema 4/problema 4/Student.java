import java.util.Vector;

public class Student extends Person {

    private Vector<String> courses = new Vector<String>(0);
    private Vector<Integer> grades = new Vector<Integer>(0);

    public Student(String name, String adress) {
        super(name, adress);
    }

    @Override
    public String toString() {
        String result = "";
        for(int i = 0; i < courses.size(); i++) {
            result += courses.get(i) + " " + grades.get(i) + "\n";
        }
        return result;
    }

    public void addCourseGrade(String course, int grade) {
        courses.add(course);
        grades.add(grade);
    }

    public void printGrades() {
        for(Integer g : grades) System.out.println(g);
    }

    public double getAverageGrade() {
        double sum = 0;
        for(Integer g : grades) sum += g;
        return sum / grades.size();
    }
}
