import java.util.Collection;

public enum Strategy {
    BestPartialScore {
        public Student getBestStudent(Collection<Grade> grades) {
            Grade bestFit = null;
            for (Grade grade : grades) {
                if (bestFit == null) {
                    bestFit = grade;
                    continue;
                }

                if (bestFit.getPartialScore() < grade.getPartialScore()) bestFit = grade;
            }
            return bestFit.getStudent();
        }
    },

    BestExamScore {
        public Student getBestStudent(Collection<Grade> grades) {
            Grade bestFit = null;
            for (Grade grade : grades) {
                if (bestFit == null) {
                    bestFit = grade;
                    continue;
                }

                if (bestFit.getExamScore() < grade.getExamScore()) bestFit = grade;
            }
            return bestFit.getStudent();
        }
    },

    BestTotalScore {
        public Student getBestStudent(Collection<Grade> grades) {
            Grade bestFit = null;
            for (Grade grade : grades) {
                if (bestFit == null) {
                    bestFit = grade;
                    continue;
                }

                if (bestFit.getExamScore() < grade.getExamScore()) bestFit = grade;
            }
            return bestFit.getStudent();
        }
    };

    public abstract Student getBestStudent(Collection<Grade> grades);
}
