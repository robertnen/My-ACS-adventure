import java.util.List;

public abstract class User {
    protected String firstName, lastName;

    public User(String firstName, String lastName) {
        this.firstName = firstName;
        this.lastName = lastName;
    }

    public String toString() {
        return firstName + " " + lastName;
    }
}

class Student extends User {

    private Parent mother, father;
    private List<Observer> observers;

    public Student(String firstName, String lastName) {
        super(firstName, lastName);
        this.observers = new ArrayList<>();
    }

    public void setMother(Parent mother) {
        this.mother = mother;
    }

    public void setFather(Parent father) {
        this.father = father;
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
}

class Parent extends User {
    public Parent(String firstName, String lastName) {
        super(firstName, lastName);
    }
}

class Teacher extends User {
    public Teacher(String firstName, String lastName) {
        super(firstName, lastName);
    }
}

class Assistant extends User {
    public Assistant(String firstName, String lastName) {
        super(firstName, lastName);
    }
}

class UserFactory {
    public static User createUser(String role, String type, String name) {
        if(role.equals("Student")) return new Student(name, name);
        if(role.equals("Parent")) return new Parent(name, name);
        if(role.equals("Teacher")) return new Teacher(name, name);
        if(role.equals("Assistant")) return new Assistant(name, name);
        return null;
    }
}

class Test {
    public static void main(String[] args) {
        //testare exercitiu 2
        User studentA = UserFactory.createUser("Student", "A", "Popescu");
        User studentB = UserFactory.createUser("Student", "B", "Ionescu");
        User studentC = UserFactory.createUser("Student", "C", "Ionescu");
 
        User mother = UserFactory.createUser("Parent", "M_AC", "Ionescu");
        User father = UserFactory.createUser("Parent", "T_AC", "Ionescu");
 
        User teacher = UserFactory.createUser("Teacher", "Teacher", "Georgescu");
        User assistant = UserFactory.createUser("Assistant", "Assistant", "Popescu");
 
        //testare exercitiu 3+5
        Course course = new Course.CourseBuilder("POO").teacher((Teacher) teacher)
       .assistant((Assistant) assistant).grade(new Grade("POO", (Student) studentA, 4d,5d))
       .grade(new Grade("POO", (Student) studentB,3d,3d)).strategy(new BestExamScore()).build();
 
        System.out.println("Curs: "+ course);
        System.out.println("Best Student:" + course.getBestStudent());
 
        //testare exercitiu 1+3+5
        Catalog catalog = Catalog.getInstance();
        catalog.addCourse(course);
 
        //testare exercitiu 4
        ((Student) studentB).setMother((Parent) mother);
        ((Student) studentB).setFather((Parent) father);
        ((Student) studentC).setMother((Parent) mother);
 
        catalog.addObserver((Parent) mother);
        catalog.addObserver((Parent) father);
        catalog.notifyObservers(new Grade("POO", (Student)studentB,2.5d,3d));
 
        //testare exercitiu 6
        HashMap<Teacher, ArrayList<Pair<Student, String, Double>>> examScores=new HashMap<>();
        ArrayList<Pair<Student, String, Double>> ar1=new ArrayList<>();
        ar1.add(new Pair(studentA,"POO",3.6d));
        examScores.put((Teacher)teacher,ar1);
 
        HashMap<Assistant, ArrayList<Pair<Student, String, Double>>> partialScores= new HashMap<>();
        ArrayList<Pair<Student, String, Double>> ar2=new ArrayList<>();
        ar2.add(new Pair(studentC,"POO",4.6d));
        partialScores.put((Assistant)assistant,ar2);
 
       Visitor v=new ScoreVisitor(examScores,partialScores);
 
        v.visit((Teacher)teacher);
        System.out.println("Actualizare teacher:" + catalog);
 
        v.visit((Assistant)assistant);
        System.out.println("Actualizare assistant:" + catalog);
 
    }
}