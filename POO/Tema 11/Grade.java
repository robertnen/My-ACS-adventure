public class Grade implements Comparable<Grade> {
    private Double partialScore, examScore;
    private Student student;
    private String course;

    public Grade(String course, Student student) {
            partialScore = 0.0;
            examScore = 0.0;
            this.course = course;
            this.student = student;
            }

    public Grade(String course, Student student,Double partialScore, Double examScore ) {
            this.partialScore = partialScore;
            this.examScore = examScore;
            this.course = course;
            this.student = student;
            }

    public Student getStudent() {
        return student;
    }

    public Double getExamScore() {
        return examScore;
    }

    public Double getPartialScore() {
        return partialScore;
    }

    public String getCourse() {
        return course;
    }

    public void setPartialScore(Double score) {
        partialScore = score;
    }

    public void setExamScore(Double score) {
        examScore = score;
    }

    public Double getTotal() {
        return partialScore + examScore;
}

    @Override
    public int compareTo(Grade o) {

        Double t1, t2;
        t1 = this.getTotal();
        t2 = ((Grade) o).getTotal();

        if(t1 < t2) return 1;
        if(t1 > t2) return -1;
        return 0;
    }
}