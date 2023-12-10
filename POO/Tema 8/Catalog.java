import java.util.*;

public class Catalog extends TreeSet {

    private static final Comparator<Student> DESC_MEAN = new Comparator<Student>() {
        @Override
        public int compare(Student s1, Student s2) {
            int meanComp = Double.compare(s2.getMedia(), s1.getMedia());

            return (meanComp == 0) ? s1.getName().compareTo(s2.getName()) : meanComp;
        }
    };

    public Catalog(Comparator<Student> comparator) {super(comparator);}
    public Catalog() {super(DESC_MEAN);}

    public void addStudent(String name, double media, int clazz) {add(new Student(name, media, clazz));}

    public Student getStudent(String name) {
        for(Object student: this)
            if(((Student) student).getName().equals(name)) return (Student) student;
        return null;
    }

    public void removeStudent(String name) {
        Student studentToRemove = getStudent(name);
        if(studentToRemove != null) remove(studentToRemove);

    }

    public Catalog byClass(int clazz) {
        Catalog result = new Catalog(DESC_MEAN);
        for(Object student: this) if (((Student) student).getClazz() == clazz) result.add(student);
        return result;
    }

    @Override
    public String toString() {
        StringBuilder result = new StringBuilder("[");
        for(Object student: this) result.append(student).append(", ");
        if(size() > 0) result.setLength(result.length() - 2);
        result.append("]");
        return result.toString();
    }

    public class Student implements Comparable<Student> {
        public String name;
        public double media;
        public int clazz;

        public Student(String name, double media, int clazz) {
            this.name = name;
            this.media = media;
            this.clazz = clazz;
        }

        public String getName() {return name;}

        public double getMedia() {return media;}

        public int getClazz() {return clazz;}

        @Override
        public int compareTo(Student other) {
            int meanComp = Double.compare(this.media, other.media);
            return (meanComp == 0) ? this.name.compareTo(other.name) : meanComp;
        }

        @Override
        public String toString() {
            return "Student{name='" + name + '\'' + ", media=" + media + ", clazz=" + clazz +'}';
        }
    }
}