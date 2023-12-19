import java.util.ArrayList;
import java.util.HashMap;

class Pair<K, V1, V2> {
    private K key;
    private V1 value1;
    private V2 value2;

    public Pair(K key, V1 value1, V2 value2) {
        this.key = key;
        this.value1 = value1;
        this.value2 = value2;
    }

    public K getKey() {
        return key;
    }

    public V1 getValue1() {
        return value1;
    }

    public V2 getValue2() {
        return value2;
    }
}

public class ScoreVisitor implements Visitor {
    private HashMap<Teacher, ArrayList<Pair<Student, String, Double>>> examScores;
    private HashMap<Assistant, ArrayList<Pair<Student, String, Double>>> partialScores;

    public ScoreVisitor(HashMap<Teacher, ArrayList<Pair<Student, String, Double>>> examScores,
                        HashMap<Assistant, ArrayList<Pair<Student, String, Double>>> partialScores) {
        this.examScores = examScores;
        this.partialScores = partialScores;
    }

    @Override
    public void visit(Assistant assistant) {
        ArrayList<Pair<Student, String, Double>> studentScores = partialScores.get(assistant);
        if (studentScores != null) {
            for (Pair<Student, String, Double> score : studentScores) {
                Student student = score.getKey();
                String courseName = score.getValue1();
                Double partialScore = score.getValue2();

                Course course = Catalog.getInstance().getCourse(courseName);
                if (course != null) {
                    Grade grade = course.getGrade(student);
                    if (grade == null) {
                        grade = new Grade(courseName, student, null, partialScore);
                        course.addGrade(grade);
                    } else {
                        grade.setPartialScore(partialScore);
                    }
                }
            }
        }
    }

    @Override
    public void visit(Teacher teacher) {
        ArrayList<Pair<Student, String, Double>> studentScores = examScores.get(teacher);
        if (studentScores != null) {
            for (Pair<Student, String, Double> score : studentScores) {
                Student student = score.getKey();
                String courseName = score.getValue1();
                Double examScore = score.getValue2();

                Course course = Catalog.getInstance().getCourse(courseName);
                if (course != null) {
                    Grade grade = course.getGrade(student);
                    if (grade == null) {
                        grade = new Grade(courseName, student, examScore, null);
                        course.addGrade(grade);
                    } else {
                        grade.setExamScore(examScore);
                    }
                }
            }
        }
    }
}
