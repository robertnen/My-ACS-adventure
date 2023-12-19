import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public class Course {
    private String name;
    private List<User> assistant = new ArrayList<User>();
    private User teacher;
    private List<Grade> grade = new ArrayList<Grade>();
    private List<User> student = new ArrayList<User>();
    private Strategy strategy;

    private Course(CourseBuilder builder) {
        this.name = builder.name;

        strategy.BestExamScore.getBestStudent(grade);
    }

    public Student strategy(Collection<Grade> grades) {
        return strategy.getBestStudent(grades);
    }

    public String getName() {
        return name;
    }

    public static class CourseBuilder {
        private String name;
        private List<User> assistant = new ArrayList<User>();
        private User teacher;
        private List<Grade> grade = new ArrayList<Grade>();
        private List<User> student = new ArrayList<User>();


        public CourseBuilder(String name) {
            this.name = name;
        }

        public CourseBuilder teacher(User teacher) {
            this.teacher = teacher;
            return this;
        }

        public CourseBuilder assistant(User assistant) {
            this.assistant.add(assistant);
            return this;
        }

        public CourseBuilder grade(Grade grade) {
            this.grade.add(grade);
            return this;
        }

        public CourseBuilder student(User student) {
            this.student.add(student);
            return this;
        }

        public CourseBuilder name(String name) {
            this.name = name;
            return this;
        }

        public Course build() {
            return new Course(this);
        }
    }

    @Override
    public String toString() {
        String result = "";
        System.out.println("Course toString()");
        return result;
    }
}